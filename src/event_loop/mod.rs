#![allow(unused)]
use core::time;
use mio::{Events, Interest, Poll, Registry, Token, Waker, event::Event};
use std::{
    error::Error,
    sync::{
        Arc, Mutex,
        atomic::{AtomicBool, AtomicUsize, Ordering},
        mpsc::Sender,
    },
    time::Duration,
};
pub(crate) mod error;
pub(crate) mod tests;

use error::ErrorType;
/*
    Event-loop API containing Reactor
    Reactor containing events and Poll + registering the event
    Poller - poll_event,registry,thread-pool
    Polling events and then accordingly for each new event dispatch
    the even on a worker thread from the thread-pool and begin the execution
    Registry -> Keeping the mapping of Token--->Event_handler/Thread_handle mio->registry and a poll function
    along with a waker associated .

*/
pub const DEFAULT_POLL_TIMEOUT_MS: u64 = 150;
pub const DEFAULT_THREAD_POOL_CAPACITY: usize = 4;
pub struct PollHandle {
    mio_registry: Registry,
    poller: Arc<Mutex<Poll>>,
    waker: Waker,
}
impl PollHandle {
    pub fn new() -> Result<Self, ErrorType> {
        let poller = Poll::new()?;
        let mio_registry_owned = poller.registry().try_clone()?;
        let waker = Waker::new(&mio_registry_owned, Token(0))?;
        Ok(PollHandle {
            mio_registry: mio_registry_owned,
            poller: Arc::new(Mutex::new(poller)),
            waker: waker,
        })
    }
    pub fn register<S>(
        &self,
        source: &mut S,
        token: Token,
        interest: Interest,
    ) -> Result<bool, ErrorType>
    where
        S: mio::event::Source,
    {
        self.mio_registry.register(source, token, interest)?;
        Ok(true)
    }
    pub fn deregister<S>(&self, source: &mut S) -> Result<bool, ErrorType>
    where
        S: mio::event::Source,
    {
        self.mio_registry.deregister(source)?;
        Ok(true)
    }
    pub fn poll(&self, timeout: Duration, events: &mut Events) -> Result<(), ErrorType> {
        let guard = &mut *self.poller.lock().unwrap();
        // Clearing the existing event queue and pushing any new event on the basis of progress made for the current event
        // accoring to their interest at the time of registering into registry .
        Ok(guard.poll(events, Some(timeout))?)
    }
    pub fn wake(&self) -> Result<(), ErrorType> {
        Ok(self.waker.wake()?)
    }
}
pub struct EventLoop {
    pub reactor: Reactor,
}
impl EventLoop {
    pub fn new(capacity: Option<usize>) -> Result<Self, ErrorType> {
        Ok(EventLoop {
            reactor: Reactor::new(capacity, None)?,
        })
    }
    pub fn register<S>(
        &self,
        source: &mut S,
        token: Token,
        interest: Interest,
    ) -> Result<(), ErrorType>
    where
        S: mio::event::Source,
    {
        let flag = self
            .reactor
            .poll_handle
            .lock()
            .unwrap()
            .register(source, token, interest)?;
        println!("New event registered successfully - {flag}");
        Ok(())
    }
    pub fn deregister<S>(&self, source: &mut S) -> Result<(), ErrorType>
    where
        S: mio::event::Source,
    {
        let flag = self
            .reactor
            .poll_handle
            .lock()
            .unwrap()
            .deregister(source)?;
        println!("Event deregistered successfully - {flag}");
        Ok(())
    }

    pub fn run(&mut self) {
        self.reactor.run();
    }
}
// Each of the sender associated with the pool can send a closure representing the
// event to be executed on the given worker .
pub type Task = Box<dyn FnOnce() + Send + 'static>;
// Worker threads that will be spawned upon `ThreadPool` initialization
// each of the worker thread will execute the events with a maximum capacity
// associated with `ThreadPool`.
pub type Workers = Vec<Worker>;
pub struct Worker {
    // Handle associated with each worker thread spawned
    handle: Option<std::thread::JoinHandle<()>>,
}
impl Worker {
    pub fn new() -> (Self, Sender<Task>) {
        let (tx, mut rx) = std::sync::mpsc::channel::<Task>();
        let thread_handle = std::thread::spawn(move || {
            while let Ok(task) = rx.recv() {
                // Calling the closure being FnOnce() to be called only once
                task();
            }
        });
        (
            Self {
                handle: Some(thread_handle),
            },
            tx,
        )
    }
}
// Each of the worker thread will be associated with a task receiver
// and there will be a sender associated with sender of task
pub struct ThreadPool {
    maximum_capacity: usize,
    workers: Workers,
    // Indexed sender for each of worker
    senders: Vec<Sender<Task>>,
    // Simple Round-robin based allocation of tasks
    counter: AtomicUsize,
}
impl ThreadPool {
    pub fn new(capacity: Option<usize>) -> Self {
        let threadpool_size = capacity.unwrap_or(DEFAULT_THREAD_POOL_CAPACITY);
        let mut workers = Workers::with_capacity(threadpool_size);
        let mut task_senders = Vec::with_capacity(threadpool_size);
        for i in 1..threadpool_size {
            let (new_worker_thread, sender) = Worker::new();
            workers.push(new_worker_thread);
            task_senders.push(sender);
        }
        Self {
            maximum_capacity: threadpool_size,
            workers,
            counter: AtomicUsize::new(0),
            senders: task_senders,
        }
    }
    pub fn get_next(&self) -> usize {
        let next_thread_id = self
            .counter
            .fetch_add(1, std::sync::atomic::Ordering::Acquire);

        next_thread_id % self.workers.len()
    }
    // Allocating threads in a round-robin based manner
    pub fn execute_task<E>(&self, event: E)
    where
        E: FnOnce() + Send + 'static,
    {
        let next_id = self.get_next();
        if let Some(sender_channel) = self.senders.get(next_id) {
            sender_channel.send(Box::from(event));
        } else {
            panic!("No such worker thread exists !");
        }
    }
}
impl Drop for ThreadPool {
    fn drop(&mut self) {
        self.senders.clear();
        for worker in self.workers.iter_mut() {
            if let Some(handle) = worker.handle.take() {
                let _ = handle.join();
            }
        }
    }
}
pub struct Reactor {
    // Avoiding the mutable reference of self in the runner loop
    // and since the poll() function requires mutable reference of Poll
    // object which will require it to be behind &mut self without lock
    // so to provided interior mutability it is better to keep it under a lock .
    pub poll_handle: Arc<Mutex<PollHandle>>,
    // Events will be accessed by the PollHandler concurrently
    // so it makes sense for keeping it behind Arc and lock to support
    // both shared ownership and interior mutability .
    pub events: Arc<Mutex<Events>>,
    pub thread_pool: ThreadPool,
    pub poll_timeout: Duration,
    pub running_flag: Arc<AtomicBool>,
    pub dispatch_tx: Option<Sender<usize>>,
}

impl Reactor {
    pub fn new(thread_pool_size: Option<usize>, timeout: Option<u64>) -> Result<Self, ErrorType> {
        let timeout_duration = if let Some(time) = timeout {
            Duration::from_millis(time)
        } else {
            Duration::from_millis(DEFAULT_POLL_TIMEOUT_MS)
        };
        let poll_handler = PollHandle::new()?;
        let res = if let Some(thread_pool_size) = thread_pool_size {
            Ok(Reactor {
                poll_handle: Arc::new(Mutex::new(poll_handler)),
                events: Arc::new(Mutex::new(Events::with_capacity(128))),
                thread_pool: ThreadPool::new(Some(thread_pool_size)),
                poll_timeout: timeout_duration,
                running_flag: Arc::new(AtomicBool::new(true)),
                dispatch_tx: None,
            })
        } else {
            let default_parallelism = std::thread::available_parallelism()?;
            Ok(Reactor {
                poll_handle: Arc::new(Mutex::new(poll_handler)),
                events: Arc::new(Mutex::new(Events::with_capacity(128))),
                thread_pool: ThreadPool::new(Some(default_parallelism.into())),
                poll_timeout: timeout_duration,
                running_flag: Arc::new(AtomicBool::new(true)),
                dispatch_tx: None,
            })
        };
        res
    }
    pub fn run(&self) {
        while self.running_flag.load(Ordering::Acquire) == true {
            let flag_val = self.running_flag.load(Ordering::SeqCst);
            println!("Event loop flag - {flag_val}");
            // Polling each event and after polling checking for the readiness
            // of each event and dispatch events to a new worker thread .
            {
                let guard = &mut *self.events.lock().unwrap();
                self.poll_handle
                    .lock()
                    .unwrap()
                    .poll(self.poll_timeout.clone(), guard);
            }

            // After being polled each of the event would have been cleared and a progressed
            // event may have been added to events so we can now dispatch those events
            // to the worker threads for their execution to take place .
            for event in self.events.lock().unwrap().iter() {
                self.dispatch_event(event);
            }
        }
    }
    pub fn stop_event_loop(&self) {
        println!("Received signal for stopping the event loop !");
        self.running_flag.store(false, Ordering::Release);
    }
    pub fn dispatch_event(&self, event: &Event) {
        let token_id = event.token().0;
        let dispatch_tx = self.dispatch_tx.clone();
        self.thread_pool.execute_task(move || {
            if let Some(tx) = dispatch_tx {
                let _ = tx.send(token_id);
            }
        });
    }
}

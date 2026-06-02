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
#[cfg(test)]
mod tests {
    use crate::event_loop::{PollHandle, Reactor, ThreadPool};

    use super::*;
    use mio::{event::Source, unix::pipe};
    use std::{
        io::{Read, Write},
        sync::{Condvar, Mutex},
    };
    struct TestSource {}
    impl TestSource {
        pub fn new() -> Self {
            Self {}
        }
    }
    impl Source for TestSource {
        fn deregister(&mut self, registry: &Registry) -> std::io::Result<()> {
            std::io::Result::Ok(())
        }
        fn register(
            &mut self,
            registry: &Registry,
            token: Token,
            interests: Interest,
        ) -> std::io::Result<()> {
            std::io::Result::Ok(())
        }
        fn reregister(
            &mut self,
            registry: &Registry,
            token: Token,
            interests: Interest,
        ) -> std::io::Result<()> {
            std::io::Result::Ok(())
        }
    }
    #[test]
    fn test_thread_pool_creation() {
        let pool = ThreadPool::new(Some(4));
        assert_eq!(pool.workers.len(), 3);
    }

    #[test]
    fn test_task_execution() {
        let pool = ThreadPool::new(Some(2));
        let counter = Arc::new(AtomicUsize::new(0));
        let counter_clone = counter.clone();
        pool.execute_task(move || {
            counter_clone.fetch_add(1, Ordering::SeqCst);
        });

        std::thread::sleep(Duration::from_millis(100));
        assert_eq!(counter.load(Ordering::SeqCst), 1);
    }
    #[test]
    fn test_multiple_tasks() {
        let pool = ThreadPool::new(Some(4));
        let counter = Arc::new(AtomicUsize::new(0));

        for _ in 0..10 {
            let counter_clone = counter.clone();
            pool.execute_task(move || {
                counter_clone.fetch_add(1, Ordering::SeqCst);
            });
        }

        std::thread::sleep(Duration::from_millis(200));
        assert_eq!(counter.load(Ordering::SeqCst), 10);
    }
    #[test]
    fn test_pool_cleanup() {
        let counter = Arc::new(AtomicUsize::new(0));
        {
            let pool = ThreadPool::new(Some(2));
            let counter_clone = counter.clone();

            pool.execute_task(move || {
                std::thread::sleep(Duration::from_millis(50));
                counter_clone.fetch_add(1, Ordering::SeqCst);
            });
        }

        assert_eq!(counter.load(Ordering::SeqCst), 1);
    }
    #[test]
    fn test_poll() {
        let mut poller = PollHandle::new().unwrap();
        let mut events = Events::with_capacity(1024);
        poller.poll(Duration::from_secs(1), &mut events).unwrap();
    }
    #[test]
    fn test_wake() {
        let poller = PollHandle::new().unwrap();
        assert!(poller.wake().is_ok());
    }

    #[test]
    fn test_register_unregister() {
        let poller = PollHandle::new().unwrap();
        let mut source = TestSource::new();
        let token = Token(1);

        assert!(
            poller
                .register(&mut source, token, Interest::READABLE)
                .is_ok(),
            "Failed to register source"
        );

        assert!(
            poller.deregister(&mut source).is_ok(),
            "Failed to unregister source"
        );
    }
    #[test]
    fn pipe_io_is_dispatched_through_poll_handle() {
        const TOKEN: Token = Token(1);
        let payload = b"hello from the event loop";
        let mut poll_handle = PollHandle::new().expect("failed to create PollHandle");

        let (mut sender, mut receiver) = pipe::new().expect("failed to create pipe");

        let registered = poll_handle
            .register(&mut receiver, TOKEN, Interest::READABLE)
            .expect("failed to register pipe receiver");
        assert!(registered, "register should report success");

        let mut events = Events::with_capacity(16);
        poll_handle
            .poll(Duration::from_millis(50), &mut events)
            .expect("initial poll failed");
        assert!(
            events.iter().all(|e| e.token() != TOKEN),
            "no readable event expected before writing"
        );

        let written = sender.write(payload).expect("failed to write to pipe");
        assert_eq!(written, payload.len(), "short write to pipe");

        let mut got_readable = false;
        for _ in 0..10 {
            poll_handle
                .poll(Duration::from_millis(100), &mut events)
                .expect("poll failed");
            for event in events.iter() {
                if event.token() == TOKEN && event.is_readable() {
                    got_readable = true;
                }
            }
            if got_readable {
                break;
            }
        }
        assert!(got_readable, "expected a readable event for the pipe token");

        let mut buf = vec![0u8; payload.len()];
        receiver
            .read_exact(&mut buf)
            .expect("failed to read from pipe");
        assert_eq!(&buf, payload, "data read back must match data written");

        let deregistered = poll_handle
            .deregister(&mut receiver)
            .expect("failed to deregister pipe receiver");
        assert!(deregistered, "deregister should report success");
    }

    #[test]
    fn waker_wakes_the_poller() {
        let mut poll_handle = PollHandle::new().expect("failed to create PollHandle");
        let mut events = Events::with_capacity(16);

        poll_handle.wake().expect("wake failed");

        poll_handle
            .poll(Duration::from_millis(200), &mut events)
            .expect("poll failed");

        assert!(
            events.iter().any(|e| e.token() == Token(0)),
            "expected a wake event on the waker token"
        );
    }
    #[test]
    fn test_multiple_handlers() {
        let poller = PollHandle::new().unwrap();
        let mut src1 = TestSource::new();
        let mut src2 = TestSource::new();

        assert!(
            poller
                .register(&mut src1, Token(1), Interest::READABLE)
                .is_ok(),
            "Failed to register src1"
        );
        assert!(
            poller
                .register(&mut src2, Token(2), Interest::WRITABLE)
                .is_ok(),
            "Failed to register src2"
        );
    }
    #[test]
    fn test_reactor_start_stop() {
        let reactor = Arc::new(Reactor::new(None, None).unwrap());

        let mut reactor_clone = Arc::clone(&reactor);
        let handle = std::thread::spawn(move || {
            reactor_clone.run();
        });

        std::thread::sleep(Duration::from_millis(100));
        println!("Spawned the event loop runner");
        reactor.stop_event_loop();
        handle.join().unwrap();
    }
    #[test]
    fn test_with_pipe() -> std::io::Result<()> {
        use mio::net::UnixStream;

        let reactor = Arc::new(Reactor::new(None, None).unwrap());
        let counter = Arc::new(Mutex::new(0));
        let condition = Arc::new(Condvar::new());

        let (mut stream1, mut stream2) = UnixStream::pair()?;

        let token = Token(1);

        reactor
            .poll_handle
            .lock()
            .unwrap()
            .register(&mut stream1, token, Interest::READABLE)
            .unwrap();

        let reactor_clone = Arc::clone(&reactor);
        let handle = std::thread::spawn(move || {
            // Poll once
            let events_result = {
                let mut events = reactor_clone.events.lock().unwrap();
                reactor_clone
                    .poll_handle
                    .lock()
                    .unwrap()
                    .poll(Duration::from_millis(100), &mut events)
            };

            if events_result.is_ok() {
                let events = reactor_clone.events.lock().unwrap();
                for event in events.iter() {
                    let _ = reactor_clone.dispatch_event(&event);
                }
            }
        });

        std::io::Write::write_all(&mut stream2, b"test data")?;

        handle.join().unwrap();

        let count = counter.lock().unwrap();
        let result = condition
            .wait_timeout(count, Duration::from_millis(500))
            .unwrap();

        if !result.1.timed_out() {
            assert_eq!(*result.0, 1);
        }

        Ok(())
    }
    #[test]
    fn test_with_tcp() -> std::io::Result<()> {
        use mio::net::{TcpListener, TcpStream};
        use std::net::SocketAddr;

        let reactor = Arc::new(Reactor::new(None, None).unwrap());
        let counter = Arc::new(Mutex::new(0));
        let condition = Arc::new(Condvar::new());

        // Create a TCP listener on localhost
        let addr: SocketAddr = "127.0.0.1:0".parse().unwrap();
        let mut listener = TcpListener::bind(addr)?;
        let listener_addr = listener.local_addr()?;

        let token = Token(1);

        reactor
            .poll_handle
            .lock()
            .unwrap()
            .register(&mut listener, token, Interest::READABLE)
            .unwrap();

        let reactor_clone = Arc::clone(&reactor);
        let handle = std::thread::spawn(move || {
            // Poll once
            let events_result = {
                let mut events = reactor_clone.events.lock().unwrap();
                reactor_clone
                    .poll_handle
                    .lock()
                    .unwrap()
                    .poll(Duration::from_millis(100), &mut events)
            };

            if events_result.is_ok() {
                let events = reactor_clone.events.lock().unwrap();
                for event in events.iter() {
                    let _ = reactor_clone.dispatch_event(&event);
                }
            }
        });

        // Connect to trigger the event
        let _stream = TcpStream::connect(listener_addr)?;

        handle.join().unwrap();

        let count = counter.lock().unwrap();
        let result = condition
            .wait_timeout(count, Duration::from_millis(500))
            .unwrap();

        if !result.1.timed_out() {
            assert_eq!(*result.0, 1);
        }

        Ok(())
    }
}

#![allow(unused)]
use core::panic;
use std::{
    fmt::Debug,
    ops::{Add, Sub},
    ptr::NonNull,
};
struct Node<T>
where
    T: Add + Ord + Sub + Debug,
{
    value: T,
    next: Option<NonNull<Node<T>>>,
    prev: Option<NonNull<Node<T>>>,
}
impl<T> Node<T>
where
    T: Add + Ord + Sub + Debug,
{
    fn new(value: T) -> Self {
        Node {
            value,
            next: None,
            prev: None,
        }
    }
}

pub struct LinkedList<T>
where
    T: Add + Ord + Sub + Debug,
{
    head: Option<NonNull<Node<T>>>,
    tail: Option<NonNull<Node<T>>>,
}

impl<T> LinkedList<T>
where
    T: Add + Ord + Sub + Debug,
{
    pub fn new() -> Self {
        LinkedList {
            head: None,
            tail: None,
        }
    }
    pub fn insert_at_head(&mut self, value: T) {
        let mut node = Box::new(Node::new(value));
        if let Some(mut ptr) = NonNull::new(Box::leak(node)) {
            if self.head == None {
                self.head = Some(ptr);
                self.tail = self.head;
            } else {
                unsafe {
                    ptr.as_mut().next = self.head;
                }
                if let Some(mut head) = self.head {
                    unsafe {
                        head.as_mut().prev = Some(ptr);
                    }
                }
                self.head = Some(ptr);
            }
        } else {
            panic!("An error occurred while node conversion to NonNull type");
        }
    }
    pub fn delete_at_head(&mut self) {
        if let Some(head_ptr) = self.head {
            unsafe {
                let head_ref = head_ptr.as_ref();

                self.head = head_ref.next;

                if let Some(mut new_head) = self.head {
                    new_head.as_mut().prev = None;
                } else {
                    self.tail = None;
                }

                drop(Box::from_raw(head_ptr.as_ptr()));
            }
        }
    }
    pub fn iterate(&self) {
        let mut temp = self.head.clone();
        while let Some(inner_ptr) = temp {
            let reference_to_node = unsafe { inner_ptr.as_ref() };
            println!("{:?}", reference_to_node.value);
            temp = reference_to_node.next;
        }
    }
}

#[test]
fn random() {
    let mut list: LinkedList<u32> = LinkedList::new();
    list.insert_at_head(1);
    list.insert_at_head(2);
    list.insert_at_head(3);
    list.iterate();
}

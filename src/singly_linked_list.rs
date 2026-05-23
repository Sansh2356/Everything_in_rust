#![allow(unused)]
use core::panic;
use std::{
    fmt::Debug,
    marker::PhantomData,
    ops::{Add, Sub},
    ptr::NonNull,
};
struct Node<T>
where
    T: Add + Ord + Sub + Debug + Clone,
{
    value: T,
    next: Option<NonNull<Node<T>>>,
    prev: Option<NonNull<Node<T>>>,
}
impl<T> Node<T>
where
    T: Add + Ord + Sub + Debug + Clone,
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
    T: Add + Ord + Sub + Debug + Clone,
{
    head: Option<NonNull<Node<T>>>,
    tail: Option<NonNull<Node<T>>>,
    len: usize,
}

impl<T> LinkedList<T>
where
    T: Add + Ord + Sub + Debug + Clone,
{
    pub fn new() -> Self {
        LinkedList {
            head: None,
            tail: None,
            len: 0usize,
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
            self.len += 1;
        } else {
            panic!("An error occurred while node conversion to NonNull type");
        }
    }
    pub fn insert_at_tail(&mut self, value: T) {
        let mut node = Box::new(Node::new(value));
        if let Some(mut ptr) = NonNull::new(Box::leak(node)) {
            if self.tail == None {
                self.tail = Some(ptr);
                self.head = self.tail;
            } else {
                unsafe {
                    ptr.as_mut().prev = self.tail;
                }
                if let Some(mut tail) = self.tail {
                    unsafe {
                        tail.as_mut().next = Some(ptr);
                    }
                }
                self.tail = Some(ptr);
            }
            self.len += 1;
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
            self.len -= 1;
        }
    }
    pub fn deleted_at_tail(&mut self) {
        if let Some(mut tail_ptr) = self.tail {
            unsafe {
                let tail_ptr_ref = tail_ptr.as_ref();
                self.tail = tail_ptr_ref.prev;
                if let Some(mut new_tail) = self.tail {
                    new_tail.as_mut().next = None;
                } else {
                    self.head = None;
                }
                drop(Box::from_raw(tail_ptr.as_ptr()));
            }
            self.len -= 1;
        }
    }

    pub fn insert_at_position(&mut self, value: T, pos: &mut usize) {
        if self.head == None || self.tail == None {
            println!("No nodes to delete in current linked list");
            return;
        } else if *pos == 0 {
            self.insert_at_head(value);
        } else if self.len == *pos {
            self.insert_at_tail(value);
        } else {
            let new_node = Box::new(Node::new(value));
            if let Some(mut new_node_ptr) = NonNull::new(Box::leak(new_node)) {
                let mut temp_node = self.head.clone();
                unsafe {
                    while let Some(mut temp) = temp_node {
                        if *pos == 1 {
                            break;
                        }
                        let temp_reference = temp.as_ref();
                        temp_node = temp_reference.next;
                        *pos -= 1;
                    }
                    if let Some(mut node) = temp_node {
                        let mut_reference_newnode = new_node_ptr.as_mut();
                        let node_ref = node.as_mut();
                        mut_reference_newnode.next = Some(node);
                        mut_reference_newnode.prev = node_ref.prev;
                        if let Some(mut prev_node) = node_ref.prev {
                            prev_node.as_mut().next = Some(node);
                        }
                        node_ref.prev = Some(node);
                    }
                }
            } else {
                panic!("An error occurred while allocating new node over heap");
            }
        }
        self.len += 1;
    }
    pub fn delete_at_position(&mut self, pos: &mut usize) {
        if *pos < 1 || *pos > self.len {
            return;
        }
        if *pos == 1 {
            self.delete_at_head();
        } else if *pos == self.len {
            self.deleted_at_tail();
        } else {
            let mut temp_node = self.head.clone();
            unsafe {
                while let Some(mut temp) = temp_node {
                    if *pos == 1 {
                        break;
                    }
                    let temp_reference = temp.as_ref();
                    temp_node = temp_reference.next;
                    *pos -= 1;
                }
                if let Some(node) = temp_node {
                    let node_ref = node.as_ref();
                    if let Some(mut prev_node) = node_ref.prev {
                        prev_node.as_mut().next = node_ref.next;
                    }
                    if let Some(mut next_node) = node_ref.next {
                        next_node.as_mut().prev = node_ref.prev;
                    }
                    drop(Box::from_raw(node.as_ptr()));
                }
            }
        }
        self.len -= 1;
    }
    pub fn iterate(&self) {
        let mut temp = self.head.clone();
        while let Some(inner_ptr) = temp {
            let reference_to_node = unsafe { inner_ptr.as_ref() };
            println!("{:?}", reference_to_node.value);
            temp = reference_to_node.next;
        }
    }
    pub fn iter(&self) -> Iter<'_, T> {
        Iter {
            next: self.head,
            _marker: PhantomData,
        }
    }
}

pub struct Iter<'a, T>
where
    T: Add + Ord + Sub + Debug + Clone,
{
    next: Option<NonNull<Node<T>>>,
    _marker: PhantomData<&'a T>,
}

impl<'a, T> Iterator for Iter<'a, T>
where
    T: Add + Ord + Sub + Debug + Clone,
{
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        self.next.map(|node| unsafe {
            let node_ref = node.as_ref();
            self.next = node_ref.next;
            &node_ref.value
        })
    }
}

impl<'a, T> IntoIterator for &'a LinkedList<T>
where
    T: Add + Ord + Sub + Debug + Clone,
{
    type Item = &'a T;
    type IntoIter = Iter<'a, T>;

    fn into_iter(self) -> Self::IntoIter {
        self.iter()
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    fn collect_forward(list: &LinkedList<i32>) -> Vec<i32> {
        let mut result = Vec::new();
        for node_val in list.iter() {
            result.push(*node_val);
        }
        result
    }

    fn collect_backward(list: &LinkedList<i32>) -> Vec<i32> {
        let mut result = Vec::new();
        let mut temp = list.tail;
        while let Some(ptr) = temp {
            unsafe {
                let node_ref = ptr.as_ref();
                result.push(node_ref.value);
                temp = node_ref.prev;
            }
        }
        result
    }
    #[test]
    fn new_creates_empty_list() {
        let list: LinkedList<i32> = LinkedList::new();
        assert_eq!(list.len, 0);
        assert!(list.head.is_none());
        assert!(list.tail.is_none());
    }

    #[test]
    fn insert_at_head_into_empty_sets_head_and_tail() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_head(10);
        assert_eq!(list.len, 1);
        assert!(list.head.is_some());
        assert!(list.tail.is_some());
        assert_eq!(list.head, list.tail);
        assert_eq!(collect_forward(&list), vec![10]);
        assert_eq!(collect_backward(&list), vec![10]);
    }

    #[test]
    fn insert_at_head_multiple_preserves_reverse_order() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_head(1);
        list.insert_at_head(2);
        list.insert_at_head(3);
        assert_eq!(list.len, 3);
        assert_eq!(collect_forward(&list), vec![3, 2, 1]);
        assert_eq!(collect_backward(&list), vec![1, 2, 3]);
    }

    #[test]
    fn insert_at_tail_into_empty_sets_head_and_tail() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(7);
        assert_eq!(list.len, 1);
        assert!(list.head.is_some());
        assert!(list.tail.is_some());
        assert_eq!(list.head, list.tail);
        assert_eq!(collect_forward(&list), vec![7]);
        assert_eq!(collect_backward(&list), vec![7]);
    }

    #[test]
    fn insert_at_tail_multiple_preserves_insertion_order() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        list.insert_at_tail(3);
        assert_eq!(list.len, 3);
        assert_eq!(collect_forward(&list), vec![1, 2, 3]);
        assert_eq!(collect_backward(&list), vec![3, 2, 1]);
    }

    #[test]
    fn mixed_head_and_tail_insertions() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(2);
        list.insert_at_head(1);
        list.insert_at_tail(3);
        list.insert_at_head(0);
        assert_eq!(list.len, 4);
        assert_eq!(collect_forward(&list), vec![0, 1, 2, 3]);
        assert_eq!(collect_backward(&list), vec![3, 2, 1, 0]);
    }

    #[test]
    fn delete_at_head_on_empty_is_noop() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.delete_at_head();
        assert_eq!(list.len, 0);
        assert!(list.head.is_none());
        assert!(list.tail.is_none());
    }

    #[test]
    fn delete_at_head_single_element_empties_list() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_head(42);
        list.delete_at_head();
        assert_eq!(list.len, 0);
        assert!(list.head.is_none());
        assert!(list.tail.is_none());
    }

    #[test]
    fn delete_at_head_multiple_removes_front() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        list.insert_at_tail(3);
        list.delete_at_head();
        assert_eq!(list.len, 2);
        assert_eq!(collect_forward(&list), vec![2, 3]);
        assert_eq!(collect_backward(&list), vec![3, 2]);
    }

    #[test]
    fn delete_at_head_until_empty() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        list.delete_at_head();
        list.delete_at_head();
        assert_eq!(list.len, 0);
        assert!(list.head.is_none());
        assert!(list.tail.is_none());
    }

    #[test]
    fn deleted_at_tail_on_empty_is_noop() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.deleted_at_tail();
        assert_eq!(list.len, 0);
        assert!(list.head.is_none());
        assert!(list.tail.is_none());
    }

    #[test]
    fn deleted_at_tail_single_element_empties_list() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(99);
        list.deleted_at_tail();
        assert_eq!(list.len, 0);
        assert!(list.head.is_none());
        assert!(list.tail.is_none());
    }

    #[test]
    fn deleted_at_tail_multiple_removes_back() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        list.insert_at_tail(3);
        list.deleted_at_tail();
        assert_eq!(list.len, 2);
        assert_eq!(collect_forward(&list), vec![1, 2]);
        assert_eq!(collect_backward(&list), vec![2, 1]);
    }

    #[test]
    fn deleted_at_tail_until_empty() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        list.deleted_at_tail();
        list.deleted_at_tail();
        assert_eq!(list.len, 0);
        assert!(list.head.is_none());
        assert!(list.tail.is_none());
    }

    #[test]
    fn insert_at_position_on_empty_list_is_noop() {
        let mut list: LinkedList<i32> = LinkedList::new();
        let mut pos = 0usize;
        list.insert_at_position(5, &mut pos);
        assert_eq!(list.len, 0);
        assert!(list.head.is_none());
        assert!(list.tail.is_none());
    }

    #[test]
    fn delete_at_position_with_zero_is_noop() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        let mut pos = 0usize;
        list.delete_at_position(&mut pos);
        assert_eq!(list.len, 2);
        assert_eq!(collect_forward(&list), vec![1, 2]);
    }

    #[test]
    fn delete_at_position_out_of_range_is_noop() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        let mut pos = 99usize;
        list.delete_at_position(&mut pos);
        assert_eq!(list.len, 2);
        assert_eq!(collect_forward(&list), vec![1, 2]);
    }

    #[test]
    fn delete_at_position_on_empty_is_noop() {
        let mut list: LinkedList<i32> = LinkedList::new();
        let mut pos = 1usize;
        list.delete_at_position(&mut pos);
        assert_eq!(list.len, 0);
        assert!(list.head.is_none());
        assert!(list.tail.is_none());
    }

    #[test]
    fn iterate_on_empty_does_not_panic() {
        let list: LinkedList<i32> = LinkedList::new();
        list.iterate();
    }

    #[test]
    fn iterate_on_populated_does_not_panic() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        list.insert_at_tail(3);
        list.iterate();
    }

    #[test]
    fn iter_on_empty_list_yields_nothing() {
        let list: LinkedList<i32> = LinkedList::new();
        let collected: Vec<&i32> = list.iter().collect();
        assert!(collected.is_empty());
    }

    #[test]
    fn iter_yields_values_in_order() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        list.insert_at_tail(3);
        let collected: Vec<i32> = list.iter().copied().collect();
        assert_eq!(collected, vec![1, 2, 3]);
    }

    #[test]
    fn into_iterator_for_reference_works_in_for_loop() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(10);
        list.insert_at_tail(20);
        list.insert_at_tail(30);
        let mut sum = 0;
        for value in &list {
            sum += *value;
        }
        assert_eq!(sum, 60);
    }

    #[test]
    fn iter_can_be_used_with_adapters() {
        let mut list: LinkedList<i32> = LinkedList::new();
        list.insert_at_tail(1);
        list.insert_at_tail(2);
        list.insert_at_tail(3);
        list.insert_at_tail(4);
        let doubled: Vec<i32> = list.iter().map(|v| v * 2).collect();
        assert_eq!(doubled, vec![2, 4, 6, 8]);
        let count = list.iter().filter(|v| **v > 1).count();
        assert_eq!(count, 3);
    }
}

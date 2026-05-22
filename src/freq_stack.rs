#![allow(unused)]
use std::collections::{HashMap, VecDeque};
struct FreqStack {
    pub maximum_frequency: usize,
    pub stack_map: HashMap<usize, VecDeque<i32>>,
    pub freq_map: HashMap<i32, usize>,
}

impl FreqStack {
    fn new() -> Self {
        FreqStack {
            maximum_frequency: 0usize,
            stack_map: HashMap::new(),
            freq_map: HashMap::new(),
        }
    }

    fn push(&mut self, val: i32) {
        let freq = self.freq_map.entry(val).or_insert(0);
        *freq += 1;

        self.maximum_frequency = self.maximum_frequency.max(*freq);
        self.stack_map
            .entry(*freq)
            .or_insert_with(VecDeque::new)
            .push_back(val);
    }

    fn pop(&mut self) -> i32 {
        if let Some(stack) = self.stack_map.get_mut(&self.maximum_frequency) {
            if stack.len() != 0 {
                let top = stack.pop_back().unwrap();
                if let Some(freq_map) = self.freq_map.get_mut(&top) {
                    *freq_map -= 1;
                }
                return top;
            } else {
                self.maximum_frequency -= 1;
                if let Some(stack) = self.stack_map.get_mut(&self.maximum_frequency) {
                    let top = stack.pop_back().unwrap();
                    if let Some(freq_map) = self.freq_map.get_mut(&top) {
                        *freq_map -= 1;
                    }
                    return top;
                }
            }
        }
        -1
    }
}
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pop_on_empty_returns_sentinel() {
        let mut s = FreqStack::new();
        assert_eq!(s.pop(), -1);
    }

    #[test]
    fn single_push_then_pop() {
        let mut s = FreqStack::new();
        s.push(42);
        assert_eq!(s.pop(), 42);
    }

    #[test]
    fn distinct_values_pop_in_lifo_order() {
        let mut s = FreqStack::new();
        s.push(1);
        s.push(2);
        s.push(3);
        assert_eq!(s.pop(), 3);
        assert_eq!(s.pop(), 2);
        assert_eq!(s.pop(), 1);
    }

    #[test]
    fn example_test_case() {
        let mut s = FreqStack::new();
        s.push(5);
        s.push(7);
        s.push(5);
        s.push(7);
        s.push(4);
        s.push(5);
        assert_eq!(s.pop(), 5);
        assert_eq!(s.pop(), 7);
        assert_eq!(s.pop(), 5);
        assert_eq!(s.pop(), 4);
    }

    #[test]
    fn ties_broken_by_most_recent_push() {
        let mut s = FreqStack::new();
        s.push(1);
        s.push(2);
        assert_eq!(s.pop(), 2);
        assert_eq!(s.pop(), 1);
    }

    #[test]
    fn repeated_pushes_of_same_value() {
        let mut s = FreqStack::new();
        s.push(9);
        s.push(9);
        s.push(9);
        assert_eq!(s.pop(), 9);
        assert_eq!(s.pop(), 9);
        assert_eq!(s.pop(), 9);
    }

    #[test]
    fn maximum_frequency_tracks_highest_count() {
        let mut s = FreqStack::new();
        s.push(1);
        assert_eq!(s.maximum_frequency, 1);
        s.push(2);
        assert_eq!(s.maximum_frequency, 1);
        s.push(1);
        assert_eq!(s.maximum_frequency, 2);
        s.push(1);
        assert_eq!(s.maximum_frequency, 3);
    }

    #[test]
    fn freq_map_decrements_on_pop() {
        let mut s = FreqStack::new();
        s.push(8);
        s.push(8);
        assert_eq!(s.freq_map.get(&8), Some(&2));
        s.pop();
        assert_eq!(s.freq_map.get(&8), Some(&1));
        s.pop();
        assert_eq!(s.freq_map.get(&8), Some(&0));
    }

    #[test]
    fn interleaved_push_and_pop() {
        let mut s = FreqStack::new();
        s.push(1);
        s.push(1);
        assert_eq!(s.pop(), 1);
        s.push(2);
        s.push(2);
        assert_eq!(s.pop(), 2);
        assert_eq!(s.pop(), 2);
        assert_eq!(s.pop(), 1);
    }

    #[test]
    fn negative_values_supported() {
        let mut s = FreqStack::new();
        s.push(-1);
        s.push(-2);
        s.push(-1);
        assert_eq!(s.pop(), -1);
        assert_eq!(s.pop(), -2);
        assert_eq!(s.pop(), -1);
    }
}

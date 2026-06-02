#![allow(unused)]
use std::ops::{Add, AddAssign, Sub};

#[derive(Clone)]
pub struct Collection {
    pub name: String,
    pub age: usize,
}
impl std::fmt::Display for Collection {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{} - {}", self.name, self.age)
    }
}
impl Collection {
    pub fn new(name: String, age: usize) -> Self {
        Collection { name, age }
    }
}

pub struct CollectionList {
    pub list: Vec<Collection>,
}

impl IntoIterator for CollectionList {
    type Item = Collection;
    type IntoIter = std::vec::IntoIter<Self::Item>;
    fn into_iter(self) -> Self::IntoIter {
        self.list.into_iter()
    }
}
pub struct Range<T>
where
    T: Sized + Ord + Sub + Add + Clone + AddAssign,
{
    pub start: T,
    pub end: T,
    pub step: T,
}

impl<T> Range<T>
where
    T: Sized + Ord + Sub + Add + Clone + AddAssign,
{
    pub fn new(start: T, end: T, step: T) -> Self {
        Range { start, end, step }
    }
}

impl<T> Iterator for Range<T>
where
    T: Sized + Ord + Sub + Add<Output = T> + Clone + AddAssign,
{
    type Item = T;
    fn next(&mut self) -> Option<Self::Item> {
        let res = if self.start >= self.end {
            None
        } else {
            let temp = self.start.clone();
            self.start = self.start.clone().add(self.step.clone());
            Some(temp)
        };
        res
    }
}
impl<T> DoubleEndedIterator for Range<T>
where
    T: Sized + Ord + Sub<Output = T> + Add<Output = T> + Clone + AddAssign,
{
    fn next_back(&mut self) -> Option<Self::Item> {
        let res = if self.start >= self.end {
            None
        } else {
            let temp = self.start.clone();
            self.start = self.start.clone().sub(self.step.clone());
            Some(temp)
        };
        res
    }
}
pub struct Flatten<O>
where
    O: Iterator,
    O::Item: IntoIterator,
{
    pub outer: O,
    pub inner: Option<<O::Item as IntoIterator>::IntoIter>,
}
impl<O> Iterator for Flatten<O>
where
    O: Iterator,
    O::Item: IntoIterator,
{
    type Item = <O::Item as IntoIterator>::Item;
    fn next(&mut self) -> Option<Self::Item> {
        loop {
            if let Some(ref mut inner_iterator) = self.inner {
                if let Some(inner_val) = inner_iterator.next() {
                    return Some(inner_val);
                } else {
                    self.inner = None;
                }
            }
            self.inner = Some(self.outer.next()?.into_iter());
        }
        None
    }
}

#[test]
fn random_test() {
    let list: CollectionList = CollectionList {
        list: Vec::from([Collection::new("Ansh".to_string(), 21)]),
    };
    for collection in list {
        println!("{}", collection);
    }
}
#[test]
fn range_test() {
    let rng = Range::new(0i32, 5i32, 2i32);
    for i in rng.rev() {
        println!("{i}");
    }
}
#[test]
fn random_test_flatten() {
    let iter = vec![vec![1, 4, 5], vec![2, 3, 4, 5]];
    let flatten_obj = Flatten {
        outer: iter.iter(),
        inner: None,
    };
    for item in flatten_obj {
        println!("{item}");
    }
}

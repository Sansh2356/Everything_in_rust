#![allow(unused)]
#![feature(btree_cursors)]
use std::fmt::Debug;
use std::io::{BufRead, Stdin, stdin};
use std::str::FromStr;
use std::{
    collections::{BTreeMap, VecDeque},
    ops::Bound,
};
pub struct InputReader;
impl InputReader {
    pub fn read_input<T>(mut obj: Box<dyn BufRead>) -> T
    where
        T: FromStr,
        <T as FromStr>::Err: Debug,
    {
        let mut buffer_string = String::new();
        let _ = obj.read_line(&mut buffer_string);
        buffer_string = buffer_string.trim().to_string();
        buffer_string.parse::<T>().unwrap()
    }
    pub fn read_input_vec<T>(mut obj: Box<dyn BufRead>) -> Vec<T>
    where
        T: FromStr,
        <T as FromStr>::Err: Debug,
    {
        let mut buffer_string = String::new();
        let _ = obj.read_line(&mut buffer_string);
        buffer_string
            .split_ascii_whitespace()
            .map(|mut val| {
                val = val.trim();
                return val.parse::<T>().unwrap();
            })
            .collect()
    }
}
#[allow(dead_code)]
fn random_problem(stdin: Stdin) {
    let mut buffer = String::from("");
    match stdin.read_line(&mut buffer) {
        Ok(_) => {}
        Err(error) => {
            panic!("{error:?}");
        }
    };
    let input = buffer.trim();
    let mut n = input.parse::<usize>().unwrap();
    let mut words: Vec<String> = Vec::with_capacity(n);
    for line in stdin.lines() {
        if let Ok(word) = line {
            words.push(word);
        }
        n -= 1;
        if n == 0 {
            break;
        }
    }

    for word in words {
        if word.len() > 10 {
            let first_char = word.chars().next().unwrap();
            let second_char = &word[word.len() - 1..];
            let l = word.len() - 2;
            let l_str = l.to_string();
            println!("{first_char}{l_str}{second_char}");
        } else {
            println!("{word}");
        }
    }
}
pub fn towers(towers: Vec<u32>) -> u32 {
    let mut tower_map: BTreeMap<u32, usize> = BTreeMap::new();
    let mut total_towers: u32 = 0;

    for tower in towers {
        if tower_map.len() == 0 {
            total_towers += 1;
            tower_map.insert(tower, 1);
        } else {
            let map_ref = tower_map.clone();
            let mut upper_bound_cursor = map_ref.lower_bound(Bound::Excluded(&tower));
            if upper_bound_cursor.peek_next().is_none() {
                total_towers += 1;
            } else {
                if let Some((key, _val)) = upper_bound_cursor.next() {
                    if let Some(val) = tower_map.get_mut(key) {
                        *val -= 1;
                        if *val == 0 {
                            tower_map.remove(key);
                        }
                    }
                };
            }
            tower_map
                .entry(tower)
                .and_modify(|val: &mut usize| {
                    *val += 1;
                })
                .or_insert(1);
        }
    }
    total_towers
}
fn minimize_dot_product(mut v: Vec<i32>, mut w: Vec<i32>) -> i32 {
    let mut sum = 0;
    v.sort();
    w.sort_by(|a, b| {
        if b > a {
            return std::cmp::Ordering::Greater;
        } else if b < a {
            return std::cmp::Ordering::Less;
        } else {
            return std::cmp::Ordering::Equal;
        }
    });
    for idx in 0..v.len() {
        let ele_1 = v.get(idx).unwrap();
        let ele_2 = w.get(idx).unwrap();
        sum += ele_1 * ele_2;
    }
    sum
}
fn solve(stdin: Stdin) {
    // let _n: usize = InputReader::read_input(Box::from(stdin.lock()));
    // let v: Vec<i32> = InputReader::read_input_vec(Box::new(stdin.lock()));
    // let w: Vec<i32> = InputReader::read_input_vec(Box::new(stdin.lock()));

    // let val = minimize_dot_product(v, w);

    // println!("{val}");

    // let v: String = InputReader::read_input(Box::new(stdin.lock()));
    // let mut stack: VecDeque<char> = VecDeque::new();
    // for char in v.chars() {
    //     if (stack.is_empty()) {
    //         stack.push_back(char);
    //     } else {
    //         let top_char: &char = stack.back().unwrap();
    //         if *top_char == char {
    //             stack.pop_back();
    //         } else {
    //             stack.push_back(char);
    //         }
    //     }
    // }
    // let ans: String = stack.iter().collect();
    // println!("{ans}");
    
}
fn main() {
    let std_in_obj = stdin();
    // let mut t: usize = InputReader::read_input(Box::new(std_in_obj.lock()));
    let mut t = 1;

    while t >= 1 {
        solve(stdin());
        t -= 1;
    }
}

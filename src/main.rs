#![feature(btree_cursors)]
#![allow(unused)]
use std::io::{Stdin, stdin};
use std::{collections::BTreeMap, ops::Bound};
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
                if let Some((key, val)) = upper_bound_cursor.next() {
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
fn solve(stdin: Stdin) {
    let mut buffer = String::from("");
    match stdin.read_line(&mut buffer) {
        Ok(_) => {}
        Err(error) => {
            panic!("{error:?}");
        }
    };
    let input = buffer.trim();
    let mut n = input.parse::<usize>().unwrap();
    let mut tower_height: Vec<u32> = Vec::with_capacity(n);
    for line in stdin.lines() {
        if let Ok(word) = line {
            tower_height.push(word.parse::<u32>().unwrap());
        }
        n -= 1;
        if n == 0 {
            break;
        }
    }
    let v = towers(tower_height);
    println!("{v}");
}
fn main() {
    let std_in_obj = stdin();
    let mut buffer = String::from("");
    match std_in_obj.read_line(&mut buffer) {
        Ok(_) => {}
        Err(error) => {
            panic!("{error:?}");
        }
    };
    let input = buffer.trim();

    let mut t = input.parse::<u32>().unwrap();
    // let mut t = 1;

    while t >= 1 {
        solve(stdin());
        t -= 1;
    }
}

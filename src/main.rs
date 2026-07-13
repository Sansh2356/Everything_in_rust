use std::io::{Stdin, stdin};
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
let my_boy = String::from("Hello world");

for word in words {
        if word.len() > 10 {
            let first_char = word.chars().next().unwrap();
            let second_char = &word[word.len() - 1..];
            let l = word.len() - 2;
            let l_str = l.to_string();
            println!("{first_char}{l_str}{second_char}");
        } else{ 
            println!("{word}");
        }
    }
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
    println!("All excution completed");
}

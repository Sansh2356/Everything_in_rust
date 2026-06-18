#![allow(unused)]
use std::collections::VecDeque;
use std::sync::{LazyLock, OnceLock};
use std::vec::Vec;
use std::{cell::RefCell, cell::UnsafeCell, ptr::NonNull};
const MOD: i32 = 1000000007;
/*
    if odd for b/power
    b is odd ----> a*(a)^b-1
    b is even ----> (a^b/2)^2

*/
fn binpow(base: i32, power: i32, prime: i32) -> i32 {
    if power == 0 {
        return 1;
    }
    if power % 2 != 0 {
        return ((base as i64 * binpow(base, power - 1, prime) as i64) % prime as i64) as i32;
    } else if (power % 2 == 0) {
        let temp: i32 = binpow(base, power / 2, prime);
        return ((temp as i64 * temp as i64) % prime as i64) as i32;
    } else {
        panic!("Not possible case !")
    };
}
/*
    (a*b)%M, a,b<=10e18
*/
fn binadd(base: i32, power: i32, prime: i32) -> i32 {
    if power == 0 {
        return 0;
    }
    let res = if power % 2 == 0 {
        (base + binadd(base, power - 1, prime)) % prime
    } else if (power % 2 != 0) {
        let temp: i32 = binadd(base, power / 2, prime);
        (temp + temp) % prime
    } else {
        panic!("Not possible case !")
    };
    res
}
/*
    computing inverse wrt to prime MODs via fermat's little theorem
    (a*a^p-2) % P = 1
    therefore (a*a^-1) % P = 1
    If p is a prime and p doesn´t divide a, then (a^p - 1) ≡ 1(mod p )
    a^-1 = a^p-2
    4 + 4 + 4 + 1 + 4 = 17 % 7  = 3
    During print in case of rust,C++ ((ans%MOD)+MOD)%MOD
    (a % m * b % m) % m
    (a % m - b % m + m) % m
    (a % m + b % m) % m
    b^e%m  = ((b%m)^e)% m
*/
fn computing_inverse(base: i32, prime: i32) -> i32 {
    binpow(base, prime - 2, prime)
}
fn factorial(number: u32) -> u32 {
    let mut prod = 1;
    for i in 1..(number + 1) {
        prod = (prod * i) % (MOD as u32);
    }
    return prod;
}
/*
    Direct method
    Table method
    Precede factorial

*/

thread_local! {
    static FACTORIAL:RefCell<[u32; 10001]> = RefCell::new([0u32; 10001]);

}
fn pre_compute_factorials() {
    let factorial_get_or_init = FACTORIAL.with_borrow_mut(|inner_value| {
        inner_value[0] = 1;
        let range = std::range::RangeInclusive {
            start: 1usize,
            last: 100usize,
        };

        for i in range {
            let computed_fact = ((inner_value[i - 1] as u64 * i as u64) % (MOD as u64)) as u32;
            inner_value[i as usize] = computed_fact;
        }
    });
}
fn get_fact(num: usize) -> u32 {
    let value = FACTORIAL.with_borrow(|inner_value| {
        return inner_value[num].to_owned();
    });
    value
}

fn compute_ncr(n: u32, c: u32, r: u32) -> u32 {
    //n!/(n-r)!r!
    let numerator = get_fact(n as usize) as u64;
    let denominator =
        (get_fact(r as usize) as u64 * get_fact((n - r) as usize) as u64) % (MOD as u64);
    let inverse_denominator = computing_inverse(denominator as i32, MOD) as u64;

    let ans = (numerator * inverse_denominator) % (MOD as u64);
    ans as u32
}
struct ArcData<T> {
    data: UnsafeCell<T>,
    weak_counter: usize,
    strong_counter: usize,
}

struct Arc<T> {
    pub ptr_to_data: NonNull<ArcData<T>>,
}
impl<T> Arc<T> {
    pub fn new(data: T) -> Self {
        let ptr_to_data = Box::new(ArcData {
            data: UnsafeCell::new(data),
            weak_counter: 1,
            strong_counter: 1,
        });
        Self {
            ptr_to_data: NonNull::from(Box::leak(ptr_to_data)),
        }
    }
}

#[test]
fn random_test() {
    pre_compute_factorials();
}

#[cfg(test)]
mod ncr_tests {
    use super::*;

    fn ncr(n: u32, r: u32) -> u32 {
        compute_ncr(n, 0, r)
    }

    #[test]
    fn computes_known_small_values() {
        pre_compute_factorials();

        assert_eq!(ncr(5, 2), 10);
        assert_eq!(ncr(6, 3), 20);
        assert_eq!(ncr(4, 2), 6);
        assert_eq!(ncr(7, 2), 21);
    }

    #[test]
    fn handles_edge_choices() {
        pre_compute_factorials();

        assert_eq!(ncr(5, 0), 1);
        assert_eq!(ncr(5, 5), 1);
        assert_eq!(ncr(8, 1), 8);
    }

    #[test]
    fn is_symmetric() {
        pre_compute_factorials();

        assert_eq!(ncr(9, 3), ncr(9, 6));
        assert_eq!(ncr(10, 4), ncr(10, 6));
    }
    #[test]
    fn random_test() {
        let u = binpow(2, 9, MOD);
        assert_eq!(u, 512);
    }
}

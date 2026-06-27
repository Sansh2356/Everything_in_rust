#include <climits>
#include <unordered_set>
#include <cmath>
#include <iomanip>
#include <set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// const int MOD = 1e9 + 7;
const int MOD = 1e9 + 7;
// Assuming a < b, log (min(a,b))
// With the help of if a <= b/2 then a % b < b/2 else if a > b/2 then a % b  = (a-b)
long long gcd(long long a, long long b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
long long lcm(long long a, long long b)
{
    return (a * b) / gcd(a, b);
}
// O(root(n)) for all num <= 1e12
bool is_prime(long long num)
{
    for (long long x = 2; x * x <= num; x++)
    {
        if (num % x == 0)
            return false;
    }
    return true;
}
// n <= 1e12
vector<long long> single_divisor(long long n)
{
    vector<long long> ans;
    for (long long x = 1; x * x <= n; x++)
    {
        if (n % x == 0)
        {
            ans.push_back(x);
            if (n / x != x)
            {
                ans.push_back(n / x);
            }
        }
    }
    return ans;
}

set<long long> cream_puff(long long n)
{
    set<long long> ans;
    for (long long x = 1; x * x <= n; x++)
    {
        if (n % x == 0)
        {
            ans.insert(x);
            if (n / x != x)
            {
                ans.insert(n / x);
            }
        }
    }
    return ans;
}
long long binpow(long long base, long long exponent, long long prime = MOD)
{
    if (exponent == 0)
        return 1;
    if (exponent % 2 != 0)
    {
        return (((base % prime) * (binpow(base, exponent - 1, prime) % prime)) % prime);
    }
    else
    {
        long long temp = binpow(base, exponent / 2, prime);
        return ((temp % prime) * (temp % prime)) % prime;
    }
}
long long binadd(long long base, long long exponent, long long prime = MOD)
{
    if (exponent == 0)
        return 0;
    if (exponent % 2 != 0)
    {
        return (((base % prime) + (binadd(base, exponent - 1, prime) % prime)) % prime);
    }
    else
    {
        long long temp = binadd(base, exponent / 2, prime);
        return ((temp % prime) + (temp % prime)) % prime;
    }
}
long long binpow_no_mod(long long base, long long exponent)
{
    if (exponent == 0)
        return 1;
    if (exponent % 2 != 0)
    {
        return ((base * (binpow(base, exponent - 1))));
    }
    else
    {
        long long temp = binpow(base, exponent / 2);
        return ((temp) * (temp));
    }
}
long long inverse(long long base, long long prime)
{
    return binpow(base, prime - 2, prime);
}
long long add(long long a, long long b, long long prime)
{
    return ((a % prime) + (b % prime)) % prime;
}
long long divide(long long a, long long b, long long prime)
{
    long long inv = inverse(b, prime);
    return ((a % prime) * (inv % prime)) % prime;
}
long long mul(long long a, long long b, long long prime)
{
    return ((a % prime) * (b % prime)) % prime;
}
long long subtract(long long a, long long b, long long prime)
{
    return (((a % prime) - (b % prime)) + prime) % prime;
}

long long fact[1000100];
long long inv_arr[1000100];
void factorial(long long prime)
{
    fact[0] = 1;
    for (long long i = 1; i <= 1000000; i++)
    {
        fact[i] = (fact[i - 1] * i) % prime;
    }
    inv_arr[1000000] = inverse(fact[1000000], prime);
    for (long long x = 1000000; x >= 1; x--)
    {
        inv_arr[x - 1] = (inv_arr[x] * x) % prime;
    }
}
// valide n<= 1e6
long long ncr(long long n, long long r, long long prime)
{
    long long numerator = fact[n];
    long long a = inv_arr[n - r];
    long long b = inv_arr[r];
    long long c = (a * b) % prime;
    return (numerator * c) % prime;
}
long long slower_ncr(long long n, long long r, long long prime)
{
    long long numerator = fact[n];
    long long denominator = ((fact[n - r] % prime) * (fact[r] % prime)) % prime;
    return ((numerator % prime) * (inverse(denominator, prime) % prime)) % prime;
}
long long table[1001][1001];
// valid for n<=1000
long long ncr_table(long long n, long long r, long long prime)
{
    // ncr = n-1cr-1 + n-1cr
    table[0][0] = 1;
    for (int x = 1; x <= n; x++)
    {
        for (int y = 0; y <= x; y++)
        {
            if (y == 0)
            {
                table[x][y] = (table[x - 1][y]) % prime;
            }
            else
            {
                table[x][y] = (table[x - 1][y] + table[x - 1][y - 1]) % prime;
            }
        }
    }
    return table[n][r];
}
// valid n <=1e9
int single_ncr(int n, int r)
{
    int num = 1, den = 1;
    for (int i = 1; i <= r; i++)
    {
        num = (num * (n - i + 1)) % MOD;
        den = (den * i) % MOD;
    }
    return (num * inverse(den, MOD)) % MOD;
}
long long dearrange[1000001];
// 10e6 O(N)
void dearrangement(long long n)
{
    dearrange[1] = 0;
    dearrange[2] = 1;

    for (long long x = 3; x <= n; x++)
    {
        dearrange[x] = ((x - 1) * (dearrange[x - 1] + dearrange[x - 2])) % MOD;
    }
}
long long npr(long long a, long long b, long long prime)
{
    long long n = fact[a];
    long long r = fact[(a - b)];
    long long dinv = inverse(r, prime);
    return (n * dinv) % MOD;
}
vector<vector<long long>> ncr_table_2(long long n, long long r, long long prime)
{
    vector<vector<long long>> local(31, vector<long long>(31, 0));
    // ncr = n-1cr-1 + n-1cr
    local[0][0] = 1;
    for (int x = 1; x <= n; x++)
    {
        for (int y = 0; y <= x; y++)
        {
            if (y == 0)
            {
                local[x][y] = (local[x - 1][y]) % prime;
            }
            else
            {
                local[x][y] = (local[x - 1][y] + local[x - 1][y - 1]) % prime;
            }
        }
    }
    return local;
}

bool cmp(pair<long long, long long> &p1, pair<long long, long long> &p2)
{
    if (p1.first == p2.first)
    {
        return p1.second < p2.second;
    }
    return p1.first > p2.first;
}

bool primes_arr[10000001];
// O(log log(N)) sigma N/p == 1/3+1/5+1/7 ...... *N
//  n<=10e7
void compute_primes()
{
    for (long long x = 2; x <= 10000000; x++)
    {
        primes_arr[x] = true;
    }
    primes_arr[1] = false;
    for (long long x = 2; x <= 10000000; x++)
    {
        if (primes_arr[x] == true)
        {
            for (long long y = x * x; y <= 10000000; y += x)
            {
                primes_arr[y] = false;
            }
        }
    }
}
void slow_compute_primes()
{
    for (long long x = 2; x <= 1000; x++)
    {
        primes_arr[x] = true;
    }
    primes_arr[1] = false;
    for (long long x = 2; x <= 1000; x++)
    {
        if (primes_arr[x] == true)
        {
            for (long long y = 2 * x; y <= 1000; y += x)
            {
                primes_arr[y] = false;
            }
        }
    }
}
// b>a and finding primes within the range [a,b]
// finding in a complexity of O((b-a)log log b)
vector<long long> segmeneted_sieve(long long a, long long b)
{
    // Finding primes within the range of [1,root(b)] using normal sieve
    // giving out time complexity of O(root(b)log(log(root(b))))
    vector<long long> local_sieve;
    for (long long x = 1; x * x <= b; x++)
    {
        if (primes_arr[x] == true)
        {
            local_sieve.push_back(x);
        }
    }
    // Initially marking every prime within the range as true.
    vector<bool> res(b - a + 1, true);
    if (a == 1)
    {
        res[0] = false;
    }
    // Then for each prime in range of [1,root(b)] we can compute
    // all its multiples and those will be composite except if the
    // number within the range if equal to prime itself.
    for (long long x = 0; x < local_sieve.size(); x++)
    {
        long long curr_prime = local_sieve[x];
        // First multiple of prime > a
        long long rem = a % curr_prime;
        long long first_multiple = -1;
        if (rem == 0)
        {
            first_multiple = a;
        }
        else
        {
            long long temp = (a - rem) + curr_prime;
            first_multiple = temp;
        }
        while (first_multiple <= b)
        {
            // Making sure if we are iterating multiples of prime itself then leave
            if (first_multiple != curr_prime)
            {
                // Factor of prime therefore a composite number
                res[first_multiple - a] = false;
            }
            // Moving to next multiple of curr_prime
            first_multiple += curr_prime;
        }
    }
    vector<long long> v;
    for (long long x = 0; x < res.size(); x++)
    {
        if (res[x] == true)
        {
            v.push_back(a + x);
        }
    }
    return v;
}

long long factors[1000001];
// log n factors n<=10e7

void build_spf(long long n)
{
    for (int x = 2; x <= n; x++)
    {
        factors[x] = x;
    }
    for (int x = 2; x <= n; x++)
    {
        // Meaning it is a prime num
        if (factors[x] == x)
        {
            // Moving on its multiples and marking it the smallest
            for (int y = 2 * x; y <= n; y += x)
            {
                if (factors[y] == y)
                {
                    factors[y] = x;
                }
            }
        }
    }
}
// O(log n) n<=10e7
unordered_map<long long, long long> compute_factors(long long num)
{
    unordered_map<long long, long long> ans;
    while (num >= 2 && factors[num] != num)
    {
        ans[factors[num]]++;
        num /= factors[num];
    }
    if (num != 1)
    {
        ans[num]++;
    }
    return ans;
}
// n<=10e12
vector<pair<long long, long long>> Factors(long long x)
{
    vector<pair<long long, long long>> ans;
    for (long long i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            int cnt = 0;
            while (x % i == 0)
            {
                cnt++;
                x /= i;
            }
            ans.push_back({i, cnt});
        }
    }
    if (x > 1)
        ans.push_back({x, 1});
    return ans;
}

// Sum of divisors and number of divisors and euler totient function
long long euler_arr[10000001];
/*
    co primes within the range of [1,x]
    will follow the closed relation as x*(1-1/p1)*(1-1/p2)....(1-1/pk)
    where x can be represented as the product of prime factors

    x = p1^a1*p2^a2....pk^ak. O(log log(x)).prod*(it.second + 1)

    Sum of divisors = (p1^(a1+1)-1/p1-1)*(p2^(a2+1)-1/p2-1)....
    Number of divisors = (a1+1)*(a2+1)....*(an+1)
    Product of divisors = product(pi^(ai*(number of divisors)/2))

    totient(xy) = totient(x)*totient(y) provided that gcd(x,y)=1 i.e. both are co-primes wrt to each other.
    totient(x) = x-1 if x is a prime num
    n<=10e7
*/
void compute_co_prime()
{
    for (long long x = 1; x <= 10000000; x++)
    {
        euler_arr[x] = x;
    }
    for (long long x = 2; x <= 10000000; x++)
    {
        if (primes_arr[x] == true)
        {
            for (long long y = x; y <= 10000000; y += x)
            {
                euler_arr[y] -= euler_arr[y] / x;
            }
        }
    }
}
// n<=10e7
long long number_of_divisors(long long num)
{
    unordered_map<long long, long long> freq = compute_factors(num);
    long long prod = 1;
    for (auto it : freq)
    {
        cout << it.first << " " << it.second << endl;
        prod = (prod * (it.second + 1));
    }
    cout << "OVER" << endl;
    return prod;
}
/*
    a^x mod(m) = (a^(x%totient(m)))%m where x and m are co-prime the given is euler's theorem
    n<=10e7
*/
long long sum_of_divisors(long long num)
{
    /*
        sum(n) = p1^ax+1-1/p-1+.....
    */
    long long ans = 1;
    unordered_map<long long, long long> m = compute_factors(num);
    for (auto it : m)
    {
        long long factor = it.first;
        long long power = it.second;
        long long numerator = binpow(factor, power + 1, MOD) - 1;
        long long denominator = factor - 1;
        long long dinv = inverse(denominator, MOD);
        ans *= ((numerator * dinv) % MOD);
    }
    return ans;
}
// n<=10e7
long long product_of_divisors(long long num)
{
    /*
        Product of divisors = product(pi^(ai*(number of divisors)/2))
    */
    long long ans = 1;
    unordered_map<long long, long long> m = compute_factors(num);
    long long num_divisors = number_of_divisors(num);
    for (auto it : m)
    {
        long long power = (it.second * num_divisors) / 2;
        long long val = binpow(it.first, power, MOD);
        ans = (ans * val) % MOD;
    }
    return ans;
}

void rec(string &s, long long idx, vector<string> &ans)
{
    if (idx >= s.length())
    {
        ans.push_back(s);
        return;
    }
    else
    {
        if (s[idx] != '?')
        {
            rec(s, idx + 1, ans);
        }
        else
        {
            s[idx] = '+';
            rec(s, idx + 1, ans);
            s[idx] = '-';
            rec(s, idx + 1, ans);
            s[idx] = '?';
        }
    }
}
/*
    Power of P in N! = floor(N/p)+floor(N/p^2) .... floor(N/P^k)
    y = min (floor{f(N,pi)/ai}) for all factors of x for finding the maximum power of a number X^a in a factorial f
    O(logp(N)) so approximately log
    O(root(x)+log(x)*log(n))
*/
// for x <=10e18
long long maximum_power(long long x, long long factorial_value)
{
    // O(root(X))
    vector<pair<long long, long long>> factors = Factors(x);
    // O(log(X))
    long long ans = INT_MAX;
    for (auto factor : factors)
    {
        long long fact = factor.first;
        long long max_power = factor.second;
        long long power_counter = 1;
        long long initial_value = floor(factorial_value / binpow(fact, power_counter, MOD));
        long long running_sum = initial_value;
        while (1)
        {
            power_counter++;
            if (power_counter > max_power)
                break;
            initial_value = floor(factorial_value / binpow(fact, power_counter, MOD));
            if (initial_value <= 0)
                break;
            running_sum += initial_value;
        }
        ans = min(ans, (long long)floor(running_sum / max_power));
    }
    return ans;
}
long long GET(long long n, long long m)
{
    long long q = n / m;
    long long r = n % m;

    long long cycle = (((m % MOD) * ((m - 1) % MOD)) % MOD * inverse(2, MOD)) % MOD;
    long long rem = (((r % MOD) * ((r + 1) % MOD)) % MOD * inverse(2, MOD)) % MOD;

    return (((q % MOD) * cycle) % MOD + rem) % MOD;
}
// Harmonic lemma,from which: O(root(n))
long long harmonic_lemma_value(long long n, long long m)
{

    long long last_item_in_range = -1;
    long long ans = 0;
    for (long long x = 1; x <= n; x = last_item_in_range + 1)
    {
        long long deno = (n / x);
        last_item_in_range = (n / deno);
        long long total_items = (last_item_in_range - x + 1);
        ans = (ans + (((total_items % MOD) * (binpow(deno, m, MOD) % MOD)) % MOD)) % MOD;
    }
    return ans % MOD;
}
long long atc_144(long long num)
{
    long long mini = 1e12;
    for (long long x = 1; x * x <= num; x++)
    {
        if (num % x == 0)
        {
            long long local = 0;
            local += (x - 1);
            if (num / x != x)
            {
                local += ((num / x) - 1);
            }
            else
            {
                local += ((num / x) - 1);
            }
            mini = min(mini, local);
        }
    }
    return mini;
}

int maxProfit(vector<int> &inventory, int orders)
{
}
class RandomClass
{
public:
    multiset<long long> m1;
    multiset<long long> rest;
    long long curr_sum;
    long long capacity;
    RandomClass(long long cap)
    {
        this->curr_sum = 0;
        this->capacity = cap;
    }
    void add(long long num)
    {
        if (m1.size() >= capacity)
        {
            long long smallest = *(m1.begin());
            if (smallest < num)
            {
                m1.erase(m1.begin());
                curr_sum -= smallest;
                m1.insert(num);
                curr_sum += num;
                rest.insert(smallest);
            }
            else
            {

                rest.insert(num);
            }
        }
        else
        {
            m1.insert(num);
            curr_sum += num;
        }
    }
    void remove(long long x)
    {
        if (m1.count(x))
        {
            m1.erase(m1.find(x));
            curr_sum -= x;
            if (rest.size() >= 1)
            {
                long long next_replacement = *(rest.rend());
                rest.erase(rest.find(next_replacement));
                m1.insert(next_replacement);
                curr_sum += next_replacement;
            }
        }
        else if (rest.count(x) == true)
        {
            rest.erase(rest.find(x));
        }
    }
    long long query()
    {
        return curr_sum;
    }
};
/*
    n+k-1ck-1
*/
long long expr_val(string expr_3)
{
    if (expr_3 == "")
        return 0;
    long long expr_3_val = 0;
    vector<long long> nums;
    long long start_idx = -1;
    if (expr_3[0] == '-')
    {
        string local = "";
        for (int x = 1; x < expr_3.size(); x++)
        {
            if (expr_3[x] == '+' || expr_3[x] == '-')
            {
                start_idx = x;
                break;
            }
            else
            {
                local.push_back(expr_3[x]);
            }
        }
        nums.push_back(stoi(local) * -1);
    }
    else if (expr_3[0] == '+')
    {
        string local = "";
        for (int x = 1; x < expr_3.size(); x++)
        {
            if (expr_3[x] == '+' || expr_3[x] == '-')
            {
                start_idx = x;
                break;
            }
            else
            {
                local.push_back(expr_3[x]);
            }
        }
        nums.push_back(stoi(local));
    }
    else
    {
        string local = "";
        for (int x = 0; x < expr_3.size(); x++)
        {
            if (expr_3[x] == '+' || expr_3[x] == '-')
            {
                start_idx = x;
                break;
            }
            else
            {
                local.push_back(expr_3[x]);
            }
        }
        nums.push_back(stoi(local));
    }
    string local = "";
    for (int x = start_idx; x < expr_3.size(); x++)
    {
        if (expr_3[x] == '+' && local.size() != 0)
        {
            string local_sub = local.substr(1, local.size());
            if (local[0] == '+')
            {
                nums.push_back(stoi(local_sub));
            }
            else if (local[0] == '-')
            {
                nums.push_back(stoi(local_sub) * -1);
            }
            local = "";
        }
        else if (expr_3[x] == '-' && local.size() != 0)
        {
            string local_sub = local.substr(1, local.size());
            if (local[0] == '+')
            {
                nums.push_back(stoi(local_sub));
            }
            else if (local[0] == '-')
            {
                nums.push_back(stoi(local_sub) * -1);
            }
            local = "";
        }
        local.push_back(expr_3[x]);
    }
    if (local[0] == '+')
    {
        string local_sub = local.substr(1, local.size());
        nums.push_back(stoi(local_sub));
    }
    else if (local[0] == '-')
    {
        string local_sub = local.substr(1, local.size());
        nums.push_back(stoi(local_sub) * -1);
    }

    for (auto num : nums)
    {
        expr_3_val += num;
    }
    return expr_3_val;
}
void solve()
{
    // string s;
    // cin >> s;
    // long long x_pos = -1;
    // long long equal_pos = -1;
    // char x_coeff = ' ';
    // for (int x = 0; x < s.size(); x++)
    // {
    //     if (s[x] == 'X')
    //         x_pos = x;
    //     else if (s[x] == '=')
    //         equal_pos = x;
    // }
    // if (x_pos == 0)
    // {
    //     x_coeff = '+';
    // }
    // else if (s[x_pos - 1] == '=')
    // {
    //     x_coeff = '+';
    // }
    // else
    // {
    //     x_coeff = s[x_pos - 1];
    // }
    // string expr_1 = "";
    // string expr_2 = "";
    // string expr_3 = "";
    // if (x_pos > equal_pos)
    // {
    //     for (int x = equal_pos + 1; x <= x_pos - 1; x++)
    //     {
    //         expr_1.push_back(s[x]);
    //     }
    //     if (x_pos != equal_pos + 1)
    //     {
    //         expr_1.pop_back();
    //     }
    //     for (int x = x_pos + 1; x < s.size(); x++)
    //     {
    //         expr_2.push_back(s[x]);
    //     }
    //     for (int x = 0; x <= equal_pos - 1; x++)
    //     {
    //         expr_3.push_back(s[x]);
    //     }
    // }
    // else
    // {
    //     for (int x = 0; x <= x_pos - 1; x++)
    //     {
    //         expr_1.push_back(s[x]);
    //     }
    //     if (x_pos != 0)
    //     {
    //         expr_1.pop_back();
    //     }
    //     for (int x = x_pos + 1; x <= equal_pos - 1; x++)
    //     {
    //         expr_2.push_back(s[x]);
    //     }
    //     for (int x = equal_pos + 1; x < s.size(); x++)
    //     {
    //         expr_3.push_back(s[x]);
    //     }
    // }
    // long long expr1_val = expr_val(expr_1);
    // long long expr2_val = expr_val(expr_2);
    // long long expr3_val = expr_val(expr_3);

    // long long expr_cum = expr1_val + expr2_val;
    // long long expr_total = expr3_val + (-1 * expr_cum);

    // if (x_coeff == '-')
    // {
    //     expr_total *= -1;
    // }
    // cout << "Expr 1 " << expr_1 << " " << expr1_val << endl;
    // cout << "Expr 2 " << expr_2 << " " << expr2_val << endl;
    // cout << "Expr 3 " << expr_3 << " " << expr3_val << endl;
    // cout << "Coefficient of x - " << x_coeff << endl;
    // cout << "FINAL ANS " << expr_total << endl;
    // cout << expr_total << endl;
    // long long n, m;
    // cin >> n >> m;
    // if (m < n)
    // {
    //     cout << 0 << endl;
    //     return;
    // }
    // m -= n;
    // long long num = (m + n - 1);
    // long long r = n - 1;

    // cout << ncr(num, r, MOD)%MOD << endl;

    // long long n;
    // cin >> n;
    // long long a = binpow(26, n, MOD);
    // long long b = binpow(5, n, MOD);
    // long long c = binpow(21, n, MOD);
    // cout << (((((a - b) + MOD) % MOD) - c) + MOD) % MOD << endl;
    // long long a, b, c, d, e, f, g, h;
    // cin >> a >> b >> c >> d >> e >> f >> g >> h;

    // long long val_1 = (binpow(a, b, MOD));
    // long long val_2 = c;
    // long long val_2_1 = ((((val_1 - val_2) + MOD) % MOD) * e) % MOD;
    // long long val_3 = d;
    // long long val_4_first = (g * h) %( MOD-1);
    // long long val_4_second = binpow(f, val_4_first, MOD);
    // long long val_4 = (val_4_second * e) % MOD;

    // long long p_first = ((val_2_1 - d) + MOD) % MOD;
    // long long p = (p_first + val_4) % MOD;

    // long long q = e;
    // long long q_inverse = inverse(q, MOD);
    // long long ans = (p * q_inverse) % MOD;
    // cout << ans << endl;

    // long long n, k;
    // cin >> n >> k;
    // long long a = binpow(k - 1, n-1, MOD);
    // long long ans = (k * a) % MOD;
    // cout << ans << endl;
    // cout<<(n*(n+1))/2<<endl;
    long long q, k;
    cin >> q >> k;

    RandomClass *obj = new RandomClass(k);
    while (q--)
    {
        long long q_type;
        long long num;
        cin >> q_type;
        if (q_type == 1)
        {
            cin >> num;
            obj->add(num);
        }
        else if (q_type == 2)
        {
            cin >> num;
            obj->remove(num);
        }
        else
        {
            char ch;
            cin >> ch;
            long long query_ans = obj->query();
            cout << query_ans << endl;
        }
    }

    // unordered_map<long long, long long> m;
    // long long n;
    // cin >> n;
    // vector<long long> v(n);
    // bool flag = true;
    // long long gcd_total = -1;
    // for (int x = 0; x < n; x++)
    // {
    //     long long num;
    //     cin >> num;
    //     v[x] = num;
    //     unordered_map<long long, long long> facts = compute_factors(num);
    //     for (auto it : facts)
    //     {
    //         if (m.count(it.first) == true)
    //         {
    //             flag = false;
    //         }
    //         m[it.first]++;
    //     }
    //     if (x >= 2)
    //     {
    //         gcd_total = gcd(gcd_total, v[x]);
    //     }
    //     else if (x == 1)
    //     {
    //         gcd_total = gcd(v[0], v[1]);
    //     }
    // }
    // if (flag == true)
    // {
    //     cout << "pairwise coprime" << endl;
    // }
    // else if (gcd_total == 1)
    // {
    //     cout << "setwise coprime" << endl;
    // }
    // else
    // {
    //     cout << "not coprime" << endl;
    // }

    // long long n, m;
    // cin >> n >> m;
    // vector<long long> v(1e6);
    // for (int x = 1; x <= m; x++)
    // {
    //     v[x] = x;
    // }
    // vector<long long> v2(n);
    // for (int x = 0; x < n; x++)
    // {
    //     long long num;
    //     cin >> num;
    //     v2[x] = num;
    // }
    // for (int x = 0; x < n; x++)
    // {
    //     unordered_map<long long, long long> m2 = compute_factors(v2[x]);
    //     for (auto factor : m2)
    //     {
    //         if (v[factor.first] != -1)
    //         {

    //             for (long long y = factor.first; y <= m; y += factor.first)
    //             {
    //                 v[y] = -1;
    //             }
    //         }
    //     }
    // }
    // long long cnt = 0;
    // for (long long x = 1; x <= m; x++)
    // {
    //     if (v[x] != -1)
    //     {
    //         cnt++;
    //     }
    // }
    // cout << cnt << endl;
    // for (long long x = 1; x <= m; x++)
    // {
    //     if (v[x] != -1)
    //     {
    //         cout << x << endl;
    //     }
    // }

    // long long n;
    // cin >> n;
    // vector<long long> v(n);
    // unordered_map<long long, unordered_set<long long>> st;
    // for (long long x = 0; x < n; x++)
    // {
    //     long long num;
    //     cin >> num;
    //     v[x] = num;
    //     st[num].insert(x);
    // }
    // long long cnt = 0;
    // for (long long x = 0; x < n; x++)
    // {
    //     long long num = v[x];
    //     vector<long long> divs = single_divisor(num);

    //     for (auto divisor : divs)
    //     {
    //         if (st.count(divisor) == true && st[divisor].size() > 1)
    //         {
    //             cnt++;
    //             break;
    //         }
    //         else if (st.count(divisor) == true && st[divisor].size() == 1)
    //         {
    //             if (st[divisor].count(x) == false)
    //             {
    //                 cnt++;
    //                 break;
    //             }
    //         }
    //     }
    // }
    // cout << n-cnt << endl;

    // long long n;
    // cin >> n;
    // cout << atc_144(n) << endl;

    // N^2*10^d
    // N*10d
    // long long n, d;
    // cin >> n >> d;
    // vector<pair<long long, long long>> fact = Factors(n);
    // unordered_map<long long, long long> m;
    // for (auto it : fact)
    // {
    //     long long base = it.first;
    //     long long exponent = it.second;
    //     m[base] = 2 * exponent;
    // }
    // m[2] += 2 * d;
    // m[5] += 2 * d;
    // long long ans = 1;
    // bool flag = true;
    // for (auto it : m)
    // {
    //     if (it.second % 2 != 0)
    //     {
    //         flag = false;
    //     }
    //     ans = ((ans % MOD) * (it.second + 1)) % MOD;
    // }
    // ans = ans * 2;
    // if (flag == true)
    // {
    //     cout << ((ans - 1) + MOD) % MOD << endl;
    // }
    // else
    // {
    //     cout << ans % MOD << endl;
    // }

    // long long l, r, m;
    // cin >> l >> r >> m;
    // long long value_1 = GET(l - 1, m);
    // long long value_2 = GET(r, m);
    // cout << ((value_2 - value_1) + MOD) % MOD << endl;
    // long long n;
    // cin >> n;
    // vector<pair<long long, long long>> factors = Factors(n);
    // long long ans = n;
    // // 1-1/p = p-1*(p-2)* .....
    // // denom = p1*p2*p3 ......

    // for (auto it : factors)
    // {
    //     ans /= it.first;
    //     ans *= (it.first - 1);
    // }
    // cout << ans << endl;

    // vector<long long> input(n);
    // for (int x = 0; x < n; x++)
    // {
    //     cin >> input[x];
    //     long long root = sqrtl(input[x]);
    //     long long mul = (root * root);
    //     if (mul != input[x])
    //     {
    //         cout<<"NO"<<endl;
    //         continue;
    //     }
    //     else
    //     {
    //         if (primes_arr[root] == true)
    //         {
    //             cout << "YES" << endl;
    //         }
    //         else{
    //             cout<<"NO"<<endl;
    //         }
    //     }
    // }

    // long long n;
    // cin >> n;
    // vector<long long> ans = compute_factors(n);
    // for (auto num : ans)
    // {
    //     cout << num << " ";
    // }
    // cout << endl;

    // long long a, b;
    // cin >> a >> b;
    // vector<long long> v = segmeneted_sieve(a, b);
    // cout << v.size() << endl;
    // for (long long x = 0; x < v.size(); x++)
    // {
    //     cout << v[x] << " ";
    // }

    // string s1, s2;
    // cin >> s1 >> s2;
    // long long f_plus = 0;
    // long long f_minus = 0;
    // for (auto ch : s1)
    // {
    //     if (ch == '+')
    //         f_plus++;
    // }
    // f_minus = (s1.size() - f_plus);
    // vector<string> ans;
    // rec(s2, 0, ans);
    // long double cnt = 0;
    // for (auto st : ans)
    // {
    //     long double a = 0;
    //     long double b = 0;
    //     for (auto ch : st)
    //     {
    //         if (ch == '+')
    //             a++;
    //         else
    //         {
    //             b++;
    //         }
    //     }
    //     if (a == f_plus && b == f_minus)
    //         cnt++;
    // }
    // cout << fixed << setprecision(12) << (cnt / (long double)ans.size()) << endl;
    // long long n;
    // cin >> n;
    // vector<long long> a(n, 0);
    // for (int x = 0; x < n; x++)
    // {
    //     long long i;
    //     cin >> i;
    //     a[x] = i;
    // }
    // if (n == 1)
    // {
    //     cout << "YES" << endl;
    //     return;
    // }
    // long long initial_gcd = gcd(a[0], a[1]);
    // for (int x = 2; x < n; x++)
    // {
    //     initial_gcd = gcd(initial_gcd, a[x]);
    // }
    // if (initial_gcd >= 2)
    // {
    //     cout << "YES" << endl;
    // }
    // else
    // {
    //     cout << "NO" << endl;
    // }
    // long long n;
    // cin >> n;
    // vector<long long> divs = single_divisor(n);
    // cout<<divs.size()<<endl;
    // if (is_prime(n))
    // {
    //     cout << "YES" << endl;
    // }
    // else
    // {
    //     cout << "NO" << endl;
    // }
    // long long m;
    // cin >> m;
    // vector<long long> a(m);
    // vector<pair<long long, long long>> v;
    // for (long long x = 0; x < m; x++)
    // {
    //     long long num;
    //     cin >> num;
    //     a[x] = num;
    // }
    // for (long long x = 0; x < m; x++)
    // {
    //     long long num;
    //     cin >> num;
    //     v.push_back({num, x});
    // }
    // sort(a.begin(), a.end());
    // sort(v.begin(), v.end(),cmp);
    // long long cnt = 0;
    // vector<long long> ans(m, 0);
    // for (auto pair : v)
    // {
    //     long long idx = pair.second;
    //     ans[idx] = a[cnt];
    //     cnt++;
    // }
    // for (auto num : ans)
    // {
    //     cout << num << " ";
    // }
    // cout << endl;

    // long long n;
    // cin >> n;
    // string s = "";
    // cin >> s;
    // string prefix = "";
    // string suffix = "";
    // for (int x = 0; x < n; x++)
    // {
    //     if (prefix.size() == 0)
    //     {
    //         prefix.push_back(s[x]);
    //     }
    //     else
    //     {
    //         if (prefix[prefix.size() - 1] == s[x])
    //         {
    //             prefix.push_back(s[x]);
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }
    // }
    // for (int x = (n - 1); x >= 0; x--)
    // {
    //     if (suffix.size() == 0)
    //     {
    //         suffix.push_back(s[x]);
    //     }
    //     else
    //     {
    //         if (suffix[suffix.size() - 1] == s[x])
    //         {
    //             suffix.push_back(s[x]);
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }
    // }
    // if (prefix == suffix && prefix.size() == suffix.size() && prefix.size() == n)
    // {
    //     long long a = (n * (n + 1)) % MOD;
    //     long long b = inverse(2, MOD);
    //     cout << (((a * b) % MOD)) << endl;
    // }
    // else
    // {
    //     if (prefix[0] != suffix[0])
    //     {
    //         cout << (prefix.size() + suffix.size() + 1) << endl;
    //     }
    //     else
    //     {
    //         cout << ((prefix.size() + 1) * (suffix.size() + 1)) % MOD << endl;
    //     }
    // }
    // long long k;
    // cin >> k;
    // // 4^2^k-2
    // long long b = binpow(2, k, MOD - 1);
    // long long c = binpow(4, b - 2, MOD);
    // cout << (6 * c) % MOD << endl;

    // long long a;
    // cin >> a;
    // if (a == 1)
    // {
    //     cout << 1 << endl;
    //     return;
    // }
    // cout << ((6 * a * (a - 1)) + 1) << endl;
    // long long x1, y1, x2, y2;
    // cin >> x1 >> y1 >> x2 >> y2;

    // long long a = abs(x2 - x1);
    // long long b = abs(y2 - y1);

    // long long c = a * a;
    // long long d = b * b;

    // cout << setprecision(10) << sqrtl(c + d) << endl;
    // long long l, r, m;
    // cin >> l >> r >> m;
    // long long ans = binadd(l, l + 1, m);
    // for (int x = l + 2; x <= r; x += 1)
    // {
    //     ans = binadd(ans, x, m);
    // }
    // cout << ans << endl;
    // long long n;
    // cin>>n;
    // vector<vector<long long>> v = ncr_table_2(30, 30, MOD);
    // for (auto arr : v)
    // {
    //     if(n <=0)break;
    //     for (auto num : arr)
    //     {
    //         if (num == 0)
    //             continue;
    //         else
    //         {

    //             cout << num << " ";
    //         }
    //     }
    //     cout << endl;
    //     n--;
    // }
    // long long a, b;
    // cin >> a >> b;
    // cout << ncr(a, b, MOD) << " " << npr(a, b, MOD) << endl;

    // long long a, b;
    // cin >> a >> b;
    // long long lc = lcm(a, b);
    // long long gd = gcd(a, b);
    // cout << gd << " " << lc << endl;
    // long long n;
    // cin >> n;
    // vector<long long> v = single_divisor(n);
    // long long ans = 0;
    // for (auto num : v)
    // {
    //     ans += num;
    // }
    // cout << ans << endl;
    //  long long n, m;
    //     cin >> n >> m;

    //     long long kmax = -1;
    //     long long kmin = INT_MAX;

    //     kmax = ((n - m) * (n - m + 1)) / 2;

    //     long long rem = n % m;
    //     long long a = (n - rem) / m;

    //     if (rem == 0)
    //     {
    //         kmin = m * ((a * (a - 1)) / 2);
    //     }
    //     else
    //     {
    //         kmin = (m - rem) * ((a * (a - 1)) / 2);

    //         long long extraGroupPairs = ((a + 1) * a) / 2;
    //         kmin += rem * extraGroupPairs;
    //     }

    //     cout << kmin << " " << kmax << endl;
    // int n, k;
    // cin >> n >> k;
    // string s;
    // cin >> s;
    // unordered_set<char> st;
    // for (int i = 0; i < k; i++)
    // {
    //     char c;
    //     cin >> c;
    //     st.insert(c);
    // }
    // long long count = 0;
    // int l = 0, r = 0;
    // while (r < n)
    // {
    //     if (st.count(s[r]))
    //     {
    //         r++;
    //     }
    //     else
    //     {
    //         long long len = r - l;
    //         count += len * (len + 1) / 2;
    //         r++;
    //         l = r;
    //     }
    // }
    // long long len = r - l;
    // count += len * (len + 1) / 2;
    // cout << count << endl;
    // long long n;
    // cin >> n;
    // n--;
    // long long num1, num2, num3;
    // long long n1 = floor(n / 3);
    // long long n2 = floor(n / 5);
    // long long n3 = floor(n / 15);

    // long long sum1 = 3 * ((n1 * (n1 + 1)) / 2);
    // long long sum2 = 5 * ((n2 * (n2 + 1)) / 2);
    // long long sum3 = 15 * ((n3 * (n3 + 1)) / 2);
    // cout << ((sum1 + sum2) - sum3) << endl;

    // long long n, k;
    // cin >> n >> k;
    // // n-2 a and 2 b
    // string ans = "";
    // for (int x = 0; x < n; x++)
    // {
    //     ans.push_back('a');
    // }
    // long long total = 0;
    // for (int x = (n - 2); x >= 0; x--)
    // {
    //     // (n-2) which is the maximums rightmost postion of leftmost 'b'
    //     // then the right most positions can contribute to atmost  (n-(x+1)) types of different strings
    //     // then we can say that if k is the kth smalles lexicographical string then k <= count of strings till now .
    //     // then fix the position of the leftmost b str[x]='b', then we have to find the rightmost position of 'b'.
    //     long long curr_contribution = 0;
    //     curr_contribution = (n - (x + 1));
    //     // 3
    //     long long temp = total;
    //     // 6
    //     total += curr_contribution;
    //     if (total >= k)
    //     {
    //         ans[x] = 'b';
    //         long long idx = (n - (k - temp));
    //         ans[idx] = 'b';
    //         cout << ans << endl;
    //         return;
    //     }
    // }
    // long long n;
    // cin >> n;
    // // 3^3n-7^n
    // long long component = (3 * n) % MOD;
    // long long pow_1 = binpow(3, component, MOD);
    // long long pow_2 = binpow(7, n, MOD);

    // long long ans = (((pow_1 % MOD) - (pow_2 % MOD)) + MOD) % MOD;
    // cout << ans << endl;

    // long long n;
    // cin >> n;
    // long long ans = binpow(2, n, MOD);
    // cout << (ans % MOD) << endl;

    // long long n;
    // cin >> n;
    // long long ans = 0;
    // for (long long x = 1; x <= n; x++)
    // {
    //     ans = (ans + binpow(2, x)) % MOD;
    // }
    // cout << ans << endl;

    // long long n;
    // cin >> n;
    // vector<long long> v(n);
    // unordered_map<long long, long long> m;
    // for (long long x = 0; x < v.size(); x++)
    // {
    //     long long num;
    //     cin >> num;
    //     v[x] = num;
    //     m[num]++;
    // }
    // sort(v.begin(), v.end());
    // long long diff = v[v.size() - 1] - v[0];
    // long long n1 = m[v[v.size() - 1]];
    // if (diff == 0)
    // {
    //     cout << diff << " " << (n * (n - 1)) / 2 << endl;
    //     return;
    // }
    // long long n2 = m[v[0]];
    // long long ans = n1 * n2;
    // cout << diff << " " << ans << endl;
    // string s;
    // cin >> s;
    // char ch1 = s[0];
    // char ch2 = s[1];
    // int num1 = 26 - ('z' - ch1);
    // int num2 = 26 - ('z' - ch2);
    // int offset = (num1 - 1) * 25;
    // int rank = 0;
    // if (num2 > num1)
    // {
    //     rank = offset + (num2 - 1);
    // }
    // else
    // {
    //     rank = offset + num2;
    // }
    // cout << rank << endl;
    // long long n, m;
    // cin >> n >> m;
    // long long final = ncr((n + m), n, MOD);
    // cout << final << endl;

    // long long n;
    // cin >> n;
    // long long num1 = (n * (n - 1)) % MOD;
    // long long num2 = (num1 * (n - 2)) % MOD;
    // long long num3 = (num3 * (n - 3)) % MOD;
    // long long deno = 24;
    // long long dinv = inverse(deno, MOD);
    // long long ans = (num3 * dinv) % MOD;
    // long long n;
    // cin >> n;
    // dearrangement(n);
    // long long ans = dearrange[n];
    // cout << ans % MOD << endl;

    // long long n;
    // cin >> n;
    // for (int x = 1; x <= 32; x++)
    // {
    //     if (((1 << x) & n) == n)
    //     {
    //         cout << "YES" << endl;
    //         return;
    //     }
    // }
    // cout << "NO" << endl;

    //     long long x1, y1, x2, y2, x3, y3, x4, y4;
    //     cin >> x1 >> y1 >> x2 >> y2;
    //     cin >> x3 >> y3 >> x4 >> y4;

    //     long long center_1_x = (x1 + x2) * 2;
    //     long long center_1_y = (y1 + y2) * 2;

    //     pair<long long, long long> center1 = {center_1_x, center_1_y};

    //     long long center_2_x = (x3 + x4) * 2;
    //     long long center_2_y = (y3 + y4) * 2;

    //     pair<long long, long long> center2 = {center_2_x, center_2_y};

    //     long long dist_1 = (((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
    //     long long dist_2 = (((x3 - x4) * (x3 - x4)) + ((y3 - y4) * (y3 - y4)));

    //     long long dist = (((center1.first - center2.first) * (center1.first - center2.first)) + ((center1.second - center2.second) * (center1.second - center2.second)));
    //     dist = sqrt(dist);

    //     long long radius_1 = sqrt(dist_1) * 2;
    //     long long radius_2 = sqrt(dist_2) * 2;
    // cout << "center_1_x = " << center_1_x << '\n';
    // cout << "center_1_y = " << center_1_y << '\n';
    // cout << "center_2_x = " << center_2_x << '\n';
    // cout << "center_2_y = " << center_2_y << '\n';

    // cout << "center1.first = " << center1.first << '\n';
    // cout << "center1.second = " << center1.second << '\n';

    // cout << "center2.first = " << center2.first << '\n';
    // cout << "center2.second = " << center2.second << '\n';

    // cout << "dist_1 = " << dist_1 << '\n';
    // cout << "dist_2 = " << dist_2 << '\n';

    // cout << "dist = " << dist << '\n';

    // cout << "radius_1 = " << radius_1 << '\n';
    // cout << "radius_2 = " << radius_2 << '\n';

    // cout << "radius_1 + radius_2 = " << (radius_1 + radius_2) << '\n';
    //     if ((radius_1 + radius_2) > dist)
    //     {
    //         cout << "NO" << endl;
    //         return;
    //     }
    //     else if ((radius_1 + radius_2) < dist)
    //     {
    //         cout << "NO" << endl;
    //         return;
    //     }
    //     cout << "YES" << endl;

    // long long a, b;
    // cin >> a >> b;
    // long long mini = min(a,b);
    // long long maxi = max(a,b);
    // a = mini;
    // b = maxi;
    // long long total_sum = ((b * (b + 1)) ) / 2;
    // long long total_even_numbers = b / 2;
    // long long total_odd_numbers = b - total_even_numbers;

    // long long prev = ((a - 1) * (a) ) / 2;

    // long long inclusive_sum = ((total_sum - prev) ) ;

    // long long even_sum = 0;
    // long long odd_sum = 0;

    // long long s = (a - 1) / 2;
    // long long e = (s * (s + 1)) ;
    // long long e_total = (total_even_numbers * (total_even_numbers + 1)) ;
    // even_sum = ((e_total - e) ) ;

    // odd_sum = ((inclusive_sum - even_sum) ) ;
    // cout << inclusive_sum << endl;
    // cout << even_sum << endl;
    // cout << odd_sum << endl;
    // long long a, b, q;
    // cin >> a>>b>>q;
    // long long c = a ^ b;
    // long long rem = q % 3;
    // if (q == 1)
    // {
    //     cout << a << endl;
    //     return;
    // }
    // if (q == 2)
    // {
    //     cout << b << endl;
    //     return;
    // }
    // if (rem == 0)
    // {
    //     cout << c << endl;
    //     return;
    // }
    // else if (rem == 1)
    // {
    //     cout << a << endl;
    //     return;
    // }
    // else
    // {
    //     cout << b << endl;
    // }

    // long long n;
    // cin >> n;
    // // n2+n <= 2*n
    // // n2+n-2*n<=0
    // //-1+-1-8n/2
    // long long r = sqrt(1 + (8 * n));
    // long long root = (-1 + r) / 2;
    // cout << root << endl;
}

int main()
{
    factorial(MOD);
    // compute_primes();
    // compute_co_prime();
    // build_spf(1000000);
    int t;
    cin >> t;
    // t = 1;
    while (t--)
    {
        solve();
    }
}

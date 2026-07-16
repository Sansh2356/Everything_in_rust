#include <climits>
#include <unordered_set>
#include <cmath>
#include <iomanip>
#include <set>
#include <unordered_map>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;

const int MOD = 1e9 + 7;

#define debarr(a, n)            \
    cout << #a << " : ";        \
    for (int i = 0; i < n; i++) \
        cerr << a[i] << " ";    \
    cerr << endl;
#define debmat(mat, row, col)         \
    cout << #mat << " :\n";           \
    for (int i = 0; i < row; i++)     \
    {                                 \
        for (int j = 0; j < col; j++) \
            cerr << mat[i][j] << " "; \
        cerr << endl;                 \
    }
#define pr(...) dbs(#__VA_ARGS__, __VA_ARGS__)
template <class S, class T>
ostream &operator<<(ostream &os, const pair<S, T> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &p)
{
    os << "[ ";
    for (auto &it : p)
        os << it << " ";
    return os << "]";
}
template <class T>
ostream &operator<<(ostream &os, const unordered_set<T> &p)
{
    os << "[ ";
    for (auto &it : p)
        os << it << " ";
    return os << "]";
}
template <class S, class T>
ostream &operator<<(ostream &os, const unordered_map<S, T> &p)
{
    os << "[ ";
    for (auto &it : p)
        os << it << " ";
    return os << "]";
}
template <class T>
ostream &operator<<(ostream &os, const set<T> &p)
{
    os << "[ ";
    for (auto &it : p)
        os << it << " ";
    return os << "]";
}
template <class T>
ostream &operator<<(ostream &os, const multiset<T> &p)
{
    os << "[ ";
    for (auto &it : p)
        os << it << " ";
    return os << "]";
}
template <class S, class T>
ostream &operator<<(ostream &os, const map<S, T> &p)
{
    os << "[ ";
    for (auto &it : p)
        os << it << " ";
    return os << "]";
}
template <class T>
void dbs(string str, T t) { cerr << str << " : " << t << "\n"; }
template <class T, class... S>
void dbs(string str, T t, S... s)
{
    int idx = str.find(',');
    cerr << str.substr(0, idx) << " : " << t << ",";
    dbs(str.substr(idx + 1), s...);
}
template <class T>
void prc(T a, T b)
{
    cerr << "[";
    for (T i = a; i != b; ++i)
    {
        if (i != a)
            cerr << ", ";
        cerr << *i;
    }
    cerr << "]\n";
}

// Assuming a < b, log (min(a,b))
// With the help of if a <= b/2 then a % b < b/2 else if a > b/2 then a % b  = (a-b)
ll gcd(ll a, ll b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
ll lcm(ll a, ll b)
{
    return (a * b) / gcd(a, b);
}
// O(root(n)) for all num <= 1e12
bool is_prime(ll num)
{
    for (ll x = 2; x * x <= num; x++)
    {
        if (num % x == 0)
            return false;
    }
    return true;
}
// n <= 1e12
vector<ll> single_divisor(ll n)
{
    vector<ll> ans;
    for (ll x = 1; x * x <= n; x++)
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

set<ll> cream_puff(ll n)
{
    set<ll> ans;
    for (ll x = 1; x * x <= n; x++)
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
ll binpow(ll base, ll exponent, ll prime = MOD)
{
    if (exponent == 0)
        return 1;
    if (exponent % 2 != 0)
    {
        return (((base % prime) * (binpow(base, exponent - 1, prime) % prime)) % prime);
    }
    else
    {
        ll temp = binpow(base, exponent / 2, prime);
        return ((temp % prime) * (temp % prime)) % prime;
    }
}
ll binadd(ll base, ll exponent, ll prime = MOD)
{
    if (exponent == 0)
        return 0;
    if (exponent % 2 != 0)
    {
        return (((base % prime) + (binadd(base, exponent - 1, prime) % prime)) % prime);
    }
    else
    {
        ll temp = binadd(base, exponent / 2, prime);
        return ((temp % prime) + (temp % prime)) % prime;
    }
}
ll binpow_no_mod(ll base, ll exponent)
{
    if (exponent == 0)
        return 1;
    if (exponent % 2 != 0)
    {
        return ((base * (binpow(base, exponent - 1))));
    }
    else
    {
        ll temp = binpow(base, exponent / 2);
        return ((temp) * (temp));
    }
}
ll inverse(ll base, ll prime)
{
    return binpow(base, prime - 2, prime);
}
const ll inverse_2 = inverse(2, MOD);
ll add(ll a, ll b, ll prime)
{
    return ((a % prime) + (b % prime)) % prime;
}
ll divide(ll a, ll b, ll prime)
{
    ll inv = inverse(b, prime);
    return ((a % prime) * (inv % prime)) % prime;
}
ll mul(ll a, ll b, ll prime)
{
    return ((a % prime) * (b % prime)) % prime;
}
ll subtract(ll a, ll b, ll prime)
{
    return (((a % prime) - (b % prime)) + prime) % prime;
}

ll fact[1000100];
ll inv_arr[1000100];
void factorial(ll prime)
{
    fact[0] = 1;
    for (ll i = 1; i <= 1000000; i++)
    {
        fact[i] = (fact[i - 1] * i) % prime;
    }
    inv_arr[1000000] = inverse(fact[1000000], prime);
    for (ll x = 1000000; x >= 1; x--)
    {
        inv_arr[x - 1] = (inv_arr[x] * x) % prime;
    }
}
// valide n<= 1e6
ll ncr(ll n, ll r, ll prime)
{
    ll numerator = fact[n];
    ll a = inv_arr[n - r];
    ll b = inv_arr[r];
    ll c = (a * b) % prime;
    return (numerator * c) % prime;
}
ll slower_ncr(ll n, ll r, ll prime)
{
    ll numerator = fact[n];
    ll denominator = ((fact[n - r] % prime) * (fact[r] % prime)) % prime;
    return ((numerator % prime) * (inverse(denominator, prime) % prime)) % prime;
}
ll table[1001][1001];
// valid for n<=1000
ll ncr_table(ll n, ll r, ll prime)
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
ll dearrange[1000001];
// 10e6 O(N)
void dearrangement(ll n)
{
    dearrange[1] = 0;
    dearrange[2] = 1;

    for (ll x = 3; x <= n; x++)
    {
        dearrange[x] = ((x - 1) * (dearrange[x - 1] + dearrange[x - 2])) % MOD;
    }
}
ll npr(ll a, ll b, ll prime)
{
    ll n = fact[a];
    ll r = fact[(a - b)];
    ll dinv = inverse(r, prime);
    return (n * dinv) % MOD;
}
vector<vector<ll>> ncr_table_2(ll n, ll r, ll prime)
{
    vector<vector<ll>> local(31, vector<ll>(31, 0));
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

bool cmp(pair<ll, ll> &p1, pair<ll, ll> &p2)
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
    for (ll x = 2; x <= 10000000; x++)
    {
        primes_arr[x] = true;
    }
    primes_arr[1] = false;
    for (ll x = 2; x <= 10000000; x++)
    {
        if (primes_arr[x] == true)
        {
            for (ll y = x * x; y <= 10000000; y += x)
            {
                primes_arr[y] = false;
            }
        }
    }
}
void slow_compute_primes()
{
    for (ll x = 2; x <= 1000; x++)
    {
        primes_arr[x] = true;
    }
    primes_arr[1] = false;
    for (ll x = 2; x <= 1000; x++)
    {
        if (primes_arr[x] == true)
        {
            for (ll y = 2 * x; y <= 1000; y += x)
            {
                primes_arr[y] = false;
            }
        }
    }
}
// b>a and finding primes within the range [a,b]
// finding in a complexity of O((b-a)log log b)
vector<ll> segmeneted_sieve(ll a, ll b)
{
    // Finding primes within the range of [1,root(b)] using normal sieve
    // giving out time complexity of O(root(b)log(log(root(b))))
    vector<ll> local_sieve;
    for (ll x = 1; x * x <= b; x++)
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
    for (ll x = 0; x < local_sieve.size(); x++)
    {
        ll curr_prime = local_sieve[x];
        // First multiple of prime > a
        ll rem = a % curr_prime;
        ll first_multiple = -1;
        if (rem == 0)
        {
            first_multiple = a;
        }
        else
        {
            ll temp = (a - rem) + curr_prime;
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
    vector<ll> v;
    for (ll x = 0; x < res.size(); x++)
    {
        if (res[x] == true)
        {
            v.push_back(a + x);
        }
    }
    return v;
}

ll factors[1000001];
// log n factors n<=10e7

void build_spf(ll n)
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
unordered_map<ll, ll> compute_factors(ll num)
{
    unordered_map<ll, ll> ans;
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
vector<pair<ll, ll>> Factors(ll x)
{
    vector<pair<ll, ll>> ans;
    for (ll i = 2; i * i <= x; i++)
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
unordered_map<ll, ll> factors_mapping(ll x)
{
    unordered_map<ll, ll> ans;
    for (ll i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            int cnt = 0;
            while (x % i == 0)
            {
                cnt++;
                x /= i;
            }
            ans.insert({i, cnt});
        }
    }
    if (x > 1)
        ans.insert({x, 1});
    return ans;
}
// Sum of divisors and number of divisors and euler totient function
ll euler_arr[10000001];
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
    for (ll x = 1; x <= 10000000; x++)
    {
        euler_arr[x] = x;
    }
    for (ll x = 2; x <= 10000000; x++)
    {
        if (primes_arr[x] == true)
        {
            for (ll y = x; y <= 10000000; y += x)
            {
                euler_arr[y] -= euler_arr[y] / x;
            }
        }
    }
}
// n<=10e7
ll number_of_divisors(ll num)
{
    unordered_map<ll, ll> freq = compute_factors(num);
    ll prod = 1;
    for (auto it : freq)
    {
        prod = (prod * (it.second + 1));
    }
    return prod;
}
/*
    a^x mod(m) = (a^(x%totient(m)))%m where x and m are co-prime the given is euler's theorem
    n<=10e7
*/
ll sum_of_divisors(ll num)
{
    /*
        sum(n) = p1^ax+1-1/p-1+.....
    */
    ll ans = 1;
    unordered_map<ll, ll> m = compute_factors(num);
    for (auto it : m)
    {
        ll factor = it.first;
        ll power = it.second;
        ll numerator = ((binpow(factor, power + 1, MOD) - 1) + MOD) % MOD;
        ll denominator = ((factor - 1) + MOD) % MOD;
        ll dinv = inverse(denominator, MOD);
        ans = ((ans % MOD) * ((numerator * dinv) % MOD)) % MOD;
    }
    return ans;
}
// n<=10e7
ll product_of_divisors(ll num)
{
    /*
        Product of divisors = product(pi^(ai*(number of divisors)/2))
    */
    ll ans = 1;
    unordered_map<ll, ll> m = compute_factors(num);
    ll num_divisors = number_of_divisors(num);
    for (auto it : m)
    {
        ll power = (it.second * num_divisors) / 2;
        ll val = binpow(it.first, power, MOD);
        ans = (ans * val) % MOD;
    }
    return ans;
}

void rec(string &s, ll idx, vector<string> &ans)
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
ll maximum_power(ll x, ll factorial_value)
{
    // O(root(X))
    vector<pair<ll, ll>> factors = Factors(x);
    // O(log(X))
    ll ans = INT_MAX;
    for (auto factor : factors)
    {
        ll fact = factor.first;
        ll max_power = factor.second;
        ll power_counter = 1;
        ll initial_value = floor(factorial_value / binpow(fact, power_counter, MOD));
        ll running_sum = initial_value;
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
        ans = min(ans, (ll)floor(running_sum / max_power));
    }
    return ans;
}
ll GET(ll n, ll m)
{
    ll q = n / m;
    ll r = n % m;

    ll cycle = (((m % MOD) * ((m - 1) % MOD)) % MOD * inverse(2, MOD)) % MOD;
    ll rem = (((r % MOD) * ((r + 1) % MOD)) % MOD * inverse(2, MOD)) % MOD;

    return (((q % MOD) * cycle) % MOD + rem) % MOD;
}
// Harmonic lemma,from which: O(root(n))
ll harmonic_lemma_value(ll n, ll m)
{

    ll last_item_in_range = -1;
    ll ans = 0;
    for (ll x = 1; x <= n; x = last_item_in_range + 1)
    {
        ll deno = (n / x);
        last_item_in_range = (n / deno);
        ll total_items = (last_item_in_range - x + 1);
        cout << last_item_in_range << " " << total_items << endl;
        cout << "X value " << x << endl;
        ans = (ans + (((total_items % MOD) * (binpow(deno, m, MOD) % MOD)) % MOD)) % MOD;
    }
    return ans % MOD;
}
// Sum of sum of divisors within range [1,n] having tc of O(root(n)) due to harmonic lemma.
ll sum_of_divisors(ll n, ll m)
{

    ll last_item_in_range = -1;
    ll ans = 0;
    for (ll x = 1; x <= n; x = last_item_in_range + 1)
    {
        ll deno = (n / x);
        last_item_in_range = (n / deno);

        ll total_items = (last_item_in_range - x + 1);
        ll sum_1 = ((((((x - 1) + MOD) % MOD) * (x % MOD)) % MOD) * inverse_2) % MOD;
        ll sum_2 = ((((last_item_in_range % MOD) * ((last_item_in_range + 1) % MOD)) % MOD) * inverse_2) % MOD;
        ll total_sum = ((sum_2 - sum_1) + MOD) % MOD;

        ans = (ans + (((deno * total_sum) % MOD)) % MOD) % MOD;
    }
    return ans % MOD;
}
ll atc_144(ll num)
{
    ll mini = 1e12;
    for (ll x = 1; x * x <= num; x++)
    {
        if (num % x == 0)
        {
            ll local = 0;
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
    return -1;
}
ll basic_ncr(ll n, ll r)
{
    ll ans = 1;
    for (ll i = 1; i <= r; i++)
    {
        ans = ans * (n - i + 1);
        ans = ans / i;
    }
    return ans;
}
class RandomClass
{
public:
    multiset<ll> m1;
    multiset<ll> rest;
    ll curr_sum;
    ll capacity;
    RandomClass(ll cap)
    {
        this->curr_sum = 0;
        this->capacity = cap;
    }
    void add(ll num)
    {
        if (m1.size() >= capacity)
        {
            ll smallest = *(m1.begin());
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
    void remove(ll x)
    {
        if (m1.count(x))
        {
            m1.erase(m1.find(x));
            curr_sum -= x;
            if (rest.size() >= 1)
            {
                ll next_replacement = *(rest.rend());
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
    ll query()
    {
        return curr_sum;
    }
};
/*
    n+k-1ck-1
*/
bool check(ll sum, ll a, ll b)
{
    while (sum >= 1)
    {
        ll rem = sum % 10;
        if (rem != a && rem != b)
        {
            return false;
        }
        sum /= 10;
    }
    return true;
}
ll expr_val(string expr_3)
{
    if (expr_3 == "")
        return 0;
    ll expr_3_val = 0;
    vector<ll> nums;
    ll start_idx = -1;
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
ll maxSum(vector<int> &nums, int k, int mul)
{
    sort(nums.begin(), nums.end());
    ll ans = 0;
    for (int x = nums.size() - 1; x >= 0 && k >= 0; x--)
    {
        if (mul >= 1)
        {
            ans += (ll)nums[x] * (ll)mul;
            mul--;
        }
        else
        {
            ans += nums[x];
        }
        k--;
    }
    return ans;
}
int removeCoveredIntervals(vector<vector<int>> &intervals)
{
    vector<pair<int, int>> v;
    for (int x = 0; x < intervals.size(); x++)
    {
        v.push_back({intervals[x][0], intervals[x][1]});
    }
    // sort(v.begin(), v.end(), cmp);
    int start = v[0].first;
    int end = v[0].second;
    int ans = v.size();
    for (int x = 1; x < v.size(); x++)
    {
        int interval_start = v[x].first;
        int interval_end = v[x].second;
        if (interval_start >= start && interval_end <= end)
        {
            ans--;
        }
        else
        {
            start = min(start, interval_start);
            end = max(end, interval_end);
        }
    }

    return ans;
}
void compute_prime_factors(int num, set<int> &st)
{
    while (num >= 2 && factors[num] != num)
    {
        if (!st.count(factors[num]))
        {
            st.insert(factors[num]);
        }
        num /= factors[num];
    }
    if (num != 1)
    {
        st.insert(num);
    }
}
int divisibleGame_tle(vector<int> &nums)
{
    int n = INT_MAX;
    int ans = INT_MIN;
    set<int> st;
    for (auto num : nums)
    {
        compute_prime_factors(num, st);
    }
    for (auto factor : st)
    {
        for (int x = 0; x < nums.size(); x++)
        {
            for (int y = x + 1; y < nums.size(); y++)
            {
                int bob_score = 0;
                int alice_score = 0;
                for (int z = x; z <= y; z++)
                {
                    if (nums[z] % factor == 0)
                    {
                        alice_score += nums[z];
                    }
                    else
                    {
                        bob_score += nums[z];
                    }
                }
                if ((alice_score - bob_score) > ans)
                {
                    n = factor;
                    ans = (alice_score - bob_score);
                }
                else if ((alice_score - bob_score) == ans)
                {
                    n = min(n, factor);
                }
            }
        }
    }
    return ans;
}
vector<ll> construct_prefix_overflow(vector<ll> nums)
{
    vector<ll> pf_arr(nums.size() + 1);
    pf_arr[0] = 0;
    for (int x = 0; x < nums.size(); x++)
    {
        ll p = (pf_arr[x] % MOD + nums[x] % MOD);
        if (p < 0)
        {
            pf_arr[x + 1] = (p % MOD + MOD) % MOD;
        }
        else
        {

            pf_arr[x + 1] = p % MOD;
        }
    }
    return pf_arr;
}
vector<ll> construct_prefix_2(vector<ll> nums, ll k)
{
    vector<ll> pf_arr(nums.size() + 1);
    pf_arr[0] = 0;
    vector<ll> bin_arr(pf_arr.size(), 0);
    for (int x = 0; x < nums.size(); x++)
    {
        ll p = pf_arr[x] + nums[x + 1];
        if (p >= k)
        {
            bin_arr[x + 1] = 1;
        }
        pf_arr[x + 1] = (pf_arr[x] + nums[x + 1]);
    }
    return bin_arr;
}
vector<ll> construct_prefix(vector<ll> nums)
{
    vector<ll> pf_arr(nums.size());
    pf_arr[0] = nums[0];
    for (int x = 1; x < nums.size(); x++)
    {
        pf_arr[x] = (pf_arr[x - 1] + nums[x]);
    }
    return pf_arr;
}
vector<ll> partial_sum(vector<vector<ll>> &queries, ll n)
{
    vector<ll> diff_arr(n, 0);
    for (int x = 0; x < queries.size(); x++)
    {
        ll l = queries[x][0];
        ll r = queries[x][1];
        ll num = queries[x][2];
        diff_arr[l] += num;
        if ((r + 1) < diff_arr.size())
            diff_arr[r + 1] -= num;
    }
    vector<ll> after_arr = construct_prefix(diff_arr);
    return after_arr;
}
vector<ll> partial_sum_2(vector<vector<ll>> &queries, ll n, ll k)
{
    vector<ll> diff_arr(n, 0);
    for (int x = 0; x < queries.size(); x++)
    {
        ll l = queries[x][0];
        ll r = queries[x][1];
        ll num = queries[x][2];
        diff_arr[l] += num;
        if ((r + 1) < diff_arr.size())
            diff_arr[r + 1] -= num;
    }
    vector<ll> after_arr = construct_prefix_2(diff_arr, k);
    return after_arr;
}
ll appealSum(string s)
{
    ll ans = 0;
    ll total_subarr = (s.length() * (s.length() + 1)) / 2;
    ll cnt = 0;
    unordered_map<char, ll> m;
    for (int x = 0; x < s.length(); x++)
    {
        if (m.count(s[x]) == true)
        {
            ll prev_idx = m[s[x]];
            ll curr_idx = x;
            ll in_between = (curr_idx - prev_idx) - 1;
            cnt += (in_between * (in_between + 1)) / 2;
            m[s[x]] = x;
        }
        else
        {
            cnt += (x * (x + 1)) / 2;
            m[s[x]] = x;
        }
    }
    for (auto it : m)
    {
        ll last_idx = it.second;
        ll n = (s.length() - last_idx) - 1;
        cnt += (n * (n + 1)) / 2;
    }
    ans += (m.size() * total_subarr);
    return ans - cnt;
}
// This is a subset of distinct so all the cases which do not include distinct will contribute to it
// but additionally others containing more than 2 distinct will also contribute to this .
ll appealSum_2(string s)
{
    ll total_subarr = (s.length() * (s.length() + 1)) / 2;
    ll cnt = 0;
    unordered_map<char, vector<ll>> m;
    for (int x = 0; x < s.length(); x++)
    {
        if (m.count(s[x]))
        {
            m[s[x]].push_back(x);
        }
        else
        {
            m[s[x]].push_back(-1);
            // if (x != 0)
            m[s[x]].push_back(x);
        }
    }
    for (auto &it : m)
    {
        it.second.push_back(s.length());
    }
    for (auto it : m)
    {

        for (int x = 1; x < it.second.size() - 1; x++)
        {
            cnt += (((it.second[x] - it.second[x - 1])) * ((it.second[x + 1] - it.second[x])));
        }
    }

    return cnt;
}
vector<vector<ll>> prefix_2d(vector<vector<ll>> &arr)
{
    vector<vector<ll>> pf(arr.size(), vector<ll>(arr[0].size(), 0));
    for (ll x = 1; x < pf.size(); x++)
    {
        for (ll y = 1; y < pf[0].size(); y++)
        {
            pf[x][y] = arr[x][y];
            if (x > 0)
                pf[x][y] += pf[x - 1][y];
            if (y > 0)
                pf[x][y] += pf[x][y - 1];
            if (x > 0 && y > 0)
                pf[x][y] -= pf[x - 1][y - 1];
        }
    }
    return pf;
}
vector<vector<ll>> prefix_2d_overflow(vector<vector<ll>> &arr)
{
    vector<vector<ll>> pf(arr.size(), vector<ll>(arr[0].size(), 0));
    for (ll x = 1; x < arr.size(); x++)
    {
        for (ll y = 1; y < arr[0].size(); y++)
        {
            pf[x][y] = arr[x][y] % MOD;
            if (x > 0)
            {
                ll val = ((pf[x][y] % MOD) + (pf[x - 1][y] % MOD)) % MOD;
                if (val < 0)
                {
                    pf[x][y] = ((val % MOD) + MOD) % MOD;
                }
                else
                {
                    pf[x][y] = (val % MOD);
                }
            }
            if (y > 0)
            {
                ll val = ((pf[x][y] % MOD) + (pf[x][y - 1] % MOD)) % MOD;
                if (val < 0)
                {
                    pf[x][y] = ((val % MOD) + MOD) % MOD;
                }
                else
                {
                    pf[x][y] = (val % MOD);
                }
            }
            if (x > 0 && y > 0)
            {
                ll val = (((pf[x][y] % MOD) - (pf[x - 1][y] % MOD)) + MOD) % MOD;
                pf[x][y] = val % MOD;
            }
        }
    }
    return pf;
}
vector<vector<ll>> partial_sum_2d(vector<vector<ll>> &queries, ll n, ll m)
{
    vector<vector<ll>> partial_sum_arr(n, vector<ll>(m, 0));
    for (ll i = 0; i < queries.size(); i++)
    {
        ll l = queries[i][0];
        ll r = queries[i][1];
        ll u = queries[i][2];
        ll d = queries[i][3];
        ll x = queries[i][4];

        partial_sum_arr[u][l] += x;
        if (r + 1 < m)
            partial_sum_arr[u][r + 1] -= x;
        if (d + 1 < n)
            partial_sum_arr[d + 1][l] -= x;
        if ((d + 1) < m && (r + 1) < n)
            partial_sum_arr[d + 1][r + 1] += x;
    }
    return prefix_2d(partial_sum_arr);
}
void solve_range_freq_kth_query()
{
    ll n, m, q;
    cin >> n >> m >> q;
    vector<ll> v(n);
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
    }
    vector<vector<ll>> queries;
    while (m--)
    {
        ll l, r;
        cin >> l >> r;
        l--;
        r--;
        queries.push_back({l, r, 1});
    }
    vector<ll> freq_arr = partial_sum(queries, n);

    map<ll, ll> mapping;
    map<ll, ll> mapping_indices;

    for (ll x = 0; x < freq_arr.size(); x++)
    {
        if (freq_arr[x] != 0)
        {
            mapping[v[x]] += freq_arr[x];
        }
    }
    vector<ll> pf_arr(mapping.size());
    pf_arr[0] = mapping.begin()->second;
    mapping_indices[pf_arr[0]] = mapping.begin()->first;
    int idx = 1;
    for (auto it : mapping)
    {
        if (it.first != mapping.begin()->first)
        {
            pf_arr[idx] = pf_arr[idx - 1] + it.second;
            mapping_indices[pf_arr[idx]] = it.first;
            idx++;
        }
    }
    while (q--)
    {
        ll k;
        cin >> k;
        auto it = lower_bound(pf_arr.begin(), pf_arr.end(), k);
        if (it != pf_arr.end())
        {
            cout << mapping_indices[*it] << " ";
        }
        else
        {
            cout << -1 << " ";
        }
    }
    cout << "\n";
}

void solve_grid_max_overlap()
{
    ll n, m, q;

    cin >> n >> m >> q;
    vector<vector<ll>> queries;
    while (q--)
    {
        ll x1, x2, y1, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        queries.push_back({y1, y2, x1, x2, c});
    }
    vector<vector<ll>> diff_arr = partial_sum_2d(queries, 1e3 + 1, 1e3 + 1);
    ll val = INT_MIN;
    ll cnt = 0;
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= m; y++)
        {
            if (diff_arr[x][y] > val)
            {
                cnt = 1;
                val = diff_arr[x][y];
            }
            else if (diff_arr[x][y] == val)
            {
                cnt++;
            }
        }
    }
    cout << val << " " << cnt << "\n";
}

void solve_rect_sum_queries()
{
    ll n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> arr(n + 1, vector<ll>(m + 1, 0));
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= m; y++)
        {
            ll num;
            cin >> num;
            arr[x][y] = num;
        }
    }
    vector<vector<ll>> pf_arr = prefix_2d_overflow(arr);
    // for(auto i:pf_arr){
    //     for(auto j:pf_arr){
    //         cout<<j<<" ";
    //     }
    //     cout<<"\n";
    // }
    while (q--)
    {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ll ans = pf_arr[x2][y2];
        if ((y1 - 1) > 0)
            ans = (((ans) - (pf_arr[x2][y1 - 1])));
        if ((x1 - 1) > 0)
            ans = (((ans) - (pf_arr[x1 - 1][y2])));
        if ((x1 - 1) > 0 && (y1 - 1) > 0)
            ans = ((ans) + (pf_arr[x1 - 1][y1 - 1]));
        ans = ans % MOD;
        if (ans < 0)
            ans += MOD;
        cout << ans << "\n";
    }
    // while (q--)
    // {
    //     ll x1, y1, x2, y2;
    //     cin >> x1 >> y1 >> x2 >> y2;
    //     ll ans = pf_arr[x2][y2] % MOD;
    //     if ((y1 - 1) > 0)
    //         ans = (((ans % MOD) - (pf_arr[x2][y1 - 1] % MOD)) + MOD) % MOD;
    //     if ((x1 - 1) > 0)
    //         ans = (((ans % MOD) - (pf_arr[x1 - 1][y2] % MOD)) + MOD) % MOD;
    //     if ((x1 - 1) > 0 && (y1 - 1) > 0)
    //         ans = ((ans % MOD) + (pf_arr[x1 - 1][y1 - 1] % MOD)) % MOD;
    //     cout << ans % MOD << "\n";
    // }
}

void solve_alternating_permutation()
{
    int n;
    cin >> n;
    vector<int> even;
    vector<int> odd;
    for (int x = 1; x <= n; x++)
        x % 2 == 0 ? even.push_back(x) : odd.push_back(x);
    for (int x = 1; x <= n; x++)
    {
        if (x % 2 == 0)
        {
            cout << odd.back() << " ";
            odd.pop_back();
        }
        else
        {
            cout << even.back() << " ";
            even.pop_back();
        }
    }
    cout << "\n";
}

void solve_appeal_sum_2()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;
    cout << appealSum_2(s) << "\n";
}

void solve_appeal_sum()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;
    cout << appealSum(s) << "\n";
}

void solve_covered_count_queries()
{
    ll n, k, q;
    cin >> n >> k >> q;
    vector<vector<ll>> queries;
    for (int x = 0; x < n; x++)
    {
        ll l, r;
        cin >> l >> r;
        queries.push_back({l, r, 1});
    }
    vector<ll> bin_arr = partial_sum_2(queries, 1e6, k);
    vector<ll> pf(bin_arr.size(), 0);
    for (int x = 1; x < bin_arr.size(); x++)
    {
        pf[x] = bin_arr[x] + pf[x - 1];
    }
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        cout << pf[r] - pf[l - 1] << "\n";
    }
}

void solve_range_sum_queries()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
    }
    ll ans = 0;
    vector<ll> pf = construct_prefix(v);
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        ll sum_1 = pf[r] % MOD;
        ll sum_2 = pf[l - 1] % MOD;
        ans = (((sum_1 % MOD + MOD)) - (sum_2 % MOD)) % MOD;
        cout << ans << "\n";
    }
}

void solve_range_update_print()
{
    ll n, q;
    cin >> n >> q;
    vector<vector<ll>> queries;
    while (q--)
    {
        ll l, r, x;
        cin >> l >> r >> x;
        queries.push_back({l, r, x});
    }
    vector<ll> p = partial_sum(queries, n);
    for (auto i : p)
        cout << i << " ";
    cout << "\n";
}

void solve_prefix_sum_print()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
    }
    vector<ll> pf = construct_prefix(v);
    for (auto i : pf)
    {
        cout << i << " ";
    }
    cout << "\n";
}

void solve_sum_abs_diff()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    ll ans = 0;
    ll cum_sum = 0;
    ll total_sum = 0;
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
        total_sum += num;
    }
    sort(v.begin(), v.end());
    for (ll x = 0; x < n; x++)
    {
        cum_sum += v[x];
        ans += abs((total_sum - cum_sum) - ((n - (x + 1)) * v[x]));
    }
    cout << ans << "\n";
}

void solve_distinct_count()
{
    ll n;
    cin >> n;
    set<int> st;
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        st.insert(num);
    }
    cout << st.size();
    cout << "\n";
}

void solve_multimap_queries()
{
    ll q;
    cin >> q;
    multimap<string, ll> m;
    while (q--)
    {
        string s;
        cin >> s;
        if (s == "add")
        {
            ll val;
            string key;
            cin >> key >> val;
            m.insert({key, val});
        }
        else if (s == "erase")
        {
            string key;
            cin >> key;
            for (auto it = m.begin(); it != m.end();)
            {
                if (it->first == key)
                {
                    it = m.erase(it);
                    break;
                }
                else
                    ++it;
            }
        }
        else if (s == "eraseall")
        {
            string num;
            cin >> num;
            while (1)
            {
                if (m.count(num))
                {
                    m.erase(num);
                }
                else
                {
                    break;
                }
            }
        }
        else if (s == "print")
        {
            string x;
            cin >> x;
            if (!m.count(x))
                cout << 0 << "\n";
            else
            {
                cout << (m.find(x))->first << "\n";
            }
        }
    }
}

void solve_print_permutations()
{
    ll n;
    cin >> n;
    vector<int> v(n);
    for (int x = 0; x < n; x++)
    {
        v[x] = (x + 1);
    }
    do
    {

        for (int x = 0; x < n; x++)
        {
            cout << v[x] << " ";
        }
        cout << endl;
    } while (next_permutation(v.begin(), v.end()));
}

void solve_max_items_budget()
{
    ll n, m;
    cin >> n >> m;

    vector<ll> v(n);
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
    }
    sort(v.begin(), v.end());
    ll ans = 0;
    for (auto i : v)
    {
        if (m < i)
            break;
        m -= i;
        ans++;
    }
    cout << ans << endl;
}

void solve_dynamic_array_queries()
{
    ll q;
    cin >> q;
    vector<ll> v;
    while (q--)
    {
        string query;
        cin >> query;
        if (query == "add")
        {
            ll num;
            cin >> num;
            v.push_back(num);
        }
        else if (query == "clear")
        {
            v.clear();
        }
        else if (query == "remove")
        {
            if (!v.empty())
                v.pop_back();
        }
        else
        {
            ll num;
            cin >> num;
            if (v.size() > num)
            {
                cout << v[num] << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
    }
}

void solve_product_mod()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    ll prod = 1;
    for (int x = 0; x < n; x++)
    {
        int num;
        cin >> num;
        v[x] = num;
        prod = ((num % MOD) * (prod % MOD)) % MOD;
    }
    cout << prod << '\n';
}

void solve_one_two_three_prefix()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    unordered_map<ll, ll> m;
    for (int x = 0; x < n; x++)
    {
        int num;
        cin >> num;
        v[x] = num;
        m[v[x]]++;
    }
    unordered_map<ll, ll> m2;
    for (int x = 0; x < v.size() - 2; x++)
    {
        m2[v[x]]++;
        ll freq_1 = m2[1];
        ll freq_2 = m2[2];
        ll freq_3 = m2[3];

        {
            if (freq_1 >= (freq_2 + freq_3))
            {
                ll rem_freq1 = m[1] - freq_1;
                ll rem_freq2 = m[2] - freq_2;
                ll rem_freq3 = m[3] - freq_3;
                ll last_idx = v[v.size() - 1];
                if (last_idx == 1)
                    rem_freq1--;
                else if (last_idx == 2)
                    rem_freq2--;
                else
                {
                    rem_freq3--;
                }
                if ((rem_freq1 + rem_freq2) >= rem_freq3)
                {
                    cout << "YES" << endl;
                    return;
                }
            }
        }
    }
    cout << "NO" << endl;
}

void solve_freq_threshold()
{
    int k;
    cin >> k;
    vector<int> v(k);
    for (int x = 0; x < k; x++)
    {
        int num;
        cin >> num;
        v[x] = num;
    }
    int cnt = 0;
    for (auto num : v)
    {
        if (num >= 3)
        {
            cout << "YES" << endl;
            return;
        }
        else if (num >= 2)
        {
            cnt++;
        }
    }
    if (cnt >= 2)
    {
        cout << "YES" << endl;
        return;
    }
    cout << "NO" << endl;
}

void solve_read_array_stub()
{
    ll n;
    cin >> n;
    vector<ll> v(n);

    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
    }
}

void solve_sum_of_divisors_range()
{
    ll n;
    cin >> n;
    cout << sum_of_divisors(n, 1) % MOD << endl;
}

void solve_primes_ending_in_one()
{
    ll n;
    cin >> n;

    for (int x = 2; x <= 55555; x++)
    {
        if (primes_arr[x] == true && x % 10 == 1)
        {
            n--;
            cout << x << " ";
        }
        if (n == 0)
            break;
    }
}

void solve_distinct_divisor_chain()
{
    ll n;
    cin >> n;
    vector<pair<ll, ll>> factors = Factors(n);
    ll ans = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (auto p : factors)
    {
        ll temp = p.second;
        while (temp >= 1)
        {
            pq.push(pow(p.first, temp));
            temp--;
        }
    }
    unordered_set<ll> st;
    while (pq.empty() != true && pq.top() <= n)
    {
        if (n % pq.top() == 0 && st.count(pq.top()) == false)
        {
            n /= pq.top();
            st.insert(pq.top());
            ans++;
        }
        pq.pop();
    }
    cout << ans << endl;
}

void solve_pairwise_distance_avg()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    ll numerator = 0;
    for (int x = 0; x < n; x++)
    {
        ll num = 0;
        cin >> num;
        v[x] = num;
        numerator += num;
    }
    sort(v.begin(), v.end());
    vector<ll> prefix_sum(n, 0);
    vector<ll> suffix_sum(n, 0);
    prefix_sum[0] = v[0];
    suffix_sum[0] = v[v.size() - 1];
    for (int x = 1; x < n; x++)
    {
        suffix_sum[x] = suffix_sum[x - 1] + v[n - x - 1];
    }
    for (int x = 1; x < v.size(); x++)
    {
        prefix_sum[x] = prefix_sum[x - 1] + v[x];
    }
    reverse(suffix_sum.begin(), suffix_sum.end());
    ll cum_sum = 0;
    for (int x = 0; x < v.size(); x++)
    {
        ll left_sum = abs((prefix_sum[x] - v[x]) - (x * v[x]));
        ll right_sum = abs((suffix_sum[x] - v[x]) - ((n - x - 1) * v[x]));
        cum_sum += (left_sum + right_sum);
    }
    numerator += (cum_sum);
    ll deno = n;
    ll gcd_value = gcd(numerator, deno);
    while (gcd_value > 1)
    {
        numerator /= gcd_value;
        deno /= gcd_value;
        gcd_value = gcd(numerator, deno);
    }
    cout << numerator << " " << deno << endl;
}

void solve_primes_in_segment_pairs()
{
    ll l, r;
    cin >> l >> r;
    ll ans = ((r - l) + 1) * ((r - l) + 1);
    ans -= ((r - l) + 1);
    vector<ll> primes = segmeneted_sieve(l, r);
    ll non_primes = (((r - l) + 1) - primes.size());
    cout << non_primes << endl;
    ans -= (non_primes * primes.size());
    ans -= (r - l) * primes.size();
    cout << ans << endl;
}

void solve_next_power_of_ten()
{
    ll x;
    cin >> x;
    ll len = 0;
    while (x >= 1)
    {
        x /= 10;
        len++;
    }
    cout << binpow(10, len) + 1 << endl;
}

void solve_divisibility_check()
{
    ll x, y;
    cin >> x >> y;
    if (y > x)
    {
        cout << "NO" << endl;
    }
    else
    {
        if (y == x)
        {
            cout << "YES" << endl;
        }
        else
        {
            if (x % y == 0)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
}

void solve_gcd_and_factor_freq()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    unordered_map<ll, ll> factor_freq;
    ll ans = 0;
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
        unordered_map<ll, ll> factors = factors_mapping(num);
        for (auto it : factors)
        {
            ll factor = it.first;
            ll power = it.second;
            factor_freq[factor]++;
        }
        if (x == 0)
        {
            ans = num;
        }
        else if (x != 0)
        {
            ans = gcd(ans, num);
        }
    }
}

void solve_min_product_mod_2019()
{
    ll l, r;
    cin >> l >> r;
    ll rem = l % 2019;
    if (rem == 0)
    {
        cout << 0 << endl;
    }
    else
    {
        ll temp = (l - rem) + 2019;
        if (temp >= l && temp <= r)
        {
            cout << 0 << endl;
            return;
        }
        ll ans = INT_MAX;
        for (ll x = l; x <= r; x++)
        {
            for (ll y = (x + 1); y <= r; y++)
            {
                ll prod = x * y;
                ll rem = prod % 2019;
                if (rem < ans)
                {
                    ans = rem;
                }
            }
        }
        cout << ans << endl;
    }
}

void solve_common_prime_divisors()
{
    ll a, b;
    cin >> a >> b;

    set<ll> divs_a = cream_puff(a);
    set<ll> divs_b = cream_puff(b);
    map<ll, bool> combined;

    for (auto it : divs_a)
    {
        if (divs_b.count(it) == true)
        {
            combined.insert({it, true});
        }
    }

    auto it = combined.begin();
    ll ans = 1;
    ll maxi = (*(combined.rbegin())).first;

    while (it != combined.end())
    {
        ll divisor = (*(it)).first;
        if (divisor == 1)
        {
            it++;
            continue;
        }
        if (is_prime(divisor))
        {
            ans++;
            // for (ll        x = 2 * divisor; x <= maxi; x += divisor)
            // {
            //     if (combined.count(x))
            //     {
            //         combined[x] = false;
            //     }
            // }
        }
        it++;
    }
    cout << ans << endl;
}

void solve_max_mod_split()
{
    ll a, b;
    cin >> a >> b;
    ll maxi = max(a, b);
    ll mini = min(a, b);

    ll rem = maxi % mini;
    ll ans = 0;

    ans += (rem * mini);
    ans += ((maxi - rem) / mini);

    cout << ans << endl;
}

void solve_exactly_k_equal_adjacent()
{
    ll n, m, k;
    cin >> n >> m >> k;
    ll ans = 0;

    for (ll x = 0; x <= k; x++)
    {
        // All the remaining blocks cannot get the same color alloted to other blocks
        // because that will lead to increasing the exactly k pair count leading to false cases as well.
        ll comp_1 = binpow((m - 1), (n - x - 1), MOD);
        ll comp_2 = m;
        ll comp_3 = (comp_1 * comp_2) % MOD;
        ll comp_4 = ncr((n - 1), x, MOD);
        ll comp_5 = (comp_4 * comp_3) % MOD;

        ans = (ans + comp_5) % MOD;
    }
    cout << ans << endl;
}

void solve_divisors_greater_than_b()
{
    ll a, b;
    cin >> a >> b;
    if (a == b)
    {
        cout << "infinity" << endl;
        return;
    }
    else if (b >= a)
    {
        cout << 0 << endl;
        return;
    }
    else
    {
        vector<ll> divs = single_divisor(a - b);
        ll ans = 0;
        for (auto div : divs)
        {
            if (div > b)
            {
                ans++;
            }
            else if (div > a)
                break;
        }
        cout << ans << endl;
    }
}

void solve_at_most_k_pairs()
{
    ll n, m, k;
    cin >> n >> m >> k;
    ll total_cases = binpow(m, n, MOD);
    ll invalid_cases = 0;
    ll total_pairs = n - 1;
    for (ll x = (k + 1); x <= total_pairs; x++)
    {
        invalid_cases = (invalid_cases % MOD + ((ncr(total_pairs, x, MOD) * m) % MOD)) % MOD;
    }
    cout << ((total_cases - invalid_cases) + MOD) % MOD << endl;
}

void solve_multiple_pairs_count()
{
    ll n;
    cin >> n;
    ll ans = 0;

    // a and b are multiples of b to satisfy the given identity
    for (ll x = 1; x <= n; x++)
    {
        ll num_multiples = floor(n / x);
        ans += (num_multiples * num_multiples);
    }
    cout << ans << endl;
}

void solve_min_cost_transform()
{
    ll n, c;
    cin >> n >> c;
    vector<ll> a(n);
    vector<ll> b(n);
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        a[x] = num;
    }
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        b[x] = num;
    }
    ll ans = INT_MAX;
    ll cnt_1 = 0;
    ll cnt_2 = 0;
    for (int x = 0; x < n; x++)
    {
        if (b[x] > a[x])
        {
            cnt_1 = INT_MAX;
            break;
        }
        else
        {
            cnt_1 += (a[x] - b[x]);
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int x = 0; x < n; x++)
    {
        if (b[x] > a[x])
        {
            cnt_2 = INT_MAX;
            break;
        }
        else
        {
            cnt_2 += (a[x] - b[x]);
        }
    }
    cnt_2 += c;
    ans = min(cnt_2, cnt_1);
    if (ans == INT_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ans << endl;
    }
}

void solve_good_digit_numbers()
{
    ll a, b, n;
    cin >> a >> b >> n;
    ll ans = 0;
    if (n == 1)
    {
        cout << 2 << "\n";
        return;
    }
    else if (n == 2)
    {
        if (check(a + b, a, b))
        {
            cout << 2 << endl;
            return;
        }
        else
        {
            cout << 0 << endl;
            return;
        }
    }
    // Iterating over length of n and checking for
    // how many bs and as can be accomodated .
    // sum of digits can be given as = a*x+(n-x)*b and checking it for all the good number
    for (int x = 0; x <= n; x++)
    {
        // Setting frequency of A's to x.
        ll sum = ((a * x) + (n - x) * b);
        if (check(sum, a, b) == true)
        {
            ans = (ans + ncr(n, x, MOD)) % MOD;
        }
    }
    cout << ans % MOD << endl;
}

void solve_factorization_steps()
{
    ll n;
    cin >> n;
    ll ans = 0;
    unordered_map<ll, ll> m = compute_factors(n);
    // At most log(n) factors
    for (auto it : m)
    {
        ll factor = it.first;
        ll factor_freq = it.second;
        ans += (factor_freq);
    }
    cout << (ans + m.size() - 1) << endl;
}

void solve_ncr_expression()
{
    ll n, m, p;
    cin >> n >> m >> p;
    cout << basic_ncr(n + m, p) - basic_ncr(n, p) - basic_ncr(m, p) - basic_ncr(n, 1) * basic_ncr(m, p - 1) - basic_ncr(n, 2) * basic_ncr(m, p - 2) - basic_ncr(n, 3) * basic_ncr(m, p - 3);
}

void solve_grid_subset_count()
{
    ll n, m;
    cin >> n >> m;
    unordered_map<ll, pair<ll, ll>> col_freq;
    unordered_map<ll, pair<ll, ll>> row_freq;
    vector<vector<ll>> v(n, vector<ll>(m, 0));
    for (int x = 0; x < v.size(); x++)
    {
        for (int y = 0; y < v[0].size(); y++)
        {
            ll num;
            cin >> num;
            v[x][y] = num;
        }
    }
    for (int x = 0; x < v.size(); x++)
    {
        ll freq = 0;
        for (int y = 0; y < v[0].size(); y++)
        {
            if (v[x][y] == 0)
                freq++;
        }
        row_freq[x] = {freq, m - freq};
    }
    for (int x = 0; x < v[0].size(); x++)
    {
        ll freq = 0;
        for (int y = 0; y < v.size(); y++)
        {
            if (v[y][x] == 0)
                freq++;
        }
        col_freq[x] = {freq, n - freq};
    }
    ll ans = (m * n);
    for (auto it : row_freq)
    {
        ll freq_1 = it.second.second;
        ll freq_0 = it.second.first;
        ans += ((1LL << freq_0) - (1 + freq_0));
        ans += ((1LL << freq_1) - (1 + freq_1));
    }
    for (auto it : col_freq)
    {
        ll freq_1 = it.second.second;
        ll freq_0 = it.second.first;
        ans += ((1LL << freq_0) - (1 + freq_0));
        ans += ((1LL << freq_1) - (1 + freq_1));
    }
    cout << ans << endl;
}

void solve_bounded_window_count()
{
    ll n, k, q;
    cin >> n >> k >> q;
    vector<ll> v(n);
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
    }
    ll l = 0;
    ll r = 0;
    ll ans = 0;
    while (l <= r && r < v.size())
    {
        if (v[r] > q)
        {
            if (((r - 1) - l) + 1 >= k)
            {
                ll val = (((r - 1) - l + 1) - k + 1);
                ans += (val * (val + 1)) / 2;
            }
            r++;
            l = r;
        }
        else
        {
            r++;
        }
    }
    if ((r - l) + 1 >= k)
    {
        ll val = (((r - 1) - l + 1) - k + 1);
        ans += (val * (val + 1)) / 2;
    }
    cout << ans << endl;
}

void solve_split_into_two()
{
    ll x;
    cin >> x;
    cout << 1 << " " << (x - 1) << endl;
}

void solve_linear_equation()
{
    string s;
    cin >> s;
    ll x_pos = -1;
    ll equal_pos = -1;
    char x_coeff = ' ';
    for (int x = 0; x < s.size(); x++)
    {
        if (s[x] == 'X')
            x_pos = x;
        else if (s[x] == '=')
            equal_pos = x;
    }
    if (x_pos == 0)
    {
        x_coeff = '+';
    }
    else if (s[x_pos - 1] == '=')
    {
        x_coeff = '+';
    }
    else
    {
        x_coeff = s[x_pos - 1];
    }
    string expr_1 = "";
    string expr_2 = "";
    string expr_3 = "";
    if (x_pos > equal_pos)
    {
        for (int x = equal_pos + 1; x <= x_pos - 1; x++)
        {
            expr_1.push_back(s[x]);
        }
        if (x_pos != equal_pos + 1)
        {
            expr_1.pop_back();
        }
        for (int x = x_pos + 1; x < s.size(); x++)
        {
            expr_2.push_back(s[x]);
        }
        for (int x = 0; x <= equal_pos - 1; x++)
        {
            expr_3.push_back(s[x]);
        }
    }
    else
    {
        for (int x = 0; x <= x_pos - 1; x++)
        {
            expr_1.push_back(s[x]);
        }
        if (x_pos != 0)
        {
            expr_1.pop_back();
        }
        for (int x = x_pos + 1; x <= equal_pos - 1; x++)
        {
            expr_2.push_back(s[x]);
        }
        for (int x = equal_pos + 1; x < s.size(); x++)
        {
            expr_3.push_back(s[x]);
        }
    }
    ll expr1_val = expr_val(expr_1);
    ll expr2_val = expr_val(expr_2);
    ll expr3_val = expr_val(expr_3);

    ll expr_cum = expr1_val + expr2_val;
    ll expr_total = expr3_val + (-1 * expr_cum);

    if (x_coeff == '-')
    {
        expr_total *= -1;
    }
    // cout << "Expr 1 " << expr_1 << " " << expr1_val << endl;
    // cout << "Expr 2 " << expr_2 << " " << expr2_val << endl;
    // cout << "Expr 3 " << expr_3 << " " << expr3_val << endl;
    // cout << "Coefficient of x - " << x_coeff << endl;
    // cout << "FINAL ANS " << expr_total << endl;
    cout << expr_total << endl;
}

void solve_stars_and_bars()
{
    ll n, m;
    cin >> n >> m;
    if (m < n)
    {
        cout << 0 << endl;
        return;
    }
    m -= n;
    ll num = (m + n - 1);
    ll r = n - 1;

    cout << ncr(num, r, MOD) % MOD << endl;
}

void solve_inclusion_exclusion_strings()
{
    ll n;
    cin >> n;
    ll a = binpow(26, n, MOD);
    ll b = binpow(5, n, MOD);
    ll c = binpow(21, n, MOD);
    cout << (((((a - b) + MOD) % MOD) - c) + MOD) % MOD << endl;
}

void solve_modular_expression()
{
    ll a, b, c, d, e, f, g, h;
    cin >> a >> b >> c >> d >> e >> f >> g >> h;

    ll val_1 = (binpow(a, b, MOD));
    ll val_2 = c;
    ll val_2_1 = ((((val_1 - val_2) + MOD) % MOD) * e) % MOD;
    ll val_3 = d;
    ll val_4_first = (g * h) % (MOD - 1);
    ll val_4_second = binpow(f, val_4_first, MOD);
    ll val_4 = (val_4_second * e) % MOD;

    ll p_first = ((val_2_1 - d) + MOD) % MOD;
    ll p = (p_first + val_4) % MOD;

    ll q = e;
    ll q_inverse = inverse(q, MOD);
    ll ans = (p * q_inverse) % MOD;
    cout << ans << endl;
}

void solve_line_coloring()
{
    ll n, k;
    cin >> n >> k;
    ll a = binpow(k - 1, n - 1, MOD);
    ll ans = (k * a) % MOD;
    cout << ans << endl;
    // cout<<(n*(n+1))/2<<endl;
}

void solve_top_k_multiset_queries()
{
    ll q, k;
    cin >> q >> k;

    RandomClass *obj = new RandomClass(k);
    while (q--)
    {
        ll q_type;
        ll num;
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
            ll query_ans = obj->query();
            cout << query_ans << endl;
        }
    }
}

void solve_coprime_classification()
{
    unordered_map<ll, ll> m;
    ll n;
    cin >> n;
    vector<ll> v(n);
    bool flag = true;
    ll gcd_total = -1;
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
        unordered_map<ll, ll> facts = compute_factors(num);
        for (auto it : facts)
        {
            if (m.count(it.first) == true)
            {
                flag = false;
            }
            m[it.first]++;
        }
        if (x >= 2)
        {
            gcd_total = gcd(gcd_total, v[x]);
        }
        else if (x == 1)
        {
            gcd_total = gcd(v[0], v[1]);
        }
    }
    if (flag == true)
    {
        cout << "pairwise coprime" << endl;
    }
    else if (gcd_total == 1)
    {
        cout << "setwise coprime" << endl;
    }
    else
    {
        cout << "not coprime" << endl;
    }
}

void solve_multiples_elimination()
{
    ll n, m;
    cin >> n >> m;
    vector<ll> v(1e6);
    for (int x = 1; x <= m; x++)
    {
        v[x] = x;
    }
    vector<ll> v2(n);
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v2[x] = num;
    }
    for (int x = 0; x < n; x++)
    {
        unordered_map<ll, ll> m2 = compute_factors(v2[x]);
        for (auto factor : m2)
        {
            if (v[factor.first] != -1)
            {

                for (ll y = factor.first; y <= m; y += factor.first)
                {
                    v[y] = -1;
                }
            }
        }
    }
    ll cnt = 0;
    for (ll x = 1; x <= m; x++)
    {
        if (v[x] != -1)
        {
            cnt++;
        }
    }
    cout << cnt << endl;
    for (ll x = 1; x <= m; x++)
    {
        if (v[x] != -1)
        {
            cout << x << endl;
        }
    }
}

void solve_non_divisible_count()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    unordered_map<ll, unordered_set<ll>> st;
    for (ll x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
        st[num].insert(x);
    }
    ll cnt = 0;
    for (ll x = 0; x < n; x++)
    {
        ll num = v[x];
        vector<ll> divs = single_divisor(num);

        for (auto divisor : divs)
        {
            if (st.count(divisor) == true && st[divisor].size() > 1)
            {
                cnt++;
                break;
            }
            else if (st.count(divisor) == true && st[divisor].size() == 1)
            {
                if (st[divisor].count(x) == false)
                {
                    cnt++;
                    break;
                }
            }
        }
    }
    cout << n - cnt << endl;
}

void solve_atc144()
{
    ll n;
    cin >> n;
    cout << atc_144(n) << endl;
}

void solve_square_divisors()
{
    // N^2*10^d
    // N*10d
    ll n, d;
    cin >> n >> d;
    vector<pair<ll, ll>> fact = Factors(n);
    unordered_map<ll, ll> m;
    for (auto it : fact)
    {
        ll base = it.first;
        ll exponent = it.second;
        m[base] = 2 * exponent;
    }
    m[2] += 2 * d;
    m[5] += 2 * d;
    ll ans = 1;
    bool flag = true;
    for (auto it : m)
    {
        if (it.second % 2 != 0)
        {
            flag = false;
        }
        ans = ((ans % MOD) * (it.second + 1)) % MOD;
    }
    ans = ans * 2;
    if (flag == true)
    {
        cout << ((ans - 1) + MOD) % MOD << endl;
    }
    else
    {
        cout << ans % MOD << endl;
    }
}

void solve_range_mod_sum()
{
    ll l, r, m;
    cin >> l >> r >> m;
    ll value_1 = GET(l - 1, m);
    ll value_2 = GET(r, m);
    cout << ((value_2 - value_1) + MOD) % MOD << endl;
}

void solve_euler_totient_single()
{
    ll n;
    cin >> n;
    vector<pair<ll, ll>> factors = Factors(n);
    ll ans = n;
    // 1-1/p = p-1*(p-2)* .....
    // denom = p1*p2*p3 ......

    for (auto it : factors)
    {
        ans /= it.first;
        ans *= (it.first - 1);
    }
    cout << ans << endl;
}

void solve_prime_square_check()
{
    ll n;
    cin >> n;
    vector<ll> input(n);
    for (int x = 0; x < n; x++)
    {
        cin >> input[x];
        ll root = sqrtl(input[x]);
        ll mul = (root * root);
        if (mul != input[x])
        {
            cout << "NO" << endl;
            continue;
        }
        else
        {
            if (primes_arr[root] == true)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
}

void solve_print_prime_factors()
{
    ll n;
    cin >> n;
    unordered_map<ll, ll> ans = compute_factors(n);
    for (auto num : ans)
    {
        cout << num << " ";
    }
    cout << endl;
}

void solve_segmented_sieve_print()
{
    ll a, b;
    cin >> a >> b;
    vector<ll> v = segmeneted_sieve(a, b);
    cout << v.size() << endl;
    for (ll x = 0; x < v.size(); x++)
    {
        cout << v[x] << " ";
    }
}

void solve_plus_minus_probability()
{
    string s1, s2;
    cin >> s1 >> s2;
    ll f_plus = 0;
    ll f_minus = 0;
    for (auto ch : s1)
    {
        if (ch == '+')
            f_plus++;
    }
    f_minus = (s1.size() - f_plus);
    vector<string> ans;
    rec(s2, 0, ans);
    long double cnt = 0;
    for (auto st : ans)
    {
        long double a = 0;
        long double b = 0;
        for (auto ch : st)
        {
            if (ch == '+')
                a++;
            else
            {
                b++;
            }
        }
        if (a == f_plus && b == f_minus)
            cnt++;
    }
    cout << fixed << setprecision(12) << (cnt / (long double)ans.size()) << endl;
}

void solve_common_gcd_check()
{
    ll n;
    cin >> n;
    vector<ll> a(n, 0);
    for (int x = 0; x < n; x++)
    {
        ll i;
        cin >> i;
        a[x] = i;
    }
    if (n == 1)
    {
        cout << "YES" << endl;
        return;
    }
    ll initial_gcd = gcd(a[0], a[1]);
    for (int x = 2; x < n; x++)
    {
        initial_gcd = gcd(initial_gcd, a[x]);
    }
    if (initial_gcd >= 2)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}

void solve_prime_and_divisor_count()
{
    ll n;
    cin >> n;
    vector<ll> divs = single_divisor(n);
    cout << divs.size() << endl;
    if (is_prime(n))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}

void solve_reorder_by_rank()
{
    ll m;
    cin >> m;
    vector<ll> a(m);
    vector<pair<ll, ll>> v;
    for (ll x = 0; x < m; x++)
    {
        ll num;
        cin >> num;
        a[x] = num;
    }
    for (ll x = 0; x < m; x++)
    {
        ll num;
        cin >> num;
        v.push_back({num, x});
    }
    sort(a.begin(), a.end());
    sort(v.begin(), v.end(), cmp);
    ll cnt = 0;
    vector<ll> ans(m, 0);
    for (auto pair : v)
    {
        ll idx = pair.second;
        ans[idx] = a[cnt];
        cnt++;
    }
    for (auto num : ans)
    {
        cout << num << " ";
    }
    cout << endl;
}

void solve_prefix_suffix_removal()
{
    ll n;
    cin >> n;
    string s = "";
    cin >> s;
    string prefix = "";
    string suffix = "";
    for (int x = 0; x < n; x++)
    {
        if (prefix.size() == 0)
        {
            prefix.push_back(s[x]);
        }
        else
        {
            if (prefix[prefix.size() - 1] == s[x])
            {
                prefix.push_back(s[x]);
            }
            else
            {
                break;
            }
        }
    }
    for (int x = (n - 1); x >= 0; x--)
    {
        if (suffix.size() == 0)
        {
            suffix.push_back(s[x]);
        }
        else
        {
            if (suffix[suffix.size() - 1] == s[x])
            {
                suffix.push_back(s[x]);
            }
            else
            {
                break;
            }
        }
    }
    if (prefix == suffix && prefix.size() == suffix.size() && prefix.size() == n)
    {
        ll a = (n * (n + 1)) % MOD;
        ll b = inverse(2, MOD);
        cout << (((a * b) % MOD)) << endl;
    }
    else
    {
        if (prefix[0] != suffix[0])
        {
            cout << (prefix.size() + suffix.size() + 1) << endl;
        }
        else
        {
            cout << ((prefix.size() + 1) * (suffix.size() + 1)) % MOD << endl;
        }
    }
}

void solve_tower_of_fours()
{
    ll k;
    cin >> k;
    // 4^2^k-2
    ll b = binpow(2, k, MOD - 1);
    ll c = binpow(4, b - 2, MOD);
    cout << (6 * c) % MOD << endl;
}

void solve_hexagon_cells()
{
    ll a;
    cin >> a;
    if (a == 1)
    {
        cout << 1 << endl;
        return;
    }
    cout << ((6 * a * (a - 1)) + 1) << endl;
}

void solve_euclidean_distance()
{
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    ll a = abs(x2 - x1);
    ll b = abs(y2 - y1);

    ll c = a * a;
    ll d = b * b;

    cout << setprecision(10) << sqrtl(c + d) << endl;
}

void solve_binadd_range_sum()
{
    ll l, r, m;
    cin >> l >> r >> m;
    ll ans = binadd(l, l + 1, m);
    for (int x = l + 2; x <= r; x += 1)
    {
        ans = binadd(ans, x, m);
    }
    cout << ans << endl;
}

void solve_pascal_rows()
{
    ll n;
    cin >> n;
    vector<vector<ll>> v = ncr_table_2(30, 30, MOD);
    for (auto arr : v)
    {
        if (n <= 0)
            break;
        for (auto num : arr)
        {
            if (num == 0)
                continue;
            else
            {

                cout << num << " ";
            }
        }
        cout << endl;
        n--;
    }
}

void solve_ncr_npr()
{
    ll a, b;
    cin >> a >> b;
    cout << ncr(a, b, MOD) << " " << npr(a, b, MOD) << endl;
}

void solve_gcd_lcm()
{
    ll a, b;
    cin >> a >> b;
    ll lc = lcm(a, b);
    ll gd = gcd(a, b);
    cout << gd << " " << lc << endl;
}

void solve_divisor_sum()
{
    ll n;
    cin >> n;
    vector<ll> v = single_divisor(n);
    ll ans = 0;
    for (auto num : v)
    {
        ans += num;
    }
    cout << ans << endl;
}

void solve_team_pairs_min_max()
{
    ll n, m;
    cin >> n >> m;

    ll kmax = -1;
    ll kmin = INT_MAX;

    kmax = ((n - m) * (n - m + 1)) / 2;

    ll rem = n % m;
    ll a = (n - rem) / m;

    if (rem == 0)
    {
        kmin = m * ((a * (a - 1)) / 2);
    }
    else
    {
        kmin = (m - rem) * ((a * (a - 1)) / 2);

        ll extraGroupPairs = ((a + 1) * a) / 2;
        kmin += rem * extraGroupPairs;
    }

    cout << kmin << " " << kmax << endl;
}

void solve_allowed_char_substrings()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    unordered_set<char> st;
    for (int i = 0; i < k; i++)
    {
        char c;
        cin >> c;
        st.insert(c);
    }
    ll count = 0;
    int l = 0, r = 0;
    while (r < n)
    {
        if (st.count(s[r]))
        {
            r++;
        }
        else
        {
            ll len = r - l;
            count += len * (len + 1) / 2;
            r++;
            l = r;
        }
    }
    ll len = r - l;
    count += len * (len + 1) / 2;
    cout << count << endl;
}

void solve_multiples_of_3_and_5()
{
    ll n;
    cin >> n;
    n--;
    ll num1, num2, num3;
    ll n1 = floor(n / 3);
    ll n2 = floor(n / 5);
    ll n3 = floor(n / 15);

    ll sum1 = 3 * ((n1 * (n1 + 1)) / 2);
    ll sum2 = 5 * ((n2 * (n2 + 1)) / 2);
    ll sum3 = 15 * ((n3 * (n3 + 1)) / 2);
    cout << ((sum1 + sum2) - sum3) << endl;
}

void solve_kth_two_b_string()
{
    ll n, k;
    cin >> n >> k;
    // n-2 a and 2 b
    string ans = "";
    for (int x = 0; x < n; x++)
    {
        ans.push_back('a');
    }
    ll total = 0;
    for (int x = (n - 2); x >= 0; x--)
    {
        // (n-2) which is the maximums rightmost postion of leftmost 'b'
        // then the right most positions can contribute to atmost  (n-(x+1)) types of different strings
        // then we can say that if k is the kth smalles lexicographical string then k <= count of strings till now .
        // then fix the position of the leftmost b str[x]='b', then we have to find the rightmost position of 'b'.
        ll curr_contribution = 0;
        curr_contribution = (n - (x + 1));
        // 3
        ll temp = total;
        // 6
        total += curr_contribution;
        if (total >= k)
        {
            ans[x] = 'b';
            ll idx = (n - (k - temp));
            ans[idx] = 'b';
            cout << ans << endl;
            return;
        }
    }
}

void solve_power_difference()
{
    ll n;
    cin >> n;
    // 3^3n-7^n
    ll component = (3 * n) % MOD;
    ll pow_1 = binpow(3, component, MOD);
    ll pow_2 = binpow(7, n, MOD);

    ll ans = (((pow_1 % MOD) - (pow_2 % MOD)) + MOD) % MOD;
    cout << ans << endl;
}

void solve_power_of_two_mod()
{
    ll n;
    cin >> n;
    ll ans = binpow(2, n, MOD);
    cout << (ans % MOD) << endl;
}

void solve_sum_powers_of_two()
{
    ll n;
    cin >> n;
    ll ans = 0;
    for (ll x = 1; x <= n; x++)
    {
        ans = (ans + binpow(2, x)) % MOD;
    }
    cout << ans << endl;
}

void solve_max_diff_pairs()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    unordered_map<ll, ll> m;
    for (ll x = 0; x < v.size(); x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
        m[num]++;
    }
    sort(v.begin(), v.end());
    ll diff = v[v.size() - 1] - v[0];
    ll n1 = m[v[v.size() - 1]];
    if (diff == 0)
    {
        cout << diff << " " << (n * (n - 1)) / 2 << endl;
        return;
    }
    ll n2 = m[v[0]];
    ll ans = n1 * n2;
    cout << diff << " " << ans << endl;
}

void solve_two_letter_rank()
{
    string s;
    cin >> s;
    char ch1 = s[0];
    char ch2 = s[1];
    int num1 = 26 - ('z' - ch1);
    int num2 = 26 - ('z' - ch2);
    int offset = (num1 - 1) * 25;
    int rank = 0;
    if (num2 > num1)
    {
        rank = offset + (num2 - 1);
    }
    else
    {
        rank = offset + num2;
    }
    cout << rank << endl;
}

void solve_grid_paths()
{
    ll n, m;
    cin >> n >> m;
    ll final = ncr((n + m), n, MOD);
    cout << final << endl;
}

void solve_choose_four()
{
    ll n;
    cin >> n;
    ll num1 = (n * (n - 1)) % MOD;
    ll num2 = (num1 * (n - 2)) % MOD;
    ll num3 = (num2 * (n - 3)) % MOD;
    ll deno = 24;
    ll dinv = inverse(deno, MOD);
    ll ans = (num3 * dinv) % MOD;
    cout << ans << endl;
}

void solve_derangement_count()
{
    ll n;
    cin >> n;
    dearrangement(n);
    ll ans = dearrange[n];
    cout << ans % MOD << endl;
}

void solve_power_of_two_check()
{
    ll n;
    cin >> n;
    for (int x = 1; x <= 32; x++)
    {
        if (((1 << x) & n) == n)
        {
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
}

void solve_circles_touch()
{
    ll x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2;
    cin >> x3 >> y3 >> x4 >> y4;

    ll center_1_x = (x1 + x2) * 2;
    ll center_1_y = (y1 + y2) * 2;

    pair<ll, ll> center1 = {center_1_x, center_1_y};

    ll center_2_x = (x3 + x4) * 2;
    ll center_2_y = (y3 + y4) * 2;

    pair<ll, ll> center2 = {center_2_x, center_2_y};

    ll dist_1 = (((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
    ll dist_2 = (((x3 - x4) * (x3 - x4)) + ((y3 - y4) * (y3 - y4)));

    ll dist = (((center1.first - center2.first) * (center1.first - center2.first)) + ((center1.second - center2.second) * (center1.second - center2.second)));
    dist = sqrt(dist);

    ll radius_1 = sqrt(dist_1) * 2;
    ll radius_2 = sqrt(dist_2) * 2;
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
    if ((radius_1 + radius_2) > dist)
    {
        cout << "NO" << endl;
        return;
    }
    else if ((radius_1 + radius_2) < dist)
    {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
}

void solve_range_even_odd_sums()
{
    ll a, b;
    cin >> a >> b;
    ll mini = min(a, b);
    ll maxi = max(a, b);
    a = mini;
    b = maxi;
    ll total_sum = ((b * (b + 1))) / 2;
    ll total_even_numbers = b / 2;
    ll total_odd_numbers = b - total_even_numbers;

    ll prev = ((a - 1) * (a)) / 2;

    ll inclusive_sum = ((total_sum - prev));

    ll even_sum = 0;
    ll odd_sum = 0;

    ll s = (a - 1) / 2;
    ll e = (s * (s + 1));
    ll e_total = (total_even_numbers * (total_even_numbers + 1));
    even_sum = ((e_total - e));

    odd_sum = ((inclusive_sum - even_sum));
    cout << inclusive_sum << endl;
    cout << even_sum << endl;
    cout << odd_sum << endl;
}

void solve_xor_sequence()
{
    ll a, b, q;
    cin >> a >> b >> q;
    ll c = a ^ b;
    ll rem = q % 3;
    if (q == 1)
    {
        cout << a << endl;
        return;
    }
    if (q == 2)
    {
        cout << b << endl;
        return;
    }
    if (rem == 0)
    {
        cout << c << endl;
        return;
    }
    else if (rem == 1)
    {
        cout << a << endl;
        return;
    }
    else
    {
        cout << b << endl;
    }
}

void solve_quadratic_root()
{
    ll n;
    cin >> n;
    // n2+n <= 2*n
    // n2+n-2*n<=0
    //-1+-1-8n/2
    ll r = sqrt(1 + (8 * n));
    ll root = (-1 + r) / 2;
    cout << root << endl;
}

void solve()
{

}
// Solving via contribution framework of type extended ends .
int maxSubArray(vector<int> &nums)
{
    int ans = INT_MIN;
    int prev = 0;
    for (int x = 0; x < nums.size(); x++)
    {
        prev = max(prev + nums[x], nums[x]);
        ans = max(ans, prev);
    }
    return ans;
}
int main()
{
    // O(N)
    factorial(MOD);
    // O(log log(n))
    compute_primes();
    compute_co_prime();
    // O(log log p)
    build_spf(1000000);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    // t = 1;
    while (t--)
    {
        solve();
    }
}

/*
    Contribution technique.
    inverting the relation if possible.
        i)Atomic item contribution.
        ii)Contribution on pivot first form extended ends .
        iii)Cumulative data structures.
    1) Number of subarrays.
    2) Sum of subarrays by extended means as well.
    3) Sum of all triplets.
    4) (i,j) arr[i] > arr[j] i < j finding sum of inversions over all subarrays.
    5) Products of all subarrays.
    6) Kadanes algorithm or maximum subarray sum.
    7) Prefix sums and contribution technique 3rd form that is cumulative datas structures.

// */
// /*
// 0 0 0 0 0 0
// 0 -1 1 4 0 2
// 0 -1 1 4 0 6
// 0 0 4 11 10 21
// 0 -1 -2 3 5 20
// 0 -1 -5 -5 0 9

// */

/*
    arr(n) and m ranges;
    with each range consisting of {li,ri};
    arr[li]....+arr[ri] into s and sort arr;
    Q queries kth query to return kth smallest;

*/

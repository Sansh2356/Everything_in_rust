#include <bits/stdc++.h>
typedef long long ll;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update>
typedef long long ll;
using namespace std;

const int MOD = 1e9 + 7;
const long double EPSILON = 1e-9; // or 10^-12

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
long long gcdSum(vector<int> &nums)
{
    vector<ll> pf_max(nums.size());
    vector<ll> pf_gcd(nums.size());

    pf_max[0] = nums[0];

    for (ll x = 1; x < nums.size(); x++)
    {
        pf_max[x] = max(pf_max[x - 1], (ll)nums[x]);
    }
    pf_gcd[0] = gcd(min(pf_max[0], (ll)nums[0]), max(pf_max[0], (ll)nums[0]));
    for (ll x = 1; x < nums.size(); x++)
    {
        ll maxi = pf_max[x];
        pf_gcd[x] = gcd(min(pf_max[x], (ll)nums[x]), max(pf_max[x], (ll)nums[x]));
    }
    sort(pf_gcd.begin(), pf_gcd.end());
    ll l = 0;
    ll r = pf_gcd.size() - 1;
    ll sum = 0;
    while (l != r && r > l)
    {
        sum += gcd(pf_gcd[l], pf_gcd[r]);
        r--;
        l++;
    }
    return sum;
}
string largestNumber(vector<int> &nums)
{

    sort(nums.begin(), nums.end());
    string ans = "";
    for (int x = 0; x < nums.size(); x++)
    {
        ans += to_string(nums[x]);
    }
    if (ans[0] == '0')
    {

        string s = "0";
        for (int x = 0; x < ans.length(); x++)
        {
            if (ans[x] != '0')
                s.push_back(ans[x]);
        }
        return s;
    }
    return ans;
}
void towers()
{
    ll n;
    cin >> n;
    ll tower_no = 0;
    map<ll, ll> st;
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        if (st.size() == 0)
        {
            tower_no++;
            st.insert({num, 1});
        }
        else
        {
            auto it = st.upper_bound(num);
            if (it == st.end())
            {
                tower_no++;
            }
            else
            {
                st[it->first]--;
                if (st[it->first] <= 0)
                {
                    st.erase(it);
                }
            }
            st[num]++;
        }
    }
    cout << tower_no << endl;
}

/*
 is a result about the representation of integers as sums of Fibonacci numbers. It states that every positive integer can be represented uniquely as the sum of one or more distinct Fibonacci numbers in such a way that the sum does not include any two consecutive Fibonacci numbers.
*/
vector<ll> arr(50, -1);
ll fibonacci(ll num)
{
    if (num == 0)
        return 0;
    if (num == 1 || num == 2)
    {
        return 1;
    }
    if (arr[num] != -1)
        return arr[num];
    return arr[num] = fibonacci(num - 1) + fibonacci(num - 2);
}
// Pair up a[x] with b[x], sort by (a[x]+b[x]) descending and let Alice pick the
// even indexed a values and Bob the odd indexed b values.
void solve_alice_bob_pair_game()
{
    ll n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> b(n);
    vector<pair<ll, pair<ll, ll>>> c(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> a[x];
    }
    for (ll x = 0; x < n; x++)
    {
        cin >> b[x];
    }
    for (ll x = 0; x < n; x++)
    {
        c[x] = {(a[x] + b[x]), {a[x], b[x]}};
    }
    sort(c.begin(), c.end(), [](pair<ll, pair<ll, ll>> &a, pair<ll, pair<ll, ll>> &b) -> bool
         { return a.first > b.first; });
    ll alice_sum = 0;
    ll bob_sum = 0;
    for (ll x = 0; x < n; x++)
    {
        if (x % 2 == 0)
        {
            alice_sum += c[x].second.first;
        }
        else
        {
            bob_sum += c[x].second.second;
        }
    }
    if (alice_sum > bob_sum)
    {
        cout << "Alice \n";
    }
    else if (bob_sum > alice_sum)
    {
        cout << "Bob \n";
    }
    else
    {
        cout << "Tie \n";
    }
}

// Zeckendorf representation - greedily subtracting the largest fibonacci number
// <= k gives the minimum count of fibonacci terms summing up to k.
void solve_min_fibonacci_terms()
{
    for (ll x = 1; x <= 50; x++)
    {
        arr[x] = fibonacci(x);
    }
    ll k;
    cin >> k;
    ll ans = 0;
    while (k > 0)
    {
        ll l = 0;
        ll r = arr.size() - 1;
        ll mid = (l + r) / 2;
        ll idx = -1;
        while (l <= r)
        {
            mid = (l + r) / 2;
            if (arr[mid] > k)
            {
                r = mid - 1;
            }
            else
            {
                idx = mid;
                l = mid + 1;
            }
        }
        k -= arr[idx];
        ans++;
    }
    cout << ans << "\n";
}

// Processing the (num1,num2) pairs ordered by the difference num1-num2 kept on
// top of the priority queue.
void solve_pq_pair_difference()
{
    ll n;
    cin >> n;
    priority_queue<pair<ll, pair<ll, ll>>> pq;
    for (ll x = 0; x < n; x++)
    {
        ll num1;
        ll num2;
        cin >> num1 >> num2;
        pq.push({num1 - num2, {num1, num2}});
    }
    ll ans = 0;
    ll rem = 0;
    while (pq.empty() != true)
    {
        if (ans == 0)
        {
            ans = pq.top().second.first;
            rem = pq.top().first;
        }
        else
        {
            if (rem < pq.top().second.first)
            {
                ans += abs(rem - pq.top().second.first);
                rem = pq.top().first;
            }
            else
            {
                rem -= pq.top().second.second;
            }
        }
        pq.pop();
    }
    cout << ans << "\n";
}

// Every element can only be shifted by multiples of gcd(x,y), so each value has
// to be congruent to its target index modulo that gcd.
void solve_permutation_gcd_shift()
{
    ll n, x, y;
    cin >> n >> x >> y;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
    }
    ll gcd_val = gcd(min(x, y), max(x, y));

    for (ll x = 0; x < n; x++)
    {
        if (abs((x + 1) - v[x]) % gcd_val != 0)
        {
            cout << "No" << "\n";
            return;
        }
    }
    cout << "Yes" << "\n";
}

// Pushing the excess of every position onto the next one and then checking
// whether the resulting array is strictly increasing.
void solve_increasing_after_carry()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        v[x] = num;
    }
    for (ll x = 0; x <= n - 1; x++)
    {
        if (v[x] == 1)
            continue;
        else
        {
            ll val = abs(v[x] - (x + 1));
            if (x + 1 < n)
            {
                v[x + 1] += val;
                v[x] = (x + 1);
            }
        }
    }
    for (ll x = 0; x < n && (x + 1) < n; x++)
    {
        if (v[x + 1] <= v[x])
        {
            cout << "No" << "\n";
            return;
        }
    }
    cout << "Yes" << "\n";
}

// Longest run of '#' characters, every operation covering 2 of them.
void solve_max_hash_segment()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;
    ll maxi = 0;
    ll len = 0;
    for (ll x = 0; x < n; x++)
    {
        if (s[x] == '#')
        {
            len++;
        }
        else if (s[x] != '#')
        {
            maxi = max(len, maxi);
            len = 0;
        }
    }
    maxi = max(len, maxi);
    cout << ceil((double)maxi / (double)2) << "\n";
}

// a*x + b*y = c is solvable only when gcd(a,b) divides c, the brute force below
// additionally looks for the non negative solution pair.
void solve_linear_diophantine()
{
    ll a, b, c;
    cin >> a >> b >> c;
    ll gcd_val = gcd(a, b);
    if (c % gcd_val != 0)
    {
        cout << "No" << "\n";
    }
    else
    {
        bool flag = false;
        for (ll x = 0; x <= 10000; x++)
        {
            for (ll y = 0; y <= 10000; y++)
            {
                if (((x * a) + (b * y)) == c)
                {
                    cout << "Yes" << "\n";
                    return;
                }
            }
        }
        if (flag == false)
        {
            cout << "No" << "\n";
        }
    }
}

// Processing the elements in increasing order of their value and deriving the
// removal time of a position from the already resolved neighbours of it.
void solve_neighbour_removal_time()
{
    ll n;
    cin >> n;
    vector<pair<ll, ll>> v(n);
    vector<pair<ll, ll>> v_temp(n);

    vector<ll> time(n, INT_MAX);
    for (ll x = 0; x < n; x++)
    {
        ll num;
        cin >> num;

        v[x] = {num, x};
    }
    v_temp = v;
    sort(v.begin(), v.end());
    for (ll x = 0; x < n; x++)
    {
        ll orig_idx = v[x].second;
        ll val = v[x].first;
        if (orig_idx + 1 < n && orig_idx - 1 >= 0)
        {

            if (time[orig_idx + 1] == INT_MAX && time[orig_idx - 1] == INT_MAX)
            {
                time[orig_idx] = min(1LL, time[orig_idx]);
            }
            else if (time[orig_idx + 1] == INT_MAX && time[orig_idx - 1] != INT_MAX)
            {
                ll v1 = v_temp[orig_idx].first;
                ll v2 = v_temp[orig_idx - 1].first;
                if (v1 > v2)
                {
                    time[orig_idx] = time[orig_idx - 1] + 1;
                }

                else
                {
                    time[orig_idx] = 1;
                }
            }
            else if (time[orig_idx + 1] != INT_MAX && time[orig_idx - 1] == INT_MAX)
            {
                ll v1 = v_temp[orig_idx].first;
                ll v2 = v_temp[orig_idx + 1].first;
                if (v1 > v2)
                {
                    time[orig_idx] = time[orig_idx + 1] + 1;
                }
                else
                {
                    time[orig_idx] = 1;
                }
            }
            else
            {
                ll v1 = v_temp[orig_idx].first;
                ll v2 = v_temp[orig_idx + 1].first;
                ll v3 = v_temp[orig_idx - 1].first;
                if (v1 > v2 && v1 > v3)
                {
                    time[orig_idx] = max(time[orig_idx + 1], time[orig_idx - 1]) + 1;
                }
                else if (v1 < v2 && v1 < v3)
                {
                    time[orig_idx] = min(1LL, time[orig_idx]);
                }
                else if (v1 > v2 && v1 < v3)
                {
                    time[orig_idx] = time[orig_idx - 1] + 1;
                }
                else if (v1 > v3 && v1 < v2)
                {
                    time[orig_idx] = time[orig_idx + 1] + 1;
                }
                else if (v1 == v2 && v1 != v3)
                {
                    if (v3 > v1)
                    {
                        time[orig_idx] = time[orig_idx + 1];
                    }
                    else if (v3 < v1)
                    {
                        time[orig_idx] = time[orig_idx - 1] + 1;
                    }
                }
                else if (v1 == v3 && v1 != v2)
                {
                    if (v2 > v1)
                    {
                        time[orig_idx] = time[orig_idx - 1];
                    }
                    else if (v2 < v1)
                    {
                        time[orig_idx] = time[orig_idx + 1] + 1;
                    }
                }
                else if (v1 == v2 && v1 == v3)
                {
                    time[orig_idx] = time[orig_idx + 1];
                }
                else
                {
                    time[orig_idx] = time[orig_idx + 1];
                }
            }
        }
        else if (orig_idx + 1 < n)
        {

            if (time[orig_idx + 1] == INT_MAX)
            {
                time[orig_idx] = 1;
            }
            else
            {
                ll v1 = v_temp[orig_idx].first;
                ll v2 = v_temp[orig_idx + 1].first;

                if (v1 > v2)
                    time[orig_idx] = time[orig_idx + 1] + 1;
                else
                    time[orig_idx] = 1;
            }
        }
        else if (orig_idx - 1 >= 0)
        {
            if (time[orig_idx - 1] == INT_MAX)
            {
                time[orig_idx] = 1;
            }
            else
            {
                ll v1 = v_temp[orig_idx].first;
                ll v2 = v_temp[orig_idx - 1].first;

                if (v1 > v2)
                    time[orig_idx] = time[orig_idx - 1] + 1;
                else
                    time[orig_idx] = 1;
            }
        }
    }
    ll ans = 0;
    for (auto i : time)
    {
        ans += i;
    };
    cout << ans << "\n";
}
void simple_qe()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    ll sum = 0;
    ll square_sum = 0;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        sum += v[x];
        square_sum += (v[x] * v[x]);
    }
    ll min_x = (sum / n);
    ll ans = INT_MAX;
    ll sum_1 = 0;
    ll sum_2 = 0;
    for (ll x = 0; x < n; x++)
    {
        sum_1 += ((v[x] - min_x) * (v[x] - min_x));
        sum_2 += ((v[x] - (min_x + 1)) * (v[x] - (min_x + 1)));
    }
    ans = min(sum_1, sum_2);

    cout << ans << "\n";
}
ll subarraySum(vector<ll> &nums, ll k)
{
    ll cnt = 0;
    unordered_map<ll, ll> m;
    ll cum_sum = 0;
    m[cum_sum] = 1;
    for (ll x = 0; x < nums.size(); x++)
    {
        cum_sum += nums[x];
        if (m.count((cum_sum - k)) == true)
            cnt += m[(cum_sum - k)];
        m[cum_sum] += 1;
    }
    return cnt;
}
// Using pigeon hole principle and prefix sum
// modulo will repeat itself always for atleast 1 value .
vector<ll> subset_divisible_n()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    unordered_map<ll, ll> m;
    vector<ll> pf_arr(n + 1);
    pf_arr[0] = 0;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        pf_arr[x + 1] = v[x] + pf_arr[x];
    }
    m[0] = -1;
    ll i = -1;
    ll j = -1;
    for (ll x = 0; x < n; x++)
    {
        if (m.count(pf_arr[x + 1] % n))
        {
            j = m[pf_arr[x + 1]] + 1;
            i = x;
            break;
        }
        m[pf_arr[x + 1] % n] = x;
    }
    cout << i << " " << j << endl;
    vector<ll> ans;
    for (ll x = j; x <= i; x++)
        ans.push_back(v[x]);
    for (auto i : ans)
        cout << i << " ";
    cout << "\n";
    return ans;
}
vector<ll> next_greater_element(vector<ll> v)
{
    ll n = v.size();
    vector<ll> nge(v.size());
    for (ll x = v.size() - 1; x >= 0; x--)
    {
        nge[x] = x + 1;
        while (nge[x] != n && v[x] > v[nge[x]])
        {
            nge[x] = nge[nge[x]];
        }
    }
    for (ll x = 0; x < n; x++)
    {
        if (nge[x] == n)
        {
            cout << "No element which is next greater than " << v[x] << " exists \n";
        }
        else
        {
            cout << "Element greater than " << v[x] << " is " << v[nge[x]] << "\n";
        }
    }
    cout << "\n";
    return nge;
}
vector<ll> next_greater_equal_element(vector<ll> v)
{
    ll n = v.size();
    vector<ll> nge(v.size());
    for (ll x = v.size() - 1; x >= 0; x--)
    {
        nge[x] = x + 1;
        while (nge[x] != n && v[x] > v[nge[x]])
        {
            nge[x] = nge[nge[x]];
        }
    }
    for (ll x = 0; x < n; x++)
    {
        if (nge[x] == n)
        {
            cout << "No element which is next greater than or equal to" << v[x] << " exists \n";
        }
        else
        {
            cout << "Element greater than or equal to" << v[x] << " is " << v[nge[x]] << "\n";
        }
    }
    cout << "\n";
    return nge;
}
vector<ll> previous_greater_element(vector<ll> v)
{
    ll n = v.size();
    vector<ll> pge(v.size());
    for (ll x = 0; x < n; x++)
    {
        pge[x] = x - 1;
        while (pge[x] != -1 && v[x] >= v[pge[x]])
        {
            pge[x] = pge[pge[x]];
        }
    }
    for (ll x = 0; x < n; x++)
    {
        if (pge[x] == -1)
        {
            cout << "No element which is previous greater than " << v[x] << " exists \n";
        }
        else
        {
            cout << "Element greater than " << v[x] << " is " << v[pge[x]] << "\n";
        }
    }
    cout << "\n";
    return pge;
}
vector<ll> previous_greater_equal_element(vector<ll> v)
{
    ll n = v.size();
    vector<ll> pge(v.size());
    for (ll x = 0; x < n; x++)
    {
        pge[x] = x - 1;
        while (pge[x] != -1 && v[x] > v[pge[x]])
        {
            pge[x] = pge[pge[x]];
        }
    }
    for (ll x = 0; x < n; x++)
    {
        if (pge[x] == -1)
        {
            cout << "No element which is previous greater than or equal" << v[x] << " exists \n";
        }
        else
        {
            cout << "Element greater than or equal" << v[x] << " is " << v[pge[x]] << "\n";
        }
    }
    cout << "\n";
    return pge;
}
vector<ll> next_smaller_element(vector<ll> v)
{
    ll n = v.size();
    vector<ll> nse(v.size());
    for (ll x = v.size() - 1; x >= 0; x--)
    {
        nse[x] = x + 1;
        while (nse[x] != n && v[x] <= v[nse[x]])
        {
            nse[x] = nse[nse[x]];
        }
    }
    for (ll x = 0; x < n; x++)
    {
        if (nse[x] == n)
        {
            cout << "No element which is next smallest than " << v[x] << " exists \n";
        }
        else
        {
            cout << "Element next smallest than " << v[x] << " is " << v[nse[x]] << "\n";
        }
    }
    cout << "\n";
    return nse;
}

vector<ll> next_smaller_equal_element(vector<ll> v)
{
    ll n = v.size();
    vector<ll> nse(v.size());
    for (ll x = v.size() - 1; x >= 0; x--)
    {
        nse[x] = x + 1;
        while (nse[x] != n && v[x] < v[nse[x]])
        {
            nse[x] = nse[nse[x]];
        }
    }
    for (ll x = 0; x < n; x++)
    {
        if (nse[x] == n)
        {
            cout << "No element which is next smaller than or equal to" << v[x] << " exists \n";
        }
        else
        {
            cout << "Element next smaller than or equal to" << v[x] << " is " << v[nse[x]] << "\n";
        }
    }
    cout << "\n";
    return nse;
}
vector<ll> previous_smaller_element(vector<ll> v)
{
    ll n = v.size();
    vector<ll> pse(v.size());
    for (ll x = 0; x < n; x++)
    {
        pse[x] = x - 1;
        while (pse[x] != -1 && v[x] <= v[pse[x]])
        {
            pse[x] = pse[pse[x]];
        }
    }
    for (ll x = 0; x < n; x++)
    {
        if (pse[x] == -1)
        {
            cout << "No element which is previous smallest than " << v[x] << " exists \n";
        }
        else
        {
            cout << "Element previous smallest than " << v[x] << " is " << v[pse[x]] << "\n";
        }
    }
    cout << "\n";
    return pse;
}
vector<ll> previous_smaller_equal_element(vector<ll> v)
{
    ll n = v.size();
    vector<ll> pse(v.size());
    for (ll x = 0; x < n; x++)
    {
        pse[x] = x - 1;
        while (pse[x] != -1 && v[x] < v[pse[x]])
        {
            pse[x] = pse[pse[x]];
        }
    }
    // for (ll x = 0; x < n; x++)
    // {
    //     if (pse[x] == -1)
    //     {
    //         cout << "No element which is previous smallest than or equal to" << v[x] << " exists \n";
    //     }
    //     else
    //     {
    //         cout << "Element previous smallest than or equal to" << v[x] << " is " << v[pse[x]] << "\n";
    //     }
    // }
    // cout << "\n";
    return pse;
}
vector<ll> next_greater_element_circular(vector<ll> v)
{
    ll n = v.size();
    vector<ll> nge(v.size());
    for (ll x = v.size() - 1; x >= 0; x--)
    {
        nge[x] = (x + 1);
        while (nge[x] != n && v[x] >= v[nge[x]])
        {
            nge[x] = nge[nge[x]];
        }
    }
    vector<ll> ans;
    for (ll x = 0; x < n / 2; x++)
    {
        if (nge[x] == n)
        {
            ans.push_back(-1);
        }
        else
        {
            ans.push_back(v[nge[x]]);
        }
    }
    return ans;
}
ll largestRectangleArea(vector<ll> &heights)
{
    ll ans = LLONG_MAX;
    ll n = heights.size();
    vector<ll> pse = previous_smaller_element(heights);
    vector<ll> nse = next_smaller_element(heights);
    for (int x = 0; x < heights.size(); x++)
    {

        ans = max(ans, (heights[x] * (nse[x] - pse[x] - 1)));
    }
    return ans;
}
void subset_original_arr()
{
    ll n;
    cin >> n;
    multiset<ll> s1;
    vector<ll> v(pow(2, n));
    for (ll x = 0; x < pow(2, n); x++)
    {
        cin >> v[x];
        s1.insert(v[x]);
    }
    s1.erase(s1.begin());
    multiset<ll> s3;
    multiset<ll> s2;
    s2.insert(0);
    while (s1.empty() == false)
    {
        ll smallest = *s1.begin();
        multiset<ll> s4;
        for (auto it : s2)
        {
            s4.insert(it + smallest);
        }
        for (auto it : s4)
        {
            s1.erase(s1.find(it));
            s2.insert(it);
        }
        s3.insert(smallest);
    }
    for (auto it : s3)
    {
        cout << it << " ";
    }
    cout << "\n";
}
// Single symbol based can also be solved using a single variable of
// depth which is intutive indicator of each depth being matched .
bool valid_parentheses()
{
    string s;
    cin >> s;
    unordered_map<char, int> m;
    m['('] = 1;
    m[')'] = -1;
    m['{'] = 2;
    m['}'] = -2;
    m['['] = 3;
    m[']'] = -3;
    stack<int> st;
    bool flag = true;
    for (ll x = 0; x < s.length(); x++)
    {
        if (st.size() == 0 && m[s[x]] < 0)
        {
            flag = false;
            break;
        }
        else if (st.size() == 0 && m[s[x]] > 0)
        {
            st.push(m[s[x]]);
        }
        else
        {
            if (m[s[x]] > 0)
                st.push(m[s[x]]);
            else if (m[s[x]] < 0)
            {
                if (st.top() + m[s[x]] == 0)
                {
                    st.pop();
                }
                else
                {
                    flag = false;
                    break;
                }
            }
        }
    }
    if (flag == false || st.size() != 0)
        return false;
    return true;
}
ll min_number_parentheses()
{
    string s;
    cin >> s;
    unordered_map<char, int> m;
    m['('] = 1;
    m[')'] = -1;
    m['{'] = 2;
    m['}'] = -2;
    m['['] = 3;
    m[']'] = -3;
    stack<int> st;
    for (ll x = 0; x < s.length(); x++)
    {
        if (st.size() == 0 && m[s[x]] < 0)
        {
            st.push(m[s[x]]);
        }
        else if (st.size() == 0 && m[s[x]] > 0)
        {
            st.push(m[s[x]]);
        }
        else
        {
            if (m[s[x]] > 0)
                st.push(m[s[x]]);
            else if (m[s[x]] < 0)
            {
                if (st.top() + m[s[x]] == 0)
                {
                    st.pop();
                }
                else
                {
                    st.push(m[s[x]]);
                }
            }
        }
    }
    return st.size();
}
// Monotonic deque for maintaining minimum or maximum element
// within a window of length k.
class MonotonicDeque
{
public:
    deque<ll> dq;
    void insert(ll value)
    {
        while (dq.empty() == false && dq.back() > value)
        {
            dq.pop_back();
        }
        dq.push_back(value);
    }
    void erase(ll v)
    {
        if (dq.empty() == false && dq.front() == v)
        {
            dq.pop_front();
        }
    }
    ll min_value()
    {
        return dq.front();
    }
};
// Minimum of every window of length k using a monotonic deque.
void solve_sliding_window_min_deque()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    MonotonicDeque st = MonotonicDeque();
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        st.insert(v[x]);

        if ((x - k) >= 0)
        {
            st.erase(v[x - k]);
        }
        if (x >= k - 1)
        {
            cout << st.min_value() << " ";
        }
    }
    cout << "\n";
}

// Maximum of every window of length k maintained via a multiset.
void solve_sliding_window_max_multiset()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    multiset<ll> st;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        st.insert(v[x]);

        if (((ll)st.size() - k) > 0)
        {
            st.erase(st.find(v[x - k]));
        }
        if (st.size() == k)
        {
            cout << *(st.rbegin()) << " ";
        }
    }
    cout << "\n";
}

// Four query types over a sorted array : value/index of the first element
// >= x (lower_bound) and > x (upper_bound).
void solve_sorted_array_bound_queries()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    while (q--)
    {
        ll t, x;
        cin >> t >> x;
        if (t == 1)
        {
            auto it = lower_bound(v.begin(), v.end(), x);
            if (it != v.end())
            {
                cout << *it << "\n";
            }
            else
            {
                cout << "-1" << "\n";
            }
        }
        else if (t == 2)
        {
            auto it = upper_bound(v.begin(), v.end(), x);
            if (it != v.end())
            {
                cout << *it << "\n";
            }
            else
            {
                cout << "-1" << "\n";
            }
        }
        else if (t == 3)
        {
            auto it = lower_bound(v.begin(), v.end(), x);
            if (it != v.end())
            {
                cout << it - v.begin() << "\n";
            }
            else
            {
                cout << "-1" << "\n";
            }
        }
        else
        {
            auto it = upper_bound(v.begin(), v.end(), x);
            if (it != v.end())
            {
                cout << it - v.begin() << "\n";
            }
            else
            {
                cout << "-1" << "\n";
            }
        }
    }
}

// Maximum count of items buyable with budget m : sort , prefix sum and
// binary search the largest prefix that fits inside the budget.
void solve_max_items_within_budget_queries()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    vector<ll> pf_arr(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    sort(v.begin(), v.end());
    pf_arr[0] = v[0];
    for (ll x = 1; x < n; x++)
    {
        pf_arr[x] = pf_arr[x - 1] + v[x];
    }
    while (q--)
    {
        ll m;
        cin >> m;
        auto it = upper_bound(pf_arr.begin(), pf_arr.end(), m);
        cout << it - pf_arr.begin() << "\n";
    }
}

// Trapping rain water : water above a bar is bounded by the smaller of the
// running prefix maximum and suffix maximum around it.
void solve_trapping_rain_water()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    vector<ll> pf_arr(n);
    vector<ll> sf_arr(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    pf_arr[0] = v[0];
    for (ll x = 1; x < n; x++)
    {
        pf_arr[x] = max(pf_arr[x - 1], v[x]);
    }
    sf_arr[n - 1] = v[n - 1];
    for (ll x = n - 2; x >= 0; x--)
    {
        sf_arr[x] = max(sf_arr[x + 1], v[x]);
    }
    ll ans = 0;
    for (ll x = 0; x < n; x++)
    {
        ans += min(pf_arr[x], sf_arr[x]) - v[x];
    }
    cout << ans << "\n";
}

// Maximum of the minimums for every window size : each element is the
// minimum of the segment (pse , nse) , afterwards a suffix maximum fills
// the window sizes that were never hit directly.
// [5,4,2,INT_MIN,INT_MIN,1]
// [5,4,2,1,1,1] ---->  ANS
void solve_max_of_min_for_every_window()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    vector<ll> pse = previous_smaller_element(v);
    vector<ll> nse = next_smaller_element(v);
    vector<ll> suffix_arr(n + 1, INT_MIN);
    for (ll x = 0; x < n; x++)
    {
        ll segment_length = nse[x] - pse[x] - 1;
        suffix_arr[segment_length] = max(v[x], suffix_arr[segment_length]);
    }
    for (ll x = suffix_arr.size() - 2; x >= 0; x--)
    {
        suffix_arr[x] = max(suffix_arr[x], suffix_arr[x + 1]);
    }
    suffix_arr[0] = -1;
    for (auto i : suffix_arr)
    {
        if (i >= 0)
        {
            cout << i << " ";
        }
    }
    cout << "\n";
}

// 1-indexed position of the previous smaller element , 0 when none exists.
void solve_previous_smaller_element_indices()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    vector<ll> pse = previous_smaller_element(v);
    for (auto &it : pse)
    {
        if (it == -1)
            cout << 0 << " ";
        else
        {
            cout << it + 1 << " ";
        }
    }
    cout << "\n";
}

// Maximise the number of unequal pairs after k decrements : greedily strip
// one occurrence off the currently most frequent value each time.
void solve_max_distinct_pairs_after_k_ops()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    unordered_map<ll, ll> freq_map;
    ll curr_diversity = (n * (n - 1)) / 2;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        freq_map[v[x]]++;
    }
    priority_queue<pair<ll, ll>> pq;
    for (auto it : freq_map)
    {
        ll freq = it.second;
        ll key = it.first;
        curr_diversity -= (freq * (freq - 1)) / 2;
        pq.push({freq, key});
    }
    while (pq.empty() != true && k > 0)
    {
        auto p = pq.top();
        pq.pop();
        if (p.first <= 1)
        {
            break;
        }
        curr_diversity += p.first - 1;
        pq.push({p.first - 1, p.second});
        k--;
    }
    cout << curr_diversity << "\n";
}

// Sum of subarray ranges : sum of maximums minus sum of minimums , both by
// the contribution of every element over the segments it dominates.
void solve_sum_of_subarray_ranges()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    vector<ll> psee = previous_smaller_equal_element(v);
    vector<ll> nse = next_smaller_element(v);
    vector<ll> nge = next_greater_element(v);
    vector<ll> pgee = previous_greater_equal_element(v);
    ll maxima = 0;
    ll minima = 0;
    for (ll x = 0; x < n; x++)
    {

        maxima += (v[x] * (nge[x] - x) * (x - pgee[x]));
        minima += (v[x] * (nse[x] - x) * (x - psee[x]));
    }
    cout << (maxima - minima) << "\n";
}

// Sum of subarray minimums via the contribution of every element over the
// (pse , nse) window where it stays the minimum.
void solve_sum_of_subarray_minimums()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }

    vector<ll> nse = next_smaller_element(v);
    vector<ll> pse = previous_smaller_element(v);

    ll sum = 0;
    for (ll x = 0; x < n; x++)
    {
        ll pse_element_idx = x - pse[x];
        ll nse_element_idx = nse[x] - x;
        sum += (v[x] * (pse_element_idx * nse_element_idx));
    }
    cout << sum << "\n";
}

// Driver for the four monotonic stack helpers over a single array.
void solve_monotonic_stack_demo()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    next_greater_element(v);
    next_smaller_element(v);
    previous_greater_element(v);
    previous_smaller_element(v);
}

// Count of zeroes after applying a flip of length k starting at every index
// the flip parity is tracked with a difference array.
void solve_k_length_bit_flips_zero_count()
{
    ll n, k;
    cin >> n >> k;
    ll ans = 0;
    vector<ll> v(n);
    vector<ll> prefix_arr(n, 0);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    for (ll x = 0; x < n; x++)
    {
        if (x == 0)
        {
            if (v[x] == 0)
                ans++;
            prefix_arr[x]++;
            if ((x + k) < n)
            {
                prefix_arr[x + k]--;
            }
        }
        else
        {
            ll change = (prefix_arr[x - 1] + prefix_arr[x]);
            prefix_arr[x] = change;
            if (change % 2 != 0)
            {
                v[x] = ~v[x];
            }
            if (v[x] == 0)
                ans++;
            prefix_arr[x]++;
            if ((x + k) < n)
            {
                prefix_arr[x + k]--;
            }
        }
    }
    cout << ans << "\n";
}

// Cancel the last element against the sum of all the others , whatever is
// left over decays down to its parity.
void solve_reduce_last_element_parity()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    ll ans = 0;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        ans += v[x];
    }
    ans -= v[v.size() - 1];
    if (ans >= v[v.size() - 1])
    {
        ans = (ans - v[v.size() - 1]) % 2;
    }
    else
    {
        ans = (v[v.size() - 1] - ans);
    }
    cout << ans << "\n";
}

// Last stone weight : repeatedly smash the two heaviest stones together.
void solve_last_stone_weight_max_diff()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    priority_queue<ll> pq;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        pq.push(v[x]);
    }
    ll ans = 0;
    while (pq.size() >= 2)
    {
        ll top_1 = pq.top();
        pq.pop();
        ll top_2 = pq.top();
        pq.pop();
        pq.push(top_1 - top_2);
    }
    while (pq.empty() != true)
    {
        ans += pq.top();
        pq.pop();
    }
    cout << ans << "\n";
}

// Total decrease needed to make the array non decreasing , only the drops
// between adjacent elements contribute.
void solve_min_decrements_non_decreasing()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    ll ans = 0;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    for (ll x = 1; x < n; x++)
    {
        if (v[x - 1] > v[x])
        {
            ans += (v[x - 1] - v[x]);
        }
    }

    cout << ans << "\n";
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
void count_pairs()
{
    ll n, num;
    cin >> n >> num;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    sort(v.begin(), v.end());
    ll ans = 0;
    for (ll x = 0; x < v.size(); x++)
    {
        auto it = upper_bound(v.begin(), v.end(), (num - v[x]));
        cout << it - v.begin() - 1 << "\n";
        {
            if (num - v[x] >= v[x])
            {
                ans += (it - v.begin() - 1);
            }
            else
            {
                ans += (it - v.begin());
            }
        }
    }
    cout << ans << "\n";
}
class Operations
{
public:
    ll sum;
    ll sum_of_squares;
    ll num_elements;
    map<ll, ll> freq_map;
    map<ll, ll> inverse_freq_map;

    // Sorted set 1
    multiset<ll> m1;
    // Sorted set 2
    multiset<ll> m2;
    Operations()
    {
        this->sum = 0;
        this->sum_of_squares = 0;
        this->num_elements = 0;
    }
    long double get_mean()
    {
        return (long double)this->sum / (long double)this->num_elements;
    }
    long double get_variance()
    {
        //-mu^2
        long double first_term = (long double)this->sum_of_squares / (long double)this->num_elements;
        long double mean_value = this->get_mean();
        return first_term - (mean_value * mean_value);
    }
    ll get_median()
    {
        if ((m1.size() + m2.size()) % 2 && (m1.size() + m2.size()) != 0)
        {
            // odd
            return *m1.rbegin();
        }
        else
        {
            // even
            return (*m1.rbegin() + *m2.begin()) / 2;
        }
    }
    ll get_mode()
    {
        if (inverse_freq_map.size() != 0)
        {
            return inverse_freq_map.rbegin()->second;
        }
    }
    void update_mode(ll value)
    {
        if (inverse_freq_map.count(freq_map[value]))
        {
            inverse_freq_map.erase(freq_map[value]);
        }
    }
    void handle_extra()
    {
        if ((m2.size() - m1.size()) >= 1)
        {
            ll v = *m2.begin();
            m2.erase(m2.begin());
            m1.insert(v);
        }
        if ((m1.size() - m2.size()) >= 1)
        {
            ll v = *m1.rbegin();
            m1.erase(v);
            m2.insert(v);
        }
    }
    void insert(ll value)
    {
        sum += value;
        num_elements++;
        sum_of_squares += (value * value);
        update_mode(value);
        freq_map[value]++;
        inverse_freq_map.insert({freq_map[value], value});
        if (m1.empty())
        {
            m1.insert(value);
        }
        else
        {
            ll smaller_value = *m1.rbegin();
            if (value > smaller_value)
            {
                m2.insert(value);
            }
            else
            {
                m1.insert(value);
            }
        }
        handle_extra();
    }
    void erase(ll value)
    {
        sum -= value;
        num_elements--;
        sum_of_squares -= (value * value);
        update_mode(value);
        freq_map[value]--;
        inverse_freq_map.insert({freq_map[value], value});
        if (m1.find(value) != m1.end())
        {
            m1.erase(value);
        }
        else if (m2.find(value) != m2.end())
        {
            m2.erase(value);
        }
        handle_extra();
    }
};
// VVIP question + technique.
// Making n elements equal mostly about median to be minimum
// or top k elements .
class MinCost
{
public:
    multiset<ll> left, right;
    ll left_sum, right_sum;
    MinCost()
    {
        this->left_sum = 0;
        this->right_sum = 0;
    }
    void insert(ll value)
    {
        if (left.empty())
        {
            left.insert(value);
            left_sum += value;
        }
        else
        {
            ll left_max_val = *left.rbegin();
            if (value > left_max_val)
            {
                right.insert(value);
                right_sum += value;
            }
            else
            {
                left.insert(value);
                left_sum += value;
            }
        }
        this->balance();
    }
    void erase(ll value)
    {
        if (left.find(value) != left.end())
        {
            left.erase(left.find(value));
            left_sum -= value;
        }
        else if (right.find(value) != right.end())
        {
            right.erase(right.find(value));
            right_sum -= value;
        }
        this->balance();
    }
    long double get_median()
    {
        if ((left.size() + right.size()) % 2 && (left.size() + right.size()) != 0)
        {
            if (left.size() != 0)
                return *left.rbegin();
        }
        else
        {
            long double v1, v2;
            v1 = 0;
            v2 = 0;
            if (!left.empty())
            {
                v1 = *left.rbegin();
            }
            if (!right.empty())
            {
                v2 = *right.begin();
            }
            return (v1 + v2) / 2;
        }
    }
    void balance()
    {
        if ((ll)(left.size() - right.size()) >= 1)
        {
            ll x = *left.rbegin();
            left.erase(left.find(x));
            left_sum -= x;
            right.insert(x);
            right_sum += x;
        }
        if ((ll)(right.size() - left.size()) >= 1)
        {
            ll x = *right.begin();
            right_sum -= x;
            right.erase(right.find(x));
            left.insert(x);
            left_sum += x;
        }
    }
    ll cost()
    {
        ll ans = 0;
        ll median = get_median();
        // Considering median to be a member of the right set and the smallest one too so
        // mod sign will remain positive for all the members of right set and negitive for all
        // members of left set.
        ans += (right_sum - (right.size() * median));
        ans += ((left.size() * median) - left_sum);
        return ans;
    }
};
class TopK
{
public:
    multiset<ll> m1;
    multiset<ll> remove;
    ll running_sum;
    ll k;
    TopK(ll k_val)
    {
        this->running_sum = 0;
        this->k = k_val;
    }
    void insert(ll value)
    {
        m1.insert(value);
        running_sum += value;
        if (m1.size() > k)
        {
            ll val = *m1.begin();
            remove.insert(val);
            m1.erase(m1.find(val));
            running_sum -= val;
        }
    }
    void erase(ll value)
    {
        if (m1.find(value) != m1.end())
        {
            m1.erase(m1.find(value));
            running_sum -= value;
            if (m1.size() < k)
            {
                if (remove.size() > 0)
                {
                    m1.insert(*remove.rbegin());
                    running_sum += *remove.rbegin();
                    remove.erase(remove.find(*remove.rbegin()));
                }
            }
        }
        else if (remove.find(value) != remove.end())
        {
            remove.erase(remove.find(value));
        }
    }
    ll get_top_k_sum()
    {
        return running_sum;
    }
};
vector<int> countTasks(vector<int> &tasks, vector<int> &shifts)
{
    vector<int> prefix_arr(tasks.size());
    prefix_arr[0] = tasks[0];
    for (int x = 1; x < tasks.size(); x++)
    {
        prefix_arr[x] = prefix_arr[x - 1] + tasks[x];
    }
    vector<int> ans;
    int total_work_done = 0;
    int n = tasks.size();
    for (int x = 0; x < shifts.size(); x++)
    {
        auto it = upper_bound(prefix_arr.begin(), prefix_arr.end(), total_work_done + shifts[x]);
        if (total_work_done + shifts[x] >= prefix_arr[prefix_arr.size() - 1])
        {
            total_work_done = 0;
            ans.push_back(0);
        }
        else
        {
            if (it == prefix_arr.end())
            {
                ans.push_back(prefix_arr.size());
            }
            else
            {
                ans.push_back((prefix_arr.end() - it));
            }
            total_work_done += shifts[x];
        }
    }
    for (auto i : ans)
    {
        cout << i << " ";
    }
    cout << "\n";
    return ans;
}
int countRatioSubarrays(vector<int> &nums, int a, int b)
{
    vector<int> odd, even;
    for (auto i : nums)
    {
        if (i % 2 == 0)
        {
            even.push_back(1);
            odd.push_back(0);
        }
        else
        {
            odd.push_back(1);
            even.push_back(0);
        }
    }
    vector<int> odd_prefix(odd.size() + 1, 0);
    vector<int> even_prefix(even.size() + 1, 0);
    for (int x = 1; x < even_prefix.size(); x++)
    {
        odd_prefix[x] = odd_prefix[x - 1] + odd[x - 1];
        even_prefix[x] = even_prefix[x - 1] + even[x - 1];
    }
    int ans = 0;
    for (int x = 0; x < nums.size(); x++)
    {
        for (int y = x; y < nums.size(); y++)
        {
            int num_odds = odd_prefix[y] - odd_prefix[x];
            int num_evens = even_prefix[y] - even_prefix[x];
            if ((num_evens / num_odds) <= (a / b))
                ans++;
        }
    }
    return ans;
}
ll maxPairStrength(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    ll ans = 0;
    for (ll x = 0; x < nums.size(); x++)
    {
        for (ll y = 0; y < nums.size(); y++)
        {
            if (x == y)
                continue;
            else
            {
                ans = max(ans, (ll)((nums[x] * nums[y]) / gcd(nums[x], nums[y])));
            }
        }
    }
    return ans;
}
/*
    a*b = gcd*lcm
    max(lcm/gcd)
*/
int maximumWidth(vector<int> &planks)
{
    // 1,1,2,2,3,4,5,5,7
    int ans = INT_MIN;
    unordered_map<int, int> freq_map;
    unordered_set<int> pairs;
    for (int x = 0; x < planks.size(); x++)
    {
        pairs.insert(planks[x]);
        freq_map[planks[x]]++;
        for (int y = 0; y < planks.size(); y++)
        {
            if (x == y)
                continue;
            else
            {
                pairs.insert(planks[x] + planks[y]);
            }
        }
    }
    for (auto pair : pairs)
    {
        int cnt = 0;
        unordered_set<int> visited_or_not;
        for (auto it : freq_map)
        {
            int num = it.first;
            int freq = it.second;
            if (pair < num || visited_or_not.count(num))
                continue;
            else if (pair == num)
            {
                cnt += freq;
                visited_or_not.insert(num);
            }
            else
            {
                if (freq_map.count(pair - num) && (pair - num) != num && visited_or_not.count(pair - num) == false)
                {
                    cnt += min(freq, freq_map[pair - num]);
                    visited_or_not.insert(pair - num);
                }
                else if ((pair - num) == num)
                {
                    visited_or_not.insert(num);
                    cnt += freq / 2;
                }
            }
        }
        ans = max(ans, cnt);
    }
    return ans;
}
int maximumWidth_optimized(vector<int> &planks)
{
    // 1,1,2,2,3,4,5,5,7
    int ans = INT_MIN;
    unordered_map<int, int> freq_map, res;
    for (int x = 0; x < planks.size(); x++)
    {
        freq_map[planks[x]]++;
        res[planks[x]]++;
    }
    for (auto p1 : freq_map)
    {
        for (auto p2 : freq_map)
        {
            if (p1.first == p2.first)
            {
                res[p1.first + p2.first] += p1.second / 2;
            }
            else if (p1.first < p2.first)
            {
                res[p1.first + p2.first] += min(p1.second, p2.second);
            }
        }
    }
    for (auto it : res)
    {
        ans = max(ans, it.second);
    }
    return ans;
}
bool is_valid(vector<int> &monsters, vector<int> &prefix_arr, ll initial_strength)
{
    for (int x = 0; x < monsters.size(); x++)
    {
        if ((prefix_arr[x] + initial_strength) < monsters[x])
            return false;
        else
        {
            initial_strength -= monsters[x];
            if (initial_strength < 0)
                initial_strength = 0;
        }
    }
    return true;
}
ll minInitialStrength(vector<int> &monsters, vector<vector<int>> &boosts)
{
    ll total_sum = 0;
    for (auto i : monsters)
        total_sum += i;
    vector<ll> diff_arr(monsters.size(), 0);
    for (int x = 0; x < boosts.size(); x++)
    {
        int li = boosts[x][0];
        int ri = boosts[x][1];
        int val = boosts[x][2];
        if (ri + 1 < monsters.size())
            diff_arr[ri + 1] -= val;
        diff_arr[li] += val;
    }
    vector<int> prefix_arr(diff_arr.size());
    prefix_arr[0] = diff_arr[0];
    for (int x = 1; x < diff_arr.size(); x++)
    {
        prefix_arr[x] = diff_arr[x] + prefix_arr[x - 1];
    }
    ll l = 0;
    ll r = total_sum;
    ll ans = LLONG_MAX;
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        if (is_valid(monsters, prefix_arr, mid))
        {
            ans = min(ans, mid);
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return ans;
}
void non_overlapping_intervals()
{
    ll n;
    cin >> n;
    vector<vector<ll>> intervals(n);
    for (ll x = 0; x < n; x++)
    {
        ll a, b;
        cin >> a >> b;
        intervals[x] = {a, b};
    }
    sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b)
         { return a[1] < b[1]; });
    int right = intervals[0][1];
    int ans = 0;
    for (int x = 1; x < intervals.size(); x++)
    {
        int l = intervals[x][0];
        int r = intervals[x][1];
        if (l < right)
        {
            ans += 1;
        }
        else
        {
            right = r;
        }
    }
    cout << n - ans << "\n";
}
vector<int> canSeePersonsCount(vector<int> &heights)
{
    vector<int> ans(heights.size());
    stack<int> st;
    for (int x = heights.size() - 1; x >= 0; x--)
    {
        int cnt = 0;
        while (!st.empty() && st.top() < heights[x])
        {
            cnt++;
            st.pop();
        }
        if (st.empty() == false)
            cnt++;
        st.push(heights[x]);
        ans[x] = cnt;
    }
    return ans;
}
long long countRatioSubarraysV2(vector<int> &nums, int a, int b)
{
    // x*b-y*a <= 0 = y*a-x*b >= 0
    // Allotting +b and -a respectively to even and odd parity of numbers
    // and then forming prefix_sum having condition of window sum be lesser
    // <= 0 having condition as pf[R]-pf[l-1]<=0 ----> pf[r] >= pf[l-1] .

    long long ans = 0;
    vector<int> prefix_arr(nums.size());
    for (int x = 0; x < nums.size(); x++)
    {
        if (nums[x] % 2 == 1)
            nums[x] = -a;
        else
        {
            nums[x] = b;
        }
    }
    //-1,-1,2
    //-1,-1,0
    prefix_arr[0] = nums[0];
    for (int x = 1; x < nums.size(); x++)
    {
        prefix_arr[x] = prefix_arr[x - 1] + nums[x];
    }
    ordered_set st;
    st.insert(0);
    for (auto pf_ele : prefix_arr)
    {
        ans += (st.order_of_key(pf_ele) +
                (st.size() - st.order_of_key(pf_ele)));
        st.insert(pf_ele);
    }
    return ans;
}
// Sweep from the right keeping every seen value in a multiset , for each
// index the prefix minimum plays the role of the smaller left element and the
// multiset is asked for something strictly between it and the current value .
void solve_pattern_132_exists()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    multiset<ll> st;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    st.insert(v[n - 1]);
    vector<ll> prefix_min(n);
    prefix_min[0] = v[0];
    for (ll i = 1; i < n; i++)
        prefix_min[i] = min(prefix_min[i - 1], v[i]);
    for (ll x = n - 1; x >= 0; x--)
    {
        ll j = v[x];
        if (prefix_min[x] == v[x])
        {
            st.insert(j);
            continue;
        }
        else if (prefix_min[x] != -1)
        {
            auto it = st.upper_bound(prefix_min[x]);
            if (it != st.end() && *it < j)
            {
                cout << "YES" << "\n";
                return;
            }
        }
        st.insert(j);
    }
    cout << "No" << "\n";
}

// Nested for loops carry a multiplier on a stack , every add contributes the
// multiplier sitting on the top and the multiplier itself is capped so the
// product never overflows before the verdict is printed .
void solve_catch_overflow()
{
    ll n;
    cin >> n;
    ll ans = 0;
    stack<ll> st;
    st.push(1);
    ll maxi = (1LL << 32) - 1;
    for (ll x = 0; x < n; x++)
    {
        string s;
        cin >> s;
        if (s == "add")
        {
            ans += st.top();
        }
        else if (s == "for")
        {
            ll num;
            cin >> num;
            st.push(min(num * st.top(), maxi));
        }
        else if (s == "end")
        {
            if (st.empty() == false)
                st.pop();
        }
    }
    if (ans >= maxi)
    {
        cout << "OVERFLOW!!!" << "\n";
        return;
    }
    cout << ans << "\n";
}

// Print the raw previous smaller element values , -1 where none exists .
void solve_previous_smaller_element_print()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    vector<ll> pse = previous_smaller_element(v);
    for (auto p : pse)
    {
        cout << p << " ";
    }
    cout << "\n";
}

// For every query pull out and consume the largest stored value that does not
// exceed the query , the multiset upper bound stepped back one place .
void solve_largest_not_exceeding_queries()
{
    ll n, m;
    cin >> n >> m;
    multiset<ll> st;
    for (int x = 0; x < n; x++)
    {
        ll num;
        cin >> num;
        st.insert(num);
    }
    for (int x = 0; x < m; x++)
    {
        ll query;
        cin >> query;
        if (st.size() == 0)
        {
            cout << -1 << "\n";
            continue;
        }
        auto it = st.upper_bound(query);
        if (it == st.end() || it == st.begin())
        {
            if (*st.rbegin() <= query)
            {
                cout << *st.rbegin() << "\n";
                st.erase(st.find(*st.rbegin()));
            }
            else
            {
                cout << -1 << "\n";
            }
        }
        else
        {
            it--;
            cout << *it << "\n";
            st.erase(st.find(*it));
        }
    }
}

// Seed the sequence with 1 2 3 and keep doubling the tail , n == 2 admits no
// valid construction .
// 5,11,6,10 = 32
// 1,2,3,6,12 = 24
// 1,2,3,6,12,24 48
// 1,2,3,6,12,24,48
void solve_construct_doubling_sequence()
{
    int n;
    cin >> n;
    if (n == 2)
        cout << -1 << "\n";
    else
    {
        if (n == 1)
            cout << 1 << "\n";
        else if (n == 3)
            cout << 1 << " " << 2 << " " << 3 << "\n";
        else
        {
            cout << 1 << " " << 2 << " " << 3 << " ";
            n -= 3;
            ll prev = 3;
            while (n > 0)
            {
                cout << prev * 2 << " ";
                prev = prev * 2;
                n--;
            }
        }
    }
}

// Cancel adjacent equal characters with a stack until nothing else collapses .
void solve_remove_adjacent_duplicates()
{
    string s;
    cin >> s;
    stack<char> st;
    for (auto ch : s)
    {
        if (st.empty())
        {
            st.push(ch);
        }
        else
        {
            if (st.top() == ch)
            {
                st.pop();
            }
            else
            {
                st.push(ch);
            }
        }
    }
    string ans = "";
    while (!st.empty())
    {
        ans.push_back(st.top());
        st.pop();
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
}

/*
    [4,2,3] -------> [2,1,4,4]
    [4,6,9] -------> [2,1,4,4] ------> [3]
    [4,6,9] -------> [1+2 = 3,4,4]  -------> [3,3]
    [4,6,9] ---------> [4+3 = 7,4] --------------> [2,2,1]
    [4,6,9] -----------> [7+2 = 9] ---------------> ][2,2,1,0]

    [5,2] ----> [3,1,1]
    [5,7] -----> [3,1,1]
    [5,7] ---------> [3,1] -------> [0]

*/
void solve_count_tasks_per_shift()
{
    int n, s;
    cin >> n >> s;
    vector<int> tasks(n);
    vector<int> shifts(s);
    for (int x = 0; x < n; x++)
        cin >> tasks[x];
    for (int x = 0; x < s; x++)
        cin >> shifts[x];
    countTasks(tasks, shifts);
}

// Greedily flip a k sized window the moment a zero shows up , the indices of
// the flips already made are binary searched to recover the parity affecting
// the current position .
void solve_min_k_bit_flips()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    ll ans = 0;
    vector<ll> changes;
    for (ll x = 0; x < n; x++)
    {
        ll change = 0;
        if (!changes.empty())
        {
            change = changes.end() -
                     lower_bound(changes.begin(), changes.end(), x - k + 1);
        }
        ll value = v[x];
        if (change % 2 != 0)
        {
            if (value == 0)
                value = 1;
            else
                value = 0;
        }
        if (value == 0)
        {
            if (x + k > n)
            {
                cout << -1 << "\n";
                return;
            }
            changes.push_back(x);
            ans++;
        }
    }
    cout << ans << "\n";
}

// Read the intervals and the queries , the per query answer is still pending .
void solve_interval_queries_stub()
{
    ll n;
    cin >> n;
    vector<pair<ll, ll>> v(n);
    for (ll x = 0; x < n; x++)
    {
        ll li, ri;
        cin >> li >> ri;
        v[x] = {li, ri};
    }
    ll q;
    cin >> q;
    while (q--)
    {
        ll y;
        cin >> y;
    }
}

// Insert , erase and running sum of the k largest values through the two
// multiset TopK design .
void solve_top_k_sum_queries()
{
    ll q, k;
    cin >> q >> k;
    TopK new_obj = TopK(k);
    while (q--)
    {
        ll query;
        cin >> query;
        if (query == 1)
        {
            ll num;
            cin >> num;
            new_obj.insert(num);
        }
        else if (query == 2)
        {
            ll num;
            cin >> num;
            new_obj.erase(num);
        }
        else if (query == 3)
        {
            char ch;
            cin >> ch;
            cout << new_obj.get_top_k_sum() << "\n";
        }
    }
}
void solve_expression()
{
    ll a, b, n;
    cin >> a >> b >> n;
    ll first_term = binpow(a, n);
    ll second_term_1 = b;
    ll second_term_2_numerator = (a % MOD + (((binpow(a, n) - a) + MOD) % MOD)) % MOD;
    ll inv = inverse((a - 1), MOD);

    ll f = ((second_term_2_numerator % MOD) * (inv % MOD)) % MOD;
    ll f_2 = (second_term_1 * f) % MOD;
    cout << (first_term % MOD + f_2 % MOD) % MOD << "\n";
}
void make_largest_smallest_palindrome()
{
    string s;
    cin >> s;
    bool odd_flag = false;
    unordered_map<char, int> m;
    for (auto ch : s)
        m[ch]++;
    vector<pair<char, ll>> chars;
    ll final_length = 0;
    char odd_char = ' ';
    for (auto it : m)
    {
        if (it.second % 2 != 0 && odd_flag == false)
        {
            odd_flag = true;
            chars.push_back({it.first, it.second - 1});
            final_length += it.second - 1;
            odd_char = it.first;
        }
        else
        {
            chars.push_back({it.first, it.second});
            final_length += it.second;
        }
    }
    string ans = "";

    for (auto it : chars)
    {
        for (long long i = 0; i < it.second / 2; i++)
            ans += it.first;
    }
    cout << ans;

    if (odd_flag)
        cout << odd_char;

    reverse(ans.begin(), ans.end());
    cout << ans << '\n';
}
void difference_greedy()
{
    ll n;
    cin >> n;
    vector<ll> v1(n), v2(n);
    for (ll x = 0; x < n; x++)
        cin >> v1[x];
    for (ll x = 0; x < n; x++)
        cin >> v2[x];

    // Keeping 2 heaps one for the negitive difference
    // and other one for positive difference because
    // it might be best optimal to cancel from maximum
    // difference present as compared to minimum present and can be maintained in heap .
    priority_queue<ll, vector<ll>, greater<ll>> negitive_diff;
    priority_queue<ll> positive_diff;
    ll ans = 0;
    for (ll x = 0; x < n; x++)
    {
        if ((v1[x] - v2[x]) > 0)
            positive_diff.push(abs(v1[x] - v2[x]));
        else if ((v1[x] - v2[x]) < 0)
            negitive_diff.push(abs(v1[x] - v2[x]));
    }
    while (negitive_diff.empty() == false && positive_diff.empty() == false)
    {
        // getting minimum negitive difference
        ll val_1 = negitive_diff.top();
        // getting maximum positive difference
        ll val_2 = positive_diff.top();

        if (val_2 >= val_1)
        {
            negitive_diff.pop();
            positive_diff.pop();
            val_2 -= val_1;
            positive_diff.push(val_2);
            ans++;
        }
        else
        {
            val_1 -= val_2;
            positive_diff.pop();
            negitive_diff.push(val_1);
        }
    }
    for (ll x = 0; x < n; x++)
    {
        if (v1[x] == v2[x])
            ans++;
    }
    cout << ans << "\n";
}
double minPrice(vector<int> &prices, vector<int> &discounts)
{
    priority_queue<ll> prices_pq;
    priority_queue<ll> discounts_pq;
    for (auto p : prices)
        prices_pq.push(p);
    for (auto d : discounts)
        discounts_pq.push(d);

    double ans = 0.0;
    while (prices_pq.empty() == false)
    {
        double price = prices_pq.top();
        prices_pq.pop();
        double discount = discounts_pq.top();
        discounts_pq.pop();
        price = (double)(price * (100 - discount)) / (double)100;
        ans += price;
    }

    return ans;
}
bool check(vector<int> &arr, int mid)
{
    if (mid != 0 && mid != arr.size() - 1)
    {
        if (arr[mid + 1] > arr[mid] || arr[mid - 1] > arr[mid])
        {
            return false;
        }
    }
    if (mid == 0)
    {
        if (arr[mid + 1] > arr[mid])
        {
            return false;
        }
    }
    if (mid == arr.size() - 1)
    {
        if (arr[mid - 1] > arr[mid])
        {
            return false;
        }
    }

    return true;
}
int findPeakElement(vector<int> &arr)
{
    // Seaching space will be [0,....n-1]//
    int n = arr.size() - 1;
    if (arr.size() == 1)
    {
        return 0;
    }
    int s = 0;
    int e = n;
    while (s <= e)
    {
        int mid = (s + e) / 2;
        if (check(arr, mid) == true)
        {
            return mid;
        }
        if (mid != 0)
        {
            if (arr[mid - 1] > arr[mid])
            {
                e = mid - 1;
            }
            else
            {
                s = mid + 1;
            }
        }
        else
        {
            s = mid + 1;
        }
    }
    return 1;
}
long long weightedSum(vector<int> &parent, vector<int> &nums)
{
    int n = parent.size();
    // Adjlist population
    vector<vector<int>> children(n);

    for (int i = 1; i < n; i++)
    {
        children[parent[i]].push_back(i);
    }

    vector<int> depth(n);
    queue<int> q;

    depth[0] = 1;
    q.push(0);

    int h = 1;

    while (!q.empty())
    {

        int u = q.front();
        q.pop();

        for (int v : children[u])
        {

            depth[v] = depth[u] + 1;

            h = max(h, depth[v]);

            q.push(v);
        }
    }

    long long ans = 0;

    for (int i = 0; i < n; i++)
    {
        ans += 1LL * nums[i] * (h - depth[i] + 1);
    }

    return ans;
}
void extra_count_codeforces()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    vector<ll> consecutive_sequences, consecutive_sequences_len;
    for (ll i = 0; i < n; i++)
    {
        if (i > 0 && v[i] == v[i - 1])
            consecutive_sequences_len.back()++;
        else
        {
            consecutive_sequences.push_back(v[i]);
            consecutive_sequences_len.push_back(1);
        }
    }
    ll ans = consecutive_sequences.size();
    ll extra = 0;
    for (ll x = 0; x + 1 < ans; x++)
    {
        if (consecutive_sequences_len[x] >= 2 && consecutive_sequences_len[x + 1] >= 2)
        {
            extra = 2;
            break;
        }
    }
    if (extra < 2)
    {
        for (ll x = 0; x < ans; x++)
        {
            if (consecutive_sequences_len[x] < 2)
                continue;
            bool choice_1 = false;
            if (x - 1 >= 0)
            {
                if (x - 2 < 0)
                {
                    choice_1 = true;
                }
                else
                {
                    if (consecutive_sequences[x - 2] != consecutive_sequences[x])
                    {
                        choice_1 = true;
                    }
                }
            }

            bool choice_2 = false;
            if (x + 1 <= ans - 1)
            {
                if (x + 2 > ans - 1)
                {
                    choice_2 = true;
                }
                else
                {
                    if (consecutive_sequences[x + 2] != consecutive_sequences[x])
                    {
                        choice_2 = true;
                    }
                }
            }
            if (choice_1 || choice_2)
            {
                extra = 1;
                break;
            }
        }
    }
    cout << (ans + extra) << "\n";
}
ll sum_2d(vector<vector<ll>> &prefix_arr, pair<ll, ll> &p1, pair<ll, ll> &p2)
{
    ll U = p1.first;
    ll L = p1.second;
    ll D = p2.first;
    ll R = p2.second;

    if (U < 0 || L < 0 ||
        D >= prefix_arr.size() ||
        R >= prefix_arr[0].size())
        return -1;

    ll sum = prefix_arr[D][R];

    if (L > 0)
        sum -= prefix_arr[D][L - 1];

    if (U > 0)
        sum -= prefix_arr[U - 1][R];

    if (U > 0 && L > 0)
        sum += prefix_arr[U - 1][L - 1];

    return sum;
}
int maxArea(vector<vector<ll>> &mat)
{
    /*
        mat[r][c] == 1 usable .
        mat[r][c] == 0 non usable .
        sum = k*k
    */
    // vector<vector<ll>> pf_arr = prefix_2d(mat);
    // ll row = mat.size();
    // ll col = mat[0].size();
    // vector<pair<ll,ll>>valid_pairs;
    // for (ll k = 1; k <= 500; k++)
    // {
    //     for (ll r = 0; r < row; r++)
    //     {
    //         for (ll c = 0; c < col; c++)
    //         {
    //             pair<ll,ll>p1 = make_pair(r,c);
    //             pair<ll,ll>p2 = make_pair(r+k,c+k);

    //             if (sum_2d(pf_arr,p1,p2) == (k*k)){
    //                 //Valid sub-matrix from the starting row and column
    //                 //starting with k row+k and column+k .
    //                 valid_pairs.push_back({r,c});
    //             }
    //         }
    //     }
    // }
    // for(ll x=0;x<valid_pairs.size();x++){
    //     for(ll y=0;y<valid_pairs.size();y++){
    //         if(x==y)continue;
    //         else{

    //         }
    //     }
    // }

    vector<vector<ll>> pf_arr = prefix_2d(mat);

    ll row = mat.size();
    ll col = mat[0].size();

    ll ans = 0;

    for (ll k = 1; k <= min(row, col); k++)
    {
        vector<pair<ll, ll>> valid_pairs;

        for (ll r = 0; r + k <= row; r++)
        {
            for (ll c = 0; c + k <= col; c++)
            {
                pair<ll, ll> p1 = {r, c};
                pair<ll, ll> p2 = {r + k - 1, c + k - 1};

                if (sum_2d(pf_arr, p1, p2) == k * k)
                {
                    valid_pairs.push_back({r, c});
                }
            }
        }

        // Check every pair of valid k x k squares
        for (ll x = 0; x < valid_pairs.size(); x++)
        {
            ll r1 = valid_pairs[x].first;
            ll c1 = valid_pairs[x].second;

            for (ll y = x + 1; y < valid_pairs.size(); y++)
            {
                ll r2 = valid_pairs[y].first;
                ll c2 = valid_pairs[y].second;

                bool non_overlapping = false;

                // Same starting row
                if (r1 == r2)
                {
                    if (abs(c1 - c2) >= k)
                        non_overlapping = true;
                }
                else
                {
                    // Different rows:
                    // They are non-overlapping if they are
                    // separated vertically OR horizontally.
                    if (abs(r1 - r2) >= k ||
                        abs(c1 - c2) >= k)
                    {
                        non_overlapping = true;
                    }
                }

                if (non_overlapping)
                {
                    ans = max(ans, 2LL * k * k);
                }
            }
        }
    }
    return ans;
}
void points_on_line()
{
    ll n, d;
    cin >> n >> d;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
        cin >> v[x];
    ll ans = 0;
    for (ll x = 0; x < n; x++)
    {
        auto it = upper_bound(v.begin(), v.end(), d + v[x]) - v.begin();
        // Finding last valid value i.e. x such that v[x] <= d+v[x]
        it--;
        ans += ((it - x) * (it - x - 1)) / 2;
    }
    cout << ans << "\n";
}
bool check_factory_machines(ll mid, ll t, vector<ll> &v)
{
    ll total_elements = 0;
    for (auto time : v)
    {
        total_elements += mid / time;
        if (total_elements >= t)
            return true;
    }

    return total_elements >= t;
}
void factory_machines()
{
    ll n, t;
    cin >> n >> t;
    vector<ll> v(n);
    ll maxi = LLONG_MIN;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        maxi = max(maxi, v[x]);
    }
    ll low = 0;
    ll high = (maxi * t);
    ll ans = LLONG_MAX;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (check_factory_machines(mid, t, v) == true)
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
}
bool check_bizon(ll mid, ll n, ll m, ll k)
{
    // For each row sum the elements less than x .
    ll cnt = 0;
    for (ll row = 1; row <= n; row++)
    {
        // each value will be i*j = v j = v/i(row)
        // if mid == v then mid/i will represent all the values in a row < mid .
        cnt += min((ll)floor(mid / row), m);
    }
    return cnt >= k;
}
// Special case when the process cannot be simulated
// so finding always by  ((total number of elements less than or equal x) >= k) .
void multiplication_table()
{
    ll n;
    cin >> n;
    ll k = (n * n) / 2;

    ll low = 0;
    ll high = 1e18;
    ll ans = LLONG_MAX;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (check_bizon(mid, n, n, k) == true)
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
}
bool check_search(ll mid, vector<ll> &nums)
{
    if (nums[mid] > nums[nums.size() - 1])
        return false;
    return true;
}
ll search(vector<ll> &nums, ll target)
{
    ll ans = -1;
    sort(nums.begin(), nums.end());
    ll original_idx = upper_bound(nums.begin(), nums.end(), target) - nums.begin();
    original_idx--;
    if (original_idx < 0 || nums[original_idx] != target)
        return -1;
    // finding the index of smallest element by a monotone space array .
    ll num_of_rotations = 0;
    ll low = 0;
    ll high = nums.size();
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (check_search(mid, nums) == true)
        {
            num_of_rotations = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return (original_idx + num_of_rotations) % nums.size();
}
bool check_bitonic(ll mid, vector<ll> &nums)
{
    if (((mid + 1) < nums.size() && (nums[mid + 1] < nums[mid])) || mid == nums.size() - 1)
        return true;
    return false;
}
void bitonic_array()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> nums(n);
    for (ll x = 0; x < n; x++)
        cin >> nums[x];
    ll peak_element_idx = 0;
    ll low = 0;
    ll high = nums.size() - 1;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (check_bitonic(mid, nums) == true)
        {
            peak_element_idx = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    while (q--)
    {
        ll k;
        cin >> k;
        ll pos_1 = -1;
        ll pos_2 = -1;
        if (k == nums[peak_element_idx])
        {
            cout << peak_element_idx + 1 << "\n";
            continue;
        }
        {
            ll it = upper_bound(nums.begin(), nums.begin() + peak_element_idx, k) - nums.begin();
            it--;
            if (it >= 0 && nums[it] == k)
                pos_1 = it;
        }
        {
            auto it = upper_bound(nums.begin() + peak_element_idx + 1, nums.end(), k, greater<ll>()) - nums.begin();
            it--;
            if (it < nums.size() && nums[it] == k)
                pos_2 = it;
        }
        if (pos_1 != -1 && pos_2 != -1)
            cout << pos_1 + 1 << " " << pos_2 + 1 << "\n";
        else
        {
            if (pos_1 == -1 && pos_2 != -1)
                cout << pos_2 + 1 << "\n";
            else if (pos_1 != -1 && pos_2 == -1)
            {
                cout << pos_1 + 1 << "\n";
            }
        }
    }
}
// Compress the array into runs of equal values , the run count is the base
// answer and one change can split at most one run of length >= 2 , two such
// runs sitting next to each other buy two extra blocks .
ll digit_sum(ll num)
{
    ll sum = 0;
    while (num >= 1)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}
void number_and_sum_of_digit()
{
    // search space = [1,N], (X-sum_of_digits(X) >= S) smallest possible value of X .
    ll n, s;
    cin >> n >> s;
    ll low = 1;
    ll high = n;
    ll ans = 0;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if ((mid - digit_sum(mid)) >= s)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << n - ans + 1 << "\n";
}
bool check_painter_partition(ll mid, vector<ll> &v, ll k)
{
    /*
      [2 5 7 2 5]
      1 <----> 2


    */
    ll painters_cnt = 0;
    ll time_left = 0;
    for (ll x = 0; x < v.size(); x++)
    {
        if (time_left >= v[x])
        {
            // This painter can only be used here and never again .
            time_left -= v[x];
        }
        else
        {
            painters_cnt += 1;
            if (painters_cnt > k)
                return false;
            // Assigning full quota because each painter can paint
            // till t seconds on some different walls which are non intersecting.
            time_left = mid;
            if (time_left >= v[x])
            {
                time_left -= v[x];
            }
            else
            {
                return false;
            }
        }
    }
    return painters_cnt <= k;
}
void painter_partition()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    ll sum = 0;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        sum += v[x];
    }
    ll low = 0;
    ll high = sum;
    ll ans = -1;
    while (low <= high)
    {
        ll mid = (high + low) / 2;
        if (check_painter_partition(mid, v, k))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
}
bool check_minimise_max_diff(ll mid, vector<ll> &v, ll k)
{
    ll total_points_required = 0;
    for (ll x = 0; x < v.size() - 1; x++)
    {
        if (mid > 0)
        {
            total_points_required += ((((v[x + 1] - v[x]) + mid) - 1) / mid) - 1;
            if (total_points_required > k)
                return false;
        }
        else
        {
            return false;
        }
    }
    // total_points_required that are required to make the diff <= mid or X
    // has to be be also lesser than k <= k;
    return total_points_required <= k;
}
void minimise_max_diff()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    sort(v.begin(), v.end());
    ll low = 0;
    // Maximum possible difference in distance .
    ll high = INT_MIN;
    for (ll x = 0; x < n && (x + 1) < n; x++)
    {
        high = max(high, (v[x + 1] - v[x]));
    }
    ll ans = 0;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (check_minimise_max_diff(mid, v, k))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
}
bool check_kth_sum_value(ll mid, vector<ll> &v1, vector<ll> &v2, ll k)
{
    // (Finding number of elements having sum <= X) >= k for process which cannot
    // be simulated .
    ll total_cnt = 0;
    if (v1.size() >= v2.size())
    {
        // Iterate over v2
        for (ll x = 0; x < v2.size(); x++)
        {
            // Finding (x-v2[x]) highest possible available value
            auto it = upper_bound(v1.begin(), v1.end(), (mid - v2[x]));
            if (it != v1.end())
            {
                ll idx = it - v1.begin();
                total_cnt += idx;
            }
            else
            {
                // All values are lesser than (x-v2[x])
                total_cnt += (v1.size());
            }
        }
    }
    else
    {
        // Iterate over v1
        for (ll x = 0; x < v1.size(); x++)
        {
            // Finding (x-v2[x]) highest possible available value
            auto it = upper_bound(v2.begin(), v2.end(), mid - v1[x]);
            if (it != v2.end())
            {
                ll idx = it - v2.begin();
                total_cnt += idx;
            }
            else
            {
                // All values are lesser than (x-v2[x])
                total_cnt += (v2.size());
            }
        }
    }
    return k <= total_cnt;
}
void kth_sum_value()
{
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> v1(n), v2(m);
    for (ll x = 0; x < n; x++)
    {
        cin >> v1[x];
    }
    for (ll x = 0; x < m; x++)
    {
        cin >> v2[x];
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    ll low = v1[0] + v2[0];
    ll high = v1[v1.size() - 1] + v2[v2.size() - 1];
    ll ans = 0;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (check_kth_sum_value(mid, v1, v2, k) == true)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
}
bool check_consecutive_ones(ll mid, vector<ll> &v, ll k, vector<ll> &prefix_zeros)
{
    // length <= mid && pf[r]-pf[l-1] <= k
    // pf[l-1]-pf[r] >= k ===> pf[l-1] >= k+pf[r]
    // [1 0 1 1 0 1 1 0 0] === [0,1,1,1,2,2,2,3,3] and k = 2
    ll num_zeros = 0;
    ll l = 0;
    ll r = 0;
    bool flag = false;
    while (l <= r && r < v.size())
    {
        if (r < mid && flag == false)
        {
            if (v[r] == 0)
                num_zeros++;
            if ((r + 1) == mid)
            {
                flag = true;
                continue;
            }
            r++;
        }
        else
        {
            if (num_zeros <= k)
                return true;
            else
            {
                if (v[l] == 0)
                    num_zeros--;
                if ((r + 1) < v.size() && v[r + 1] == 0)
                    num_zeros++;
            }
            l++;
            r++;
        }
    }
    return false;
}
void solve_consecutive_ones()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    vector<ll> prefix_zeros(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        if (x == 0)
            prefix_zeros[x] = v[x];
        else
        {
            prefix_zeros[x] = prefix_zeros[x - 1] + v[x];
        }
    }
    // Number of zeros must be <= K within a subarray .
    ll low = 0;
    ll high = n;
    ll ans = 0;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (check_consecutive_ones(mid, v, k, prefix_zeros))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
}
void bs_real_domain()
{
    long double n;
    cin >> n;
    long double low = 0.0;
    long double high = n;
    // Taking epsilon according to the error
    //  limit provided in questions .
    while (abs(low - high) >= EPSILON)
    {
        long double mid = (low + high) / 2;
        // check function
        if (1)
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }
    long double ans = (low + high) / 2;
    cout << ans << "\n";
}
bool check_class_room(ll mid, vector<ll> &v, ll k)
{
    ll last = v[0];
    k--;
    for (ll x = 1; x < v.size(); x++)
    {
        if ((v[x] - last) < mid)
            continue;
        else
        {
            last = v[x];
            k--;
        }
    }
    if (k > 0)
        return false;
    return true;
}
void classRoom()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
        cin >> v[x];
    sort(v.begin(), v.end());
    ll low = v[1] - v[0];
    ll high = v[v.size() - 1] - v[0];
    ll ans = 0;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (check_class_room(mid, v, k))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
}
void maximize_fraction()
{
    ll n, k;
    cin >> n >> k;
    ll temp = k;
    vector<ll> a(n), b(n);
    for (ll x = 0; x < n; x++)
        cin >> a[x];
    for (ll x = 0; x < n; x++)
        cin >> b[x];

    long double low = 0.0;
    long double high = 1e8;
    long double ans = 0.0;
    while (abs(high - low) >= EPSILON)
    {
        long double mid = (low + high) / 2.0;
        k = temp;
        priority_queue<long double> pq;
        for (ll x = 0; x < n; x++)
        {
            pq.push((a[x] - (b[x] * mid)));
        }
        long double sum = 0.0;
        while (k--)
        {
            sum += pq.top();
            pq.pop();
        }
        if (sum >= 0)
        {
            ans = mid;
            low = mid;
        }
        else
        {
            high = mid;
        }
    }
    cout << fixed << setprecision(6) << ans << "\n";
}
bool check_ugly_number(long long mid, long long a, long long b, long long c, long long n)
{
    // Using inclusion and exclusion principle
    long long cnt = 0;
    // (Number of elements <= mid) >= n
    cnt += mid / a;
    cnt += mid / b;
    cnt += mid / c;
    cnt -= mid / lcm(a, b);
    cnt -= mid / lcm(b, c);
    cnt -= mid / lcm(a, c);
    cnt += mid / (lcm(lcm(a, b), c));
    return cnt >= n;
}
int nthUglyNumber(int n, int a, int b, int c)
{
    long long low = 1;
    long long high = 1e10;
    long long ans = 0;
    while (low <= high)
    {
        long long mid = (low + (high - low) / 2);
        if (check_ugly_number(mid, a, b, c, n))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return ans;
}
void array_division()
{
}
long double get_time(ll num_operations, long double a, long double b)
{
    return (((long double)num_operations * b) + (a / sqrt((num_operations + 1))));
}
// Ternary search for problems that will be convex upwards or convex downwards.
void freefall()
{
    long double a, b;
    cin >> a >> b;
    long double low = 0;
    long double high = (a + b - 1) / b;
    long double ans = 0;
    while (low <= high)
    {
        long long mid = (low + high) / 2;
        if (get_time(mid, a, b) <= get_time(mid + 1, a, b))
        {
            ans = get_time(mid, a, b);
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << fixed << setprecision(15) << ans << "\n";
}
bool check_color_ball(ll mid, vector<ll> &balls, ll n, ll k, unordered_map<ll, ll> &freq_map)
{
    // Divinding one by one so k*x minimum balls must be required so group
    // in K always if possible otherwise split 1-by-1 to each group .
    ll cnt = 0;
    for (auto it : freq_map)
    {
        cnt += min(it.second, k);
    }
    if (cnt >= k * mid)
        return true;
    return false;
}
void color_ball()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    unordered_map<ll, ll> freq_map;

    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        freq_map[v[x]]++;
    }
    ll low = 0;
    ll high = n;
    ll ans = 0;
    while (low <= high)
    {
        ll mid = (high + low) / 2;
        if (check_color_ball(mid, v, n, k, freq_map))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << ans << "\n";
}
bool check_min_subarray_len(int length, vector<int> &nums, int target)
{
    int l = 0;
    int r = 0;
    bool flag = false;
    int sum = 0;
    while (l <= r)
    {
        if ((r + 1) <= length && flag == false)
        {
            sum += nums[r];
            if ((r + 1) >= length)
            {
                flag = true;
                continue;
            }
            r++;
        }
        else
        {
            if (sum >= target)
                return true;
            target -= nums[l];
            if ((r + 1) < nums.size())
            {
                target += nums[r + 1];
            }
            l++;
            r++;
        }
    }
    return false;
}
int minSubArrayLen(int target, vector<int> &nums)
{
    int low = 0;
    int high = nums.size();
    int ans = INT_MAX;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (check_min_subarray_len(mid, nums, target))
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    ans == INT_MAX ? ans = 0 : ans = ans;
    cout << ans << "\n";
}
bool check_equal_substring(int mid, string s, string t, int maxCost)
{
    int l = 0;
    int r = 0;
    bool flag = false;
    int sum = 0;
    while (l <= r)
    {
        if ((r + 1) <= mid && flag == false)
        {
            sum += abs(s[r] - t[r]);
            if ((r + 1) >= mid)
            {
                flag = true;
                continue;
            }
            r++;
        }
        else
        {
            if (sum <= maxCost)
                return true;
            sum -= abs(s[l] - t[l]);
            if ((r + 1) < t.size())
            {
                sum += abs(t[r + 1] - s[r + 1]);
            }
            l++;
            r++;
        }
    }
    return false;
}
int equalSubstring(string s, string t, int maxCost)
{
    int low = 0;
    int high = s.length();
    int ans = 0;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (check_equal_substring(mid, s, t, maxCost))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return ans;
}
int kthDigit(long long k)
{
    ll digits = 1;
    ll power = 0;
    ll batch_size = 9;
    ll total_batch_count = 0;
    while (1)
    {
        ll total_size = batch_size * digits * pow(10, power);
        if (k - total_size <= 0)
        {
            break;
        }
        if (power != 0)
        {
            total_batch_count += pow(10, power - 1) * batch_size;
        }
        else if (power == 0)
        {
            total_batch_count++;
        }
        k -= total_size;
        digits++;
        power++;
    }
    ll smaller_batch_size = (k - 1) / (digits * 10);
    smaller_batch_size += 1;
    ll end = (pow(10, power) + (smaller_batch_size * 10)) - 1;
    ll start = end - 9;
    k -= ((smaller_batch_size - 1) * digits * 10);

    total_batch_count += ((smaller_batch_size));

    string interval_digits = "";
    if (total_batch_count % 2 != 0)
    {
        for (ll x = start; x <= end; x++)
        {
            ll cur_num = x;
            string small = "";
            while (cur_num >= 1)
            {
                ll digit = cur_num % 10;
                cur_num /= 10;
                string s = to_string(digit);
                small.push_back(s[0]);
            }
            reverse(small.begin(), small.end());
            interval_digits += small;
        }
    }
    else
    {
        for (ll x = end; x >= start; x--)
        {
            ll cur_num = x;
            string small = "";
            while (cur_num >= 1)
            {
                ll digit = cur_num % 10;
                cur_num /= 10;
                string s = to_string(digit);
                small.push_back(s[0]);
            }
            reverse(small.begin(), small.end());
            interval_digits += small;
        }
    }
    char final_digit = interval_digits[k - 1];
    string s_dash = "";
    s_dash.push_back(final_digit);
    return stoi(s_dash);
}
bool check_seperate_squares(long double y_coordinate, vector<vector<int>> &squares)
{
    long double area_above = 0.0;
    long double area_below = 0.0;
    for (int x = 0; x < squares.size(); x++)
    {
        int x_c = squares[x][0];
        int y_c = squares[x][1];
        int square_side_len = squares[x][2];

        long double bottom = y_c;
        long double top = y_c + square_side_len;

        if (y_coordinate >= top)
        {
            area_below += (long double)square_side_len * square_side_len;
        }
        else if (y_coordinate <= bottom)
        {
            area_above += (long double)square_side_len * square_side_len;
        }
        else
        {
            long double height_below = y_coordinate - bottom;
            long double height_above = top - y_coordinate;

            area_below += height_below * square_side_len;
            area_above += height_above * square_side_len;
        }
    }
    if (area_below <= area_above)
        return false;
    return true;
}
double separateSquares(vector<vector<int>> &squares)
{
    long double low = 0.0;
    long double high = 1e9;
    long double ans = 0.0;
    while (abs(low - high) >= EPSILON)
    {
        long double mid = (low + high) / 2;
        if (check_seperate_squares(mid, squares))
        {
            ans = mid;
            high = mid;
        }
        else
        {
            low = mid;
        }
    }
    return ans;
}
vector<int> leftmostBuildingQueries(vector<int> &heights, vector<vector<int>> &queries)
{
}
int nearestDrone(vector<vector<int>> &drones, vector<int> &target)
{
    vector<pair<int, int>> v;
    for (int x = 0; x < drones.size(); x++)
    {
        if ((abs(target[0] - drones[x][0]) +
             abs(target[1] - drones[x][1])) <= drones[x][2])
        {
            v.push_back({abs(target[0] - drones[x][0]) +
                             abs(target[1] - drones[x][1]),
                         x});
        }
    }
    sort(v.begin(), v.end(), [](pair<int, int> &p1, pair<int, int> &p2)
         {
    if (p1.first == p2.first)
        return p1.second > p2.second;
    return p1.first > p2.first; });
    if (v.size() == 0)
        return -1;
    return v[v.size() - 1].second;
}
int minOperations(string s)
{

    int n = s.size();
    int ans = INT_MAX;

    for (int r = 0; r < n; r++)
    {

        int ops = r;

        for (int i = 0; i < n / 2; i++)
        {

            char left = s[(i + r) % n];
            char right = s[(n - 1 - i + r) % n];

            int f1 = (right - left + 26) % 26;
            int f2 = (left - right + 26) % 26;

            ops += min(f1, f2);
        }

        ans = min(ans, ops);
    }

    return ans;
}
bool check_kth_excluded(ll mid, vector<ll> &v, ll k)
{
    // (Number of elements <= mid )>= K
    ll normal = mid;
    auto extra = upper_bound(v.begin(), v.end(), mid) - v.begin();
    return ((normal - extra) >= k);
}
void kth_excluded()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
        cin >> v[x];
    sort(v.begin(), v.end());
    while (q--)
    {
        ll k;
        cin >> k;
        ll low = 0;
        ll high = 1e18;
        ll ans = 0;
        while (low <= high)
        {
            ll mid = (low + high) / 2;
            if (check_kth_excluded(mid, v, k))
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        cout << ans << "\n";
    }
}
/*
You are given a sequence of length N: A=(A1​,…,AN​).
Answer Q queries given in the following format.
You are given integers L, R, and X. Find the number of elements among AL​,…,AR​ whose values are equal to X.
*/
void beaver_2nd()
{
    int n, m;
    cin >> n >> m;
    ;

    long long v1 = 0, v2 = 0;
    for (int i = 0; i < n; i++)
    {
        long long num;
        cin >> num;
        if (i == 0)
            v1 = num;
    }
    for (int i = 0; i < m; i++)
    {
        long long num;
        cin >> num;
        if (i == 0)
            v2 = num;
    }
    if ((v1 + n) >= (v2 + m))
        cout << 1 << "\n";
    else
    {
        cout << 2 << "\n";
    }
}
void range_count_query()
{
    ll n, q;
    cin >> n;
    vector<ll> v(n);
    unordered_map<int, vector<int>> m;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        m[v[x]].push_back(x);
    }
    cin >> q;
    while (q--)
    {
        ll l, r, x;
        cin >> l >> r >> x;
        ll final_len = (lower_bound(m[x].begin(), m[x].end(), r) - (lower_bound(m[x].begin(), m[x].end(), l - 1)));
        cout << final_len << "\n";
    }
}
bool check_burgers(ll mid, vector<ll> &v1, vector<ll> &cost, ll total_money, string s)
{
    ll bread_r = 0;
    ll cheese_r = 0;
    ll slice_r = 0;

    for (auto ch : s)
    {
        if (ch == 'B')
        {
            bread_r++;
        }
        else if (ch == 'S')
        {
            slice_r++;
        }
        else
        {
            cheese_r++;
        }
    }
    ll total_bread_required = mid * bread_r;
    ll total_slice_required = mid * slice_r;
    ll total_cheese_required = mid * cheese_r;
    ll extra_cost_required = 0;
    if (total_bread_required <= v1[0] && total_slice_required <= v1[1] && total_cheese_required <= v1[2])
    {
        return true;
    }
    else if (total_bread_required <= v1[0] && total_slice_required <= v1[1])
    {
        extra_cost_required += abs(v1[2] - total_cheese_required) * cost[2];
    }
    else if (total_slice_required <= v1[1] && total_cheese_required <= v1[2])
    {
        extra_cost_required += abs(v1[0] - total_bread_required) * cost[0];
    }
    else if (total_bread_required <= v1[0] && total_cheese_required <= v1[2])
    {
        extra_cost_required += abs(v1[1] - total_slice_required) * cost[1];
    }
    else if (total_bread_required > v1[0] && total_slice_required > v1[1])
    {
        extra_cost_required += abs(v1[0] - total_bread_required) * cost[0];
        extra_cost_required += abs(v1[1] - total_slice_required) * cost[1];
    }
    else if (total_slice_required > v1[1] && total_cheese_required > v1[2])
    {
        extra_cost_required += abs(v1[1] - total_slice_required) * cost[1];
        extra_cost_required += abs(v1[2] - total_cheese_required) * cost[2];
    }
    else if (total_bread_required > v1[0] && total_cheese_required > v1[2])
    {
        extra_cost_required += abs(v1[0] - total_bread_required) * cost[0];
        extra_cost_required += abs(v1[2] - total_cheese_required) * cost[2];
    }
    else
    {
        extra_cost_required += abs(v1[0] - total_bread_required) * cost[0];
        extra_cost_required += abs(v1[1] - total_slice_required) * cost[1];
        extra_cost_required += abs(v1[2] - total_cheese_required) * cost[2];
    }
    if (extra_cost_required <= total_money)
    {
        return true;
    }
    return false;
}
void hamburgers()
{
    /*
        nb,ns and nc and BSC -- bottom to top and bread,sausage and cheese respectively .
        pb,ps and pc are the respective prices of each item.
        bread,sausages and cheese pieces.
        total r rubles is the total money tha the person can use to buy the items.
    */
    string s;
    cin >> s;
    ll bread_count, slice_count, cheese_count;
    cin >> bread_count >> slice_count >> cheese_count;
    vector<ll> v1 = {bread_count, slice_count, cheese_count};
    ll bread_cost, slice_cost, cheese_cost;
    cin >> bread_cost >> slice_cost >> cheese_cost;
    vector<ll> v2 = {bread_cost, slice_cost, cheese_cost};

    ll total_money;
    cin >> total_money;
    ll low = 0;
    ll high = 1e18;
    ll ans = 0;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (check_burgers(mid, v1, v2, total_money, s))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
}
void random_fixed_window()
{
    ll n, d;
    cin >> n >> d;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
        cin >> v[x];
    unordered_map<ll, ll> m;
    ll distinct = 0;
    for (ll x = 0; x <= d - 1; x++)
    {
        if (!m.count(v[x]))
        {
            distinct++;
        }
        m[v[x]]++;
    }
    ll l = 0;
    ll r = d - 1;
    ll pen = distinct;
    while (l <= r && r < v.size())
    {
        if (distinct <= pen)
        {
            pen = min(pen, distinct);
        }
        m[v[l]]--;
        if (m[v[l]] <= 0)
        {
            distinct--;
            m.erase(v[l]);
        }
        if ((r + 1) < n)
        {
            if (!m.count(v[r + 1]))
            {
                distinct++;
            }
            m[v[r + 1]]++;
        }
        l++;
        r++;
    }
    cout << pen << "\n";
}
bool check_midnight_lamp(ll mid, ll k, ll n)
{
    ll total_written = mid;
    ll curr_power = 1;
    while (1)
    {
        ll deno = floor(mid / pow(k, curr_power));
        if (deno == 0)
            break;
        else
        {
            total_written += deno;
        }
        curr_power++;
    }
    return total_written >= n;
}
void midnight_lamp()
{
    ll n, k;
    cin >> n >> k;
    ll low = 1;
    ll high = 1e9;
    ll ans = 0;

    while (low <= high)
    {
        ll mid = low + (high - low) / 2;

        if (check_midnight_lamp(mid, k, n))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << ans << "\n";
}
void count_zeros_maxm()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    ll head = -1;
    ll tail = 0;
    ll ans = INT_MIN;
    ll cnt_0 = 0;
    while (tail <= n)
    {
        while ((head + 1) < n && (v[head + 1] == 1) || (v[head + 1] == 0 && cnt_0 < k))
        {
            if (v[head + 1] == 0)
                cnt_0++;
            head++;
        }
        ans = max(ans, (head - tail + 1));
        if (tail <= head)
        {
            if (v[tail] == 0)
                cnt_0--;
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    cout << ans << "\n";
}
void cnt_distinct_element()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    ll distinct_cnt = 0;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    ll head = -1;
    ll tail = 0;
    ll ans = 0;
    unordered_map<ll, ll> freq_map;

    while (tail < n)
    {
        while ((head + 1) < n && ((distinct_cnt < k) || (distinct_cnt == k && freq_map.count(v[head + 1]))))
        {
            head++;
            if (freq_map.count(v[head]) == false)
            {
                distinct_cnt++;
            }
            freq_map[v[head]]++;
        }
        ans += (head - tail + 1);
        if (tail <= head)
        {
            freq_map[v[tail]]--;
            if (freq_map[v[tail]] <= 0)
            {
                freq_map.erase(v[tail]);
                distinct_cnt--;
            }
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    cout << ans << "\n";
}
void longest_distinct_subarray()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    ll distinct_cnt = 0;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    ll head = -1;
    ll tail = 0;
    ll ans = 0;
    unordered_map<ll, ll> freq_map;

    while (tail < n)
    {
        while ((head + 1) < n && (freq_map.count(v[head + 1]) == false))
        {
            head++;
            if (freq_map.count(v[head]) == false)
            {
                distinct_cnt++;
            }
            freq_map[v[head]]++;
        }
        ans = max(ans, head - tail + 1);
        if (tail <= head)
        {
            freq_map[v[tail]]--;
            if (freq_map[v[tail]] <= 0)
            {
                freq_map.erase(v[tail]);
                distinct_cnt--;
            }
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    cout << ans << "\n";
}
void shortest_subarray()
{
    ll n;
    cin >> n;
    vector<ll> v(n);
    ll distinct_cnt = 0;
    unordered_set<ll> st;
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
        st.insert(v[x]);
    }
    // Distinct elements equal k where k is total .
    // finding longest subarray having distinct elements <= (k-1) will find answer .
    ll k = (ll)st.size() - 1;
    ll head = -1;
    ll tail = 0;
    ll ans = (ll)v.size();
    unordered_map<ll, ll> freq_map;

    while (tail < n)
    {
        while ((head + 1) < n && ((distinct_cnt < k) || (distinct_cnt == k && freq_map.count(v[head + 1]))))
        {
            head++;
            if (freq_map.count(v[head]) == false)
            {
                distinct_cnt++;
            }
            freq_map[v[head]]++;
        }
        if ((head + 1) < n)
        {
            ans = min(ans, (head - tail + 1) + 1);
        }
        if (tail <= head)
        {
            freq_map[v[tail]]--;
            if (freq_map[v[tail]] <= 0)
            {
                freq_map.erase(v[tail]);
                distinct_cnt--;
            }
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    cout << ans << "\n";
}
void subarray_sum_less_k()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    ll head = -1;
    ll tail = 0;
    ll ans = 0;
    ll curr_sum = 0;
    while (tail < n)
    {
        while ((head + 1) < n && (curr_sum + v[head + 1] <= k))
        {
            head++;
            curr_sum += v[head];
        }
        ans += (head - tail + 1);
        if (tail <= head)
        {
            curr_sum -= v[tail];
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    cout << ans << "\n";
}
int minimumScore(vector<vector<int>> &grid)
{
    int n = grid.size();

    if (n == 0)
    {
        return 0;
    }

    for (auto &row : grid)
    {
        if (row.empty())
        {
            return -1;
        }

        sort(row.begin(), row.end());
    }

    using State = tuple<int, int, int>;
    priority_queue<State, vector<State>, greater<State>> minimumHeap;

    int currentMaximum = LLONG_MIN;

    for (int row = 0; row < n; row++)
    {
        minimumHeap.push({grid[row][0], row, 0});
        currentMaximum = max(currentMaximum, grid[row][0]);
    }

    int answer = LLONG_MAX;

    while (true)
    {
        auto [currentMinimum, row, position] = minimumHeap.top();
        minimumHeap.pop();

        answer = min(answer, currentMaximum - currentMinimum);

        int nextPosition = position + 1;

        if (nextPosition == (int)grid[row].size())
        {
            break;
        }

        int nextValue = grid[row][nextPosition];
        minimumHeap.push({nextValue, row, nextPosition});
        currentMaximum = max(currentMaximum, nextValue);
    }

    return answer;
}
void is_subsequence()
{
    ll n, m;
    cin >> n >> m;
    vector<ll> v1(n);
    for (ll x = 0; x < n; x++)
        cin >> v1[x];
    vector<ll> v2(m);
    for (ll x = 0; x < m; x++)
        cin >> v2[x];

    ll head_1 = 0;
    ll head_2 = 0;
    while ((head_1) < n && head_2 < m)
    {
        if (v1[head_1] == v2[head_2] && (head_2 + 1) >= m)
        {
            cout << "YES" << "\n";
            return;
        }
        else if (v1[head_1] == v2[head_2])
        {
            head_1++;
            head_2++;
        }
        if (v1[head_1] != v2[head_2])
        {
            head_1++;
        }
    }
    cout << "NO" << "\n";
}
vector<vector<int>> threeSum(vector<int> &nums)
{
    vector<vector<int>> ans;
    set<int> visited;

    sort(nums.begin(), nums.end());
    for (int x = 0; x < nums.size(); x++)
    {
        int i = x + 1;
        int j = nums.size() - 1;
        if (visited.count(nums[x]))
            continue;
        visited.insert(nums[x]);
        while (i < j)
        {
            int sum = (nums[x] + nums[i] + nums[j]);
            if (sum < 0)
            {
                i++;
            }
            else if (sum > 0)
            {
                j--;
            }
            else
            {
                ans.push_back({nums[x], nums[i], nums[j]});
                i++;
                while (nums[i] == nums[i - 1] && i < j)
                {
                    i++;
                }
            }
        }
    }
    return ans;
}
ll inclusion_exclusion_k_non_prime(vector<int> &coins, ll mid)
{
    int sum = 0;
    for (int msk = 1; msk < (1 << coins.size()); ++msk)
    {
        int mult = -1,
            bits = 0;
        for (int i = 0; i < (int)coins.size(); ++i)
        {
            if (msk & (1 << i))
            {
                ++bits;
                if (mult == -1)
                    mult = coins[i];
                else if (mult != -1)
                {
                    mult = lcm(mult, coins[i]);
                }
            }
        }

        int cur = mid / mult;
        if (bits % 2 == 1)
            sum += cur;
        else
            sum -= cur;
    }
    return mid - sum;
    // cout << mid - sum << "\n";
}
bool check_find_kth_smallest(long long mid, vector<int> &coins, int k)
{
    // (Finding number of elements <= mid ) >= k
    return inclusion_exclusion_k_non_prime(coins, mid) >= k;
}
long long findKthSmallest(vector<int> &coins, int k)
{
    ll start = 0;
    for (ll x = 0; x < coins.size(); x++)
    {
        start = min(start, (ll)coins[x]);
    }
    ll end = 1e18;
    ll ans = 0;
    while (start <= end)
    {
        ll mid = (start + (end - start) / 2);
        if (check_find_kth_smallest(mid, coins, k))
        {
            ans = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return ans;
}
void inclusion_exclusion_k()
{
    int n, r;
    cin >> n >> r;
    vector<int> p;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
        {
            p.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        p.push_back(n);

    int sum = 0;
    for (int msk = 1; msk < (1 << p.size()); ++msk)
    {
        cout << "{ ";
        int mult = 1,
            bits = 0;
        for (int i = 0; i < (int)p.size(); ++i)
        {
            if (msk & (1 << i))
            {
                cout << p[i] << " ";
                ++bits;
                mult *= p[i];
            }
        }
        cout << "} -> mult = " << mult << "\n";

        int cur = r / mult;
        if (bits % 2 == 1)
            sum += cur;
        else
            sum -= cur;
    }

    cout << r - sum << "\n";
}
bool check_kth_number(ll mid, ll n, ll m, ll k)
{
    ll cnt = 0;
    for (ll x = 1; x <= n; x++)
    {
        cnt += min(m, mid / x);
    }
    return cnt >= k;
}
int findKthNumber(int m, int n, int k)
{
    ll start = 1;
    ll end = 1e18;
    ll ans = 0;
    while (start <= end)
    {
        ll mid = (start + (end - start) / 2);
        if (check_kth_number(mid, n, m, k))
        {
            ans = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return ans;
}
bool check_kth_number(ll mid, vector<vector<int>> &matrix, ll k)
{
    ll cnt = 0;
    for (ll x = 0; x < matrix.size(); x++)
    {
        auto it = upper_bound(matrix[x].begin(), matrix[x].end(), mid) - matrix[x].begin();
        cnt += it;
    }
    return cnt >= k;
}
int kthSmallest(vector<vector<int>> &matrix, int k)
{
    ll start = -1e9;
    ll end = 1e9;
    ll ans = 0;
    while (start <= end)
    {
        ll mid = (start + (end - start) / 2);
        if (check_kth_number(mid, matrix, k))
        {
            ans = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return ans;
}
bool check_smallest_distance_pair(ll mid, vector<int> &nums, int k)
{
    ll cnt = 0;
    for (int x = 0; x < nums.size(); x++)
    {
        auto pos =
            upper_bound(nums.begin() + x + 1, nums.end(), (mid + nums[x])) -
            nums.begin();
        cnt += (pos - x - 1);
    }
    return cnt >= k;
}
int smallestDistancePair(vector<int> &nums, int k)
{
    sort(nums.begin(), nums.end());
    ll start = 0;
    ll end = nums[nums.size() - 1] - nums[0];
    ll ans = 0;
    while (start <= end)
    {
        ll mid = (start + (end - start) / 2);
        if (check_smallest_distance_pair(mid, nums, k))
        {
            ans = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return ans;
}
int findRadius(vector<int> &houses, vector<int> &heaters)
{
    int ans = INT_MAX;
    sort(heaters.begin(), heaters.end());
    for (int x = 0; x < houses.size(); x++)
    {
        auto it = lower_bound(heaters.begin(), heaters.end(), houses[x]);
        if (it == heaters.end())
        {
            int local_min = (houses[x] - *heaters.rbegin());
            ans = max(ans, local_min);
        }
        else
        {
            int local_min = (*it - houses[x]);
            if (it != heaters.begin())
            {
                it--;
                local_min = min(local_min, (houses[x] - *it));
            }
            ans = max(ans, local_min);
        }
    }
    return ans;
}
bool check_max_possible_score(long long mid, vector<int> &start, int d)
{
    long long prev = start[0];
    for (int x = 1; x < start.size(); x++)
    {
        // Any value >= mid is valid .
        // Having 3 cases respectively prev+mid >= start & <= end
        // prev+mid < start so it will satisfy >= mid so we will take next
        // start as the newer value and prev+mid > end then it is not
        // possible .
        if ((prev + mid) >= start[x] && (prev + mid) <= (start[x] + d))
        {
            prev = prev + mid;
        }
        else if ((prev + mid) < start[x])
        {
            prev = start[x];
        }
        else
        {
            return false;
        }
    }
    return true;
}
int maxPossibleScore(vector<int> &start, int d)
{
    long long ans = 0;
    long long low = 0;
    long long high = 1e18;

    sort(start.begin(), start.end());
    while (low <= high)
    {
        long long mid = (low + (high - low) / 2);
        if (check_max_possible_score(mid, start, d))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return ans;
}
bool compute_new_cost(ll k, ll tail, ll head, multiset<ll> &st, vector<ll> &nums)
{
    ll curr_mini = *st.begin();
    ll curr_maxi = *st.rbegin();
    if (curr_maxi < nums[head])
    {
        curr_maxi = nums[head];
    }
    if (curr_mini > nums[head])
    {
        curr_mini = nums[head];
    }
    return ((curr_maxi - curr_mini) * (head - tail + 1)) <= k;
}
long long countSubarrays(vector<ll> &nums, long long k)
{

    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    ll head = -1;
    ll tail = 0;
    ll ans = 0;
    multiset<ll> st;
    while (tail < n)
    {
        while ((head + 1) < n && compute_new_cost(k, tail, head, st, nums))
        {
            head++;
            st.insert(nums[head]);
        }
        ans += (head - tail + 1);
        if (tail <= head)
        {
            tail++;
            ll curr_mini = *st.begin();
            ll curr_maxi = *st.rbegin();
            if (curr_maxi == nums[tail] && curr_mini != nums[tail])
            {
                st.erase(st.find(*st.rbegin()));
            }
            else if (curr_maxi != nums[tail] && curr_mini == nums[tail])
            {
                st.erase(st.find(*st.begin()));
            }
            else if (curr_maxi == nums[tail] && curr_mini == nums[tail])
            {
                st.erase(st.find(*st.rbegin()));
            }
            else
            {
                st.erase(st.find(nums[tail]));
            }
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    cout << ans << "\n";
}
// int subarraysWithKDistinct(vector<ll>& v, int k) {
//     return cnt_distinct_element(v, k) - cnt_distinct_element(v, k - 1);
// }
int lengthOfLongestSubstring(string s)
{
    int start = 0;
    int end = 0;
    string sub = "";
    int cnt = 0;
    unordered_map<char, int> m;
    while (start <= end && end < s.length())
    {
        m[s[end]] += 1;
        sub.push_back(s[end]);
        if (m[s[end]] > 1)
        {
            cnt = max(cnt, (end - start));
            unordered_map<char, int> m2;
            m = m2;
            sub = "";
            start++;
            end = start;
        }
        else if (m[s[end]] <= 1)
        {
            end++;
            if (end >= s.length())
            {
                cnt = max(cnt, (end - start));
                unordered_map<char, int> m2;
                m = m2;
                sub = "";
                start++;
                end = start;
            }
        }
    }
    return cnt;
}
int numRescueBoats(vector<int> &people, int limit)
{
    sort(people.begin(), people.end());
    int s = 0;
    int e = people.size() - 1;
    int cnt = 0;
    while (s <= e)
    {
        if ((people[s] + people[e]) <= limit)
        {
            cnt += 1;
            s++;
            e--;
        }
        else if ((people[s] + people[e]) > limit)
        {
            cnt += 1;
            e--;
        }
    }
    return cnt;
}
int countDistinct(vector<int> &nums, int k, int p)
{
    int head = -1;
    int tail = 0;
    int ans = 0;
    int cnt = 0;
    while (tail < nums.size())
    {
        while ((head + 1) < nums.size() && ((cnt < k) || (cnt == k && nums[head + 1] % p != 0)))
        {
            head++;
            if (nums[head] % p == 0)
                cnt++;
        }
        ans += (head - tail + 1);
        if (tail <= head)
        {
            if (nums[tail] % p == 0)
                cnt--;
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    return ans;
}
bool compute_subarray(vector<int> &nums, long long k, long long head_pos, long long tail_pos, long long curr_sum)
{
    curr_sum += nums[head_pos];
    return (curr_sum * (head_pos - tail_pos + 1)) <= k;
}
long long countSubarrays(vector<int> &nums, long long k)
{
    long long head = -1;
    long long tail = 0;
    long long ans = 0;
    long long sum = 0;
    while (tail < nums.size())
    {
        while ((head + 1) < nums.size() && compute_subarray(nums, k, head + 1, tail, sum))
        {
            head++;
            sum += nums[head];
        }
        ans += (head - tail + 1);
        if (tail <= head)
        {
            sum -= nums[tail];
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    return ans;
}
vector<vector<int>> findDisappearedNumbers(vector<int> &nums, int lower,
                                           int upper)
{
    vector<vector<int>> ans;
    bool start_flag = true;
    bool end_flag = false;
    unordered_set<int> st;
    for (auto it : nums)
        st.insert(it);
    for (int x = lower; x <= upper; x++)
    {
        if (!st.count(x) && start_flag == true)
        {
            ans.push_back({x, -1});
            end_flag = true;
            start_flag = false;
        }
        if (st.count(x) && end_flag == true)
        {
            if (ans.size() != 0)
            {
                vector<int> v = ans.back();
                ans[ans.size() - 1] = {v[0], x - 1};
            }
            start_flag = true;
            end_flag = false;
        }
    }
    if (end_flag == true && ans.size() >= 1 && ans.back()[1] == -1)
    {
        vector<int> v = ans.back();
        ans[ans.size() - 1] = {v[0], upper};
    }

    return ans;
}
int longestSubarray(vector<int> &nums, int k)
{
    build_spf(100001);
    int head = -1;
    int tail = 0;
    int ans = 0;
    int distinct_cnt = 0;
    unordered_map<int, int> freq_map;
    while (tail < nums.size())
    {
        while ((head + 1) < nums.size())
        {
            int curr_num = nums[head + 1];
            int curr_distinct_cnt = distinct_cnt;
            unordered_map<ll, ll> curr_num_factors =
                compute_factors(curr_num);
            for (auto it : curr_num_factors)
            {
                int curr_factor = it.first;
                if (!freq_map.count(curr_factor))
                {
                    curr_distinct_cnt++;
                }
            }
            if (curr_distinct_cnt > k)
                break;
            head++;
            for (auto it : curr_num_factors)
            {
                int curr_factor = it.first;
                if (freq_map.count(curr_factor) == false)
                {
                    distinct_cnt++;
                }
                freq_map[curr_factor] += it.second;
            }
        }
        ans = max(ans, (head - tail + 1));
        if (tail <= head)
        {
            int curr_num = nums[tail];
            unordered_map<ll, ll> curr_num_factors =
                compute_factors(curr_num);
            for (auto it : curr_num_factors)
            {
                int curr_factor = it.first;
                freq_map[curr_factor] -= it.second;
                if (freq_map[curr_factor] <= 0)
                {
                    distinct_cnt--;
                    freq_map.erase(curr_factor);
                }
            }
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    return ans;
}
int longestSubstring(string s, int k)
{
    int ans = 0;
    // Iterating over the fixed number of
    // unique characters in a string or a substring .
    for (int x = 1; x <= 26; x++)
    {
        // Maximum 1 unique element can exist
        // so finding all substrings having unique <= 1
        // and checking each of this unique character has frequency >= k.
        unordered_map<char, int> freq_map;
        int curr_unique_cnt = 0;
        int maximum_unique_cnt = x;
        int head = -1;
        int tail = 0;
        while (tail < s.size())
        {
            // Eating as much as you can.
            while ((head + 1) < s.size() &&
                   ((curr_unique_cnt < maximum_unique_cnt) ||
                    curr_unique_cnt == maximum_unique_cnt &&
                        freq_map.count(s[head + 1])))
            {
                head++;
                if (!freq_map.count(s[head]))
                {
                    curr_unique_cnt++;
                }
                freq_map[s[head]]++;
            }
            // Updating answer on the basis of check.
            bool check_flag = true;
            for (auto it : freq_map)
            {
                if (it.second < k)
                {
                    check_flag = false;
                    break;
                }
            }
            // Updating ans if condition satisfies .
            if (check_flag)
            {
                ans = max(ans, (head - tail + 1));
            }
            // Removing tail element .
            if (tail <= head)
            {
                freq_map[s[tail]]--;
                if (freq_map[s[tail]] <= 0)
                {
                    freq_map.erase(s[tail]);
                    curr_unique_cnt--;
                }
                tail++;
            }
            else
            {
                tail++;
                head = tail - 1;
            }
        }
    }
    return ans;
}
bool check(unordered_map<char, int> &m,
           unordered_map<char, int> &m2,
           string s, string t, int head_pos)
{
    for (auto &[ch, cnt] : m)
    {
        if (m2[ch] < cnt)
            return false;
    }

    while (head_pos < (int)s.size())
    {
        char ch = s[head_pos];

        if (!m.count(ch))
        {
            head_pos++;
        }
        else if (m2[ch] > m[ch])
        {
            m2[ch]--;
            head_pos++;
        }
        else
        {
            break;
        }
    }

    return true;
}
string longestSubsequenceRepeatedK(string s, string t)
{
    int head = -1;
    int tail = 0;
    int ans_l = -1;
    int ans_r = -1;
    int len = INT_MAX;
    unordered_map<char, int> m;
    for (auto ch : t)
    {
        m[ch]++;
    }
    unordered_map<char, int> m2;
    while (tail < s.size())
    {
        // Eating as much as you can.
        while ((head + 1) < s.size() &&
               check(m, m2, s, t, head + 1))
        {
            head++;
            m2[s[head]]++;
        }
        if ((head - tail + 1) < len)
        {
            ans_l = tail;
            ans_r = head;
        }
        // Removing tail element .
        if (tail <= head)
        {
            m2[s[tail]]--;
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
    string ans = "";
    for (int x = ans_l; x <= ans_r; x++)
    {
        if (x <= 0 || x >= s.length())
            return "";
        ans.push_back(s[x]);
    }
    return ans;
}
bool check(unordered_map<char, int> &m, unordered_map<char, int> &m2)
{
    for (auto &[ch, cnt] : m)
    {
        if (m2[ch] < cnt)
            return false;
    }
    return true;
}
string minWindow(string s, string t)
{
    if (t.size() > s.size())
        return "";
    int head = -1;
    int tail = 0;
    int ans_l = -1;
    int len = INT_MAX;
    unordered_map<char, int> m;
    for (char ch : t)
        m[ch]++;
    unordered_map<char, int> m2;
    while (tail < (int)s.size())
    {
        while (head + 1 < (int)s.size() && !check(m, m2))
        {
            head++;
            m2[s[head]]++;
        }
        if (check(m, m2) && head - tail + 1 < len)
        {
            len = head - tail + 1;
            ans_l = tail;
        }

        m2[s[tail]]--;
        tail++;
    }
    if (ans_l == -1)
        return "";
    return s.substr(ans_l, len);
}
int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
    
}
int validSubarraySize(vector<int> &nums, int threshold)
{
}
void solve()
{
    // Approximated LRU in redis using idle time optimization and LRU clock .
    // zmalloc for tracking of amount of memory currently being consumed.
}
int main()
{
    // O(N)
    // factorial(MOD);
    // O(log log(n))
    // compute_primes();
    // compute_co_prime();
    // O(log log p)
    build_spf(1000000);
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    int t;
    // cin >> t;
    t = 1;
    while (t--)
    {
        solve();
    }
}

/*
    2 pointers -

    1)Form 0 - sliding window .
    2)Form 1 - dynamic window and L and R --- subarray based and gap minimization problems.
        i)eat as much as possible.
        ii)update ans.
        ii)remove 1 element.
    3)Form 2 - pointers converging .

    4)Form 3 - pointers on 2 different structures .



    // Monospace array having all 0s before 1s and vice-versa will fall under this category .
    // default case to be kept in mind thus following the same template for binary search and finding first one.
    // Forms - sublinear and binary search on answers,lower_bounds and binary search on every start .

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

    Greedy and sweep-line formulation
    swapping proof or exchange arguments for ordering based problems - min(dot-product) and problems and decay .
    greedy forward based problems covering problems of gas station its 3 variants.
    operator decoding based problems .

    NGE array creation, nse,pse,pge via both method of stack and non-stack version.
    histogram area

    STL patterns - algorithmic design problems such as LRU etc .

    1) Window maintainaince - find min of every k window, finding number of max,finding number of even or odd etc
    montonic deque applications.
    2) Subarray finding .
    3) Parantheses based questions.

    Finding mean,median and mode related designing questions and TopK pattern.
    Range maintainence ideas .

    */

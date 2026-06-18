#include <climits>
#include <unordered_set>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
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
void solve()
{
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
    long long n;
    cin >> n;
    dearrangement(n);
    long long ans = dearrange[n];
    cout << ans % MOD << endl;
}
int main()
{
    factorial(MOD);
    int t;
    // cin >> t;
    t = 1;
    while (t--)
    {
        solve();
    }
}

#include <iostream>
#include <unordered_map>
#include <climits>
#include <set>
#include <map>
#include <queue>
#include <list>
#include <algorithm>
#include <unordered_set>
#include <stack>
#include <vector>
typedef long long ll;
using namespace std;
class FreqStack
{
public:
    unordered_map<int, stack<int>> stack_map;
    unordered_map<int, int> freq_map;
    int freq;
    FreqStack()
    {
        this->freq = INT_MIN;
    }

    void push(int val)
    {
        // this will update the maximum frequency tracker
        this->freq = max(freq, freq_map[val]++);
        // pushing n times the values inside the stack map
        if (stack_map.count(freq_map[val]))
        {
            stack_map[freq_map[val]].push(val);
        }
        else
        {
            stack_map[freq_map[val]].push(val);
        }
    }

    int pop()
    {
        if (stack_map[freq].size() != 0 && stack_map.count(freq))
        {
            int top = stack_map[freq].top();
            stack_map[freq].pop();
            freq_map[top]--;
            return top;
        }
        else
        {
            freq--;
        }
        int top = stack_map[freq].top();
        stack_map[freq].pop();
        freq_map[top]--;
        return top;
    }
};
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
vector<vector<ll>> prefix_2d(vector<vector<ll>> &arr)
{
    vector<vector<ll>> pf(arr.size(), vector<ll>(arr[0].size(), 0));
    for (ll x = 0; x < pf.size(); x++)
    {
        for (ll y = 0; y < pf[0].size(); y++)
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
void solve_rect_sum_queries()
{
    ll n, q;
    cin >> n >> q;
    vector<vector<ll>> arr(n + 1, vector<ll>(n + 1, 0));
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            char num;
            cin >> num;
            if (num == '*')
            {
                arr[x][y] = 1;
            }
            else
            {
                arr[x][y] = 0;
            }
        }
    }
    vector<vector<ll>> pf_arr = prefix_2d(arr);

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
        cout << ans << "\n";
    }
}
vector<vector<ll>> partial_sum_2d(vector<vector<ll>> &queries, ll n, ll m)
{
    vector<vector<ll>> partial_sum_arr(n, vector<ll>(m, 0));
    for (ll i = 0; i < queries.size(); i++)
    {
        ll u = queries[i][0];
        ll l = queries[i][1];
        ll d = queries[i][2];
        ll r = queries[i][3];
        ll x = 1;

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
    return pse;
}
vector<ll> next_greater_equal_element(vector<ll> v)
{
    ll n = v.size();
    vector<ll> nge(v.size());
    for (ll x = v.size() - 1; x >= 0; x--)
    {
        nge[x] = x + 1;
        while (nge[x] != n && v[x] >= v[nge[x]])
        {
            nge[x] = nge[nge[x]];
        }
    }
    //     for (ll x = 0; x < n; x++)
    // {
    //     if (nge[x] == n)
    //     {
    //         cout << "No element which is next greater than or equal to" << v[x] << " exists \n";
    //     }
    //     else
    //     {
    //         cout << "Element greater than or equal to" << v[x] << " is " << v[nge[x]]<<" " <<nge[x] <<"\n";
    //     }
    // }
    // cout << "\n";
    return nge;
}
vector<ll> previous_greater_element(vector<ll> v)
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
    return pge;
}
vector<ll> previous_greater_equal_element(vector<ll> v)
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
    return pge;
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
    void remove(ll v)
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
// Monotonic stack in O(N) .
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
bool primes_arr[10000001];

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
void solve()
{
    // [1,3,6] ---> [0,1,0,0] -----> [1,2,3]
    // [1,2,3] ---> [1,0,1] -----> []
    // P[r]-P[l-1] = k
    // P[r] = k+P[l-1] selecting r and checking
    // P[l-1] = P[r]-k
    // [1,1,1,2,2] = [1,0,0,1,0] and k = 0
    // P[l-1] = P[r] for a,b and c all .
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    vector<int> consecutive_sequences, consecutive_sequences_len;
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && v[i] == v[i - 1])
            consecutive_sequences_len.back()++;
        else
        {
            consecutive_sequences.push_back(v[i]);
            consecutive_sequences_len.push_back(1);
        }
    }
    int ans = consecutive_sequences.size();
    int extra = 0;
    for (int x = 0; x + 1 < ans; x++)
    {
        if (consecutive_sequences_len[x] >= 2 && consecutive_sequences_len[x + 1] >= 2)
        {
            extra = 2;
            break;
        }
    }
    if (extra < 2)
    {
        for (int x = 0; x < ans; x++)
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
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    // t = 1;
    while (t--)
    {
        solve();
    }
}

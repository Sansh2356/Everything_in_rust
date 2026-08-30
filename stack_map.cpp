#include <iostream>
#include <unordered_map>
#include <climits>
#include <set>
#include <map>
#include <queue>
#include <list>
#include <algorithm>
#include <unordered_set>
#include <iomanip>
#include <cmath>
#include <stack>
#include <vector>
typedef long long ll;
const long double EPSILON = 1e-9; // or 10^-12
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
// VVIQ having the answer as the point of search space during binary search
void minimizing_difference()
{
}
int findMaxValueOfEquation(vector<vector<int>> &points, int k)
{
    return 1;
}
void pair_of_topics()
{
    ll n;
    cin >> n;
    vector<ll> a(n), b(n);
    vector<pair<ll, ll>> a_diff(n), b_diff(n);
    for (ll x = 0; x < n; x++)
        cin >> a[x];
    for (ll x = 0; x < n; x++)
        cin >> b[x];
}
void impartial_gift()
{
    ll n, m, d;
    cin >> n >> m >> d;
    vector<ll> a(n), b(m);
    for (ll x = 0; x < n; x++)
        cin >> a[x];
    for (ll x = 0; x < m; x++)
        cin >> b[x];
    sort(a.begin(), a.end());
    ll ans = -1;

    cout << ans << "\n";
}
void cses_sliding_window_sum()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
        cin >> v[x];
    ll head = -1;
    ll tail = 0;
    ll ans = -1;
    unordered_map<ll, ll> freq_map;
    ll distinct_cnt = 0;
    while (tail < n)
    {
        while ((head + 1) < n && ((head - tail + 1)) < k)
        {
            head++;
            if (!freq_map.count(v[head]))
                distinct_cnt++;
            freq_map[v[head]]++;
        }
        if ((head - tail + 1) == k)
        {
            cout << distinct_cnt << " ";
        }
        if (tail <= head)
        {
            freq_map[v[tail]]--;
            if (freq_map[v[tail]] <= 0)
                distinct_cnt--;
            tail++;
        }
        else
        {
            tail++;
            head = tail - 1;
        }
    }
}
class SegtreeNode
{
public:
    ll sum;
    SegtreeNode()
    {
        this->sum = 0;
    }
};
SegtreeNode merge(SegtreeNode a, SegtreeNode b)
{
    SegtreeNode newNode = SegtreeNode();
    newNode.sum = (a.sum + b.sum);
    return newNode;
}
SegtreeNode segtree[4 * 1000001];
void build_seg_tree(ll node, ll left_range, ll right_range, vector<ll> &v)
{
    if (left_range == right_range)
    {
        segtree[node].sum = v[left_range];
        return;
    }
    ll mid = (left_range + right_range) / 2;
    build_seg_tree(2 * node, left_range, mid, v);
    build_seg_tree(2 * node + 1, mid + 1, right_range, v);
    segtree[node] = merge(segtree[2 * node], segtree[2 * node + 1]);
}
void update_seg_tree(ll node, ll left_range, ll right_range, ll new_val, ll pos)
{
    if (pos < left_range || pos > right_range)
    {
        return;
    }
    if (left_range == right_range)
    {
        segtree[node].sum = new_val;
        return;
    }
    ll mid = (left_range + right_range) / 2;
    update_seg_tree(2 * node, left_range, mid, new_val, pos);
    update_seg_tree(2 * node + 1, mid + 1, right_range, new_val, pos);
    segtree[node] = merge(segtree[2 * node], segtree[2 * node + 1]);
}
SegtreeNode query_seg_tree(ll node, ll left_range, ll right_range, ll left_query_range, ll right_query_range)
{
    if (right_query_range < left_range || left_query_range > right_range)
    {
        return SegtreeNode();
    }
    if (left_range >= left_query_range && right_query_range >= right_range)
    {
        return segtree[node];
    }
    ll mid = (left_range + right_range) / 2;
    return merge(query_seg_tree(2 * node, left_range, mid, left_query_range, right_query_range), query_seg_tree(2 * node + 1, mid + 1, right_range, left_query_range, right_query_range));
}
void dynamic_range_minimum_queries()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    build_seg_tree(1, 0, n - 1, v);
    while (q--)
    {
        int query_type;
        cin >> query_type;
        if (query_type == 1)
        {
            ll k, u;
            cin >> k >> u;
            k--;
            update_seg_tree(1, 0, n - 1, u, k);
        }
        else if (query_type == 2)
        {
            ll a, b;
            cin >> a >> b;
            a--;
            b--;
            cout << query_seg_tree(1, 0, n - 1, a, b).sum << "\n";
        }
    }
}
void range_xor_queries()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (ll x = 0; x < n; x++)
    {
        cin >> v[x];
    }
    build_seg_tree(1, 0, n - 1, v);
    while (q--)
    {

        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        cout << query_seg_tree(1, 0, n - 1, a, b).sum << "\n";
    }
}
int total_ans = 0;
bool check_rec_s_queen(vector<vector<bool>> &visited, int n, int curr_col, int curr_row)
{
    for (int r = curr_row - 1; r >= 0; r--)
        if (visited[r][curr_col])
            return false;

    for (int r = curr_row - 1, c = curr_col - 1; r >= 0 && c >= 0; r--, c--)
        if (visited[r][c])
            return false;

    for (int r = curr_row - 1, c = curr_col + 1; r >= 0 && c < n; r--, c++)
        if (visited[r][c])
            return false;

    int km[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    for (auto &m : km)
    {
        int r = curr_row + m[0];
        int c = curr_col + m[1];
        if (r >= 0 && r < n && c >= 0 && c < n && visited[r][c])
            return false;
    }

    return true;
}
void rec_s_queen(int row, vector<vector<bool>> &visited, int n)
{
    if (row == n)
    {
        total_ans++;
        return;
    }
    for (int x = 0; x < n; x++)
    {
        if (!visited[row][x] && check_rec_s_queen(visited, n, x, row))
        {
            visited[row][x] = true;
            rec_s_queen(row + 1, visited, n);
            visited[row][x] = false;
        }
    }
}
void s_queens()
{
    int n;
    cin >> n;
    vector<vector<bool>> visited(n, vector<bool>(n));
    rec_s_queen(0, visited, n);
    cout << total_ans << "\n";
}
vector<string> all_parantheses;
void solve(string op, int open, int close)
{
    if (open == 0 && close == 0)
    {
        all_parantheses.push_back(op);
        return;
    }
    if (open == close)
    {
        string op1 = op;
        op1.push_back('(');
        solve(op1, open - 1, close);
    }
    else if (open == 0)
    {
        string op1 = op;
        op1.push_back(')');
        solve(op1, open, close - 1);
    }
    else if (close == 0)
    {
        string op1 = op;
        op1.push_back('(');
        solve(op1, open - 1, close);
    }
    else
    {
        string op1 = op;
        string op2 = op;
        op1.push_back('(');
        op2.push_back(')');
        solve(op1, open - 1, close);
        solve(op2, open, close - 1);
    }
}
bool check_meeting_place(long double maxi_time, vector<ll> &friends, vector<ll> &speeds)
{
    
}
void meeting_place_cannot_be_changed()
{
    ll n;
    cin >> n;
    vector<ll> speeds(n), friends(n);
    for (ll x = 0; x < n; x++)
        cin >> friends[x];
    for (ll x = 0; x < n; x++)
        cin >> speeds[x];
    long double start = 0;
    long double end = 1e9;
    while (abs(start - end) >= EPSILON)
    {
        long double mid = (start + (end - start) / 2);
        if (check_meeting_place(mid, friends, speeds))
        {
            end = mid;
        }
        else
        {
            start = mid;
        }
    }
    cout << fixed<<setprecision(12)<<(start + end) / 2 << "\n";
}

int maxValidSplits(vector<int> &nums)
{
    return 1;
}
int primeSubarray(vector<int> &nums, int k)
{
}
void solve()
{
    // s_queens();
    // range_xor_queries();
    // dynamic_range_minimum_queries();
    // cses_sliding_window_sum();
    // impartial_gift();
    // [1,3,6] ---> [0,1,0,0] -----> [1,2,3]
    // [1,2,3] ---> [1,0,1] -----> []
    // P[r]-P[l-1] = k
    // P[r] = k+P[l-1] selecting r and checking
    // P[l-1] = P[r]-k
    // [1,1,1,2,2] = [1,0,0,1,0] and k = 0
    // P[l-1] = P[r] for a,b and c all .
}
int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    ll t;
    // cin >> t;
    t = 1;
    while (t--)
    {
        solve();
    }
}

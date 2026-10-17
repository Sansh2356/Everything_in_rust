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
const int MOD = 1e9 + 7;
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
// VVIMP a variation of monotonic deque in case of negitive numbers over prefix array .
int shortestSubarray(vector<int> &nums, int k)
{
    /*
        prefix[r]-prefix[l-1] >= k
        prefix[l-1] <= prefix[r]-k we can directly find total number of such
        subarrays .

        Find floor(root(x)) .

        Binary search on an infinite array .

        dijkstra,0-1 bfs,bellman-ford,flloyd-warshall .
    */
    return 1;
}
void bfs(vector<bool> &visited, unordered_map<int, vector<int>> &adj_list)
{
    queue<int> q;
    visited[0] = true;
    q.push(0);
    while (!q.empty())
    {
        int curr_node = q.front();
        q.pop();
        if (visited[curr_node])
            continue;
        cout << curr_node << " ";
        for (auto neighbor : adj_list[curr_node])
        {
            if (visited[neighbor])
            {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    cout << "\n";
}
void dfs(int curr_node, int color, unordered_map<int, vector<int>> &adj_list, vector<bool> &visited, vector<int> &node_color)
{
    if (visited[curr_node])
    {
        return;
    }
    visited[curr_node] = true;
    node_color[curr_node] = color;
    for (auto neighbor : adj_list[curr_node])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, color, adj_list, visited, node_color);
        }
    }
}

// vector<int> dx = {1, 1, -1, -1, 2, 2, -2, -2};
// vector<int> dy = {2, -2, 2, -2, 1, -1, 1, -1};
bool perimeter_check(int r, int c, vector<string> &grid)
{
    if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size())
    {
        return false;
    }
    return true;
}
class Solution
{
public:
    vector<int> rearrangeArray(vector<int> &nums)
    {
        vector<int> ans;
        map<int, int> m;
        for (auto i : nums)
            m[i]++;
        while (!m.empty())
        {
            bool flag = true;
            for (auto &it : m)
            {
                if (it.second > 0)
                {
                    ans.push_back(it.first);
                    it.second--;
                }
                else
                {
                    m.erase(it.first);
                }
            }
        }
        return ans;
    }
};

int resilientSubarray(vector<int> &nums, int k)
{
}

void solve()
{
    // kruskal();
    // remove_edges();
    // area_perimeter_components(grid_2);
    // infected_people();
    // save_yourself();
    // snake_ladders();
    // jump_game();
    // budget_travelling();
    // apsp();
    // flloyd_warshall();
    // ll n, m;
    // cin >> n >> m;
    // vector<vector<ll>> edges(m);
    // for (int x = 0; x < m; x++)
    // {
    //     ll u, v, c;
    //     cin >> u >> v >> c;
    //     edges[x] = {u, v, -c};
    // }
    // dist.assign(n + 1, LLONG_MAX);
    // bellman_ford(edges, n, 1);
    // vector<ll> temp_dist = dist;
    // bellman_ford(edges, n, 1);
    // vector<ll> cycle_nodes;
    // for (int x = 1; x <= n; x++)
    // {
    //     // Positive cycle exists .
    //     if (temp_dist[x] < dist[x])
    //     {
    //         cout << "CYCLE EXISTS \n";
    //         cycle_nodes.push_back(x);
    //     }
    // }

    // cout << -temp_dist[n] << "\n";

    // burn_all();
    // shortest_path_1();
    // kahn();
    // one_piece();
    // edge_reverse();
    // dijkstra();

    // ll n, k;
    // cin >> n >> k;
    // vector<vector<ll>> grid(n, vector<ll>(10, 0));

    // for (ll x = 0; x < n; x++)
    // {
    //     string s;
    //     cin >> s;
    //     for (int y = 0; y < s.length(); y++)
    //     {
    //         string sub = "";
    //         sub.push_back(s[y]);
    //         grid[x][y] = stoi(sub);
    //     }
    // }
    // while (1)
    // {
    //     bool flag = false;
    //     vector<vector<ll>> visited(n, vector<ll>(10, -1));
    //     for (int x = 0; x < n; x++)
    //     {
    //         for (int y = 0; y < 10; y++)
    //         {
    //             if (visited[x][y] == -1 && grid[x][y] != 0)
    //             {
    //                 component_size = 0;
    //                 vector<pair<int, int>> cells = vertical_grid(x, y, grid, visited);
    //                 if (component_size >= k)
    //                 {

    //                     flag = true;
    //                     for (auto i : cells)
    //                     {
    //                         grid[i.first][i.second] = 0;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     if (flag == false)
    //         break;
    //     for (int y = 0; y < grid[0].size(); y++)
    //     {
    //         int move = 0;
    //         for (int row = grid.size() - 1; row >= 0; row--)
    //         {
    //             if (grid[row][y] == 0)
    //             {
    //                 move++;
    //             }
    //             else if (grid[row][y] != 0 && move > 0)
    //             {
    //                 grid[row + move][y] = grid[row][y];
    //                 grid[row][y] = 0;
    //             }
    //         }
    //     }
    // }
    // for (int x = 0; x < grid.size(); x++)
    // {
    //     for (int y = 0; y < grid[0].size(); y++)
    //     {
    //         cout << grid[x][y];
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";

    // kahn();
    // finding_cycles();
    // check_cycle();

    // ll n, m;
    // cin >> n >> m;
    // vector<bool> visited(n + 1, false);
    // unordered_map<int, vector<int>> adj_list;
    // for (int x = 0; x < m; x++)
    // {
    //     int u, v;
    //     cin >> u >> v;
    //     adj_list[u].push_back(v);
    //     adj_list[v].push_back(u);
    // }
    // bfs(visited, adj_list);

    // ll n, m;
    // cin >> n >> m;
    // vector<ll> v(n);
    /*
        m*bm - sigma bi for all i from [1,m-1] .
        bm will be last term of subsequence taken
        so all other terms from [1,m-1] will be lesser in index range .
    */
    // generate_permutations_2();
    // solve_segmented_sieve_print();
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    // cin >> t;
    t = 1;
    while (t--)
    {
        solve();
    }
}
/*
    1) Non cyclic connected componenets .
    2) A unique simple path exists between any 2 nodes.
    3) Both dfs and bfs are valid itself .
    4) Finding diameter in a tree.
    5) Finding spsp between all pair of nodes.
    6) Center of a tree .
    7) Ancestral states based question + data structures.
    8) Rerooting .
    9) DSU .
*/
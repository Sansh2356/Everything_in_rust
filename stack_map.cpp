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

vector<int> dx = {1, 1, -1, -1, 2, 2, -2, -2};
vector<int> dy = {2, -2, 2, -2, 1, -1, 1, -1};
bool check_islands(int r, int c, vector<vector<int>> &grid)
{
    if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size())
    {
        return false;
    }
    return true;
}
void bfs(vector<vector<int>> &grid, vector<vector<int>> &visited, int row,
         int col)
{
    queue<pair<int, int>> q;
    q.push({row, col});
    visited[row][col] = 1;
    while (q.empty() != true)
    {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int x = 0; x < 4; x++)
        {
            int neig_r = r + dx[x];
            int neig_c = c + dy[x];
            if (check_islands(neig_r, neig_c, grid) == true &&
                visited[neig_r][neig_c] == -1)
            {
                q.push({neig_r, neig_c});
                visited[neig_r][neig_c] = 1;
            }
        }
    }
}
int KnightWalk(int N, int Sx, int Sy, int Fx, int Fy)
{
    vector<vector<int>> visited(N + 1, vector<int>(N + 1, -1));
    vector<vector<int>> grid(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> dist(N + 1, vector<int>(N + 1, 0));

    queue<pair<int, int>> q;
    q.push({Sx, Sy});
    visited[Sx][Sy] = 1;
    while (q.empty() != true)
    {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        if (r == Fx && c == Fy)
            return dist[r][c];
        for (int x = 0; x < dx.size(); x++)
        {
            int neig_r = r + dx[x];
            int neig_c = c + dy[x];
            if (check_islands(neig_r, neig_c, grid) == true &&
                visited[neig_r][neig_c] == -1)
            {
                q.push({neig_r, neig_c});
                dist[neig_r][neig_c] = dist[r][c] + 1;
                visited[neig_r][neig_c] = 1;
            }
        }
    }
    return -1;
}
bool check_random(int x, int y, int n, int m)
{
    if (x >= 0 && x < n && y >= 0 && y < m)
        return true;
    return false;
}
vector<pair<pair<int, int>, ll>> get_neighbors(int x, int y, vector<string> &grid)
{
    vector<pair<pair<int, int>, ll>> ans;
    for (int x = 0; x < 4; x++)
    {
        ll new_x = x + dx[x];
        ll new_y = y + dy[x];
        if (check_random(new_x, new_y, grid.size(), grid[0].size()))
        {
            if (grid[new_x][new_y] == '#')
            {

                ans.push_back({{new_x, new_y}, 1});
            }
            else
            {
                ans.push_back({{new_x, new_y}, 0});
            }
        }
    }
    return ans;
}
ll random_question_bfs(vector<string> &grid, ll start_x, ll start_y, ll end_x, ll end_y)
{
    vector<vector<ll>> dist(grid.size(), vector<ll>(grid[0].size(), LLONG_MAX));
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    deque<pair<int, int>> dq;
    dq.push_back({start_x, start_y});
    while (!dq.empty())
    {
        ll curr_node_x = dq.front().first;
        ll curr_node_y = dq.front().second;
        dq.pop_front();

        if (visited[curr_node_x][curr_node_y])
            continue;
        visited[curr_node_x][curr_node_y] = true;

        for (auto i : get_neighbors(curr_node_x, curr_node_y, grid))
        {
            if (!visited[i.first.first][i.first.second] && dist[i.first.first][i.first.second] > dist[curr_node_x][curr_node_y] + i.second)
            {
                visited[i.first.first][i.first.second] = true;
                dist[i.first.first][i.first.second] = dist[curr_node_x][curr_node_y] + i.second;
                if (i.second == 0)
                {
                    dq.push_back({i.first.first, i.first.second});
                }
                else
                {

                    dq.push_front({i.first.first, i.first.second});
                }
            }
        }
    }

    return dist[end_x][end_y];
}
void random_question()
{
    ll n, m;
    cin >> n >> m;
    vector<string> grid;
    for (ll x = 0; x < m; x++)
    {
        string s;
        cin >> s;
        grid.push_back(s);
    }
    ll start_x, start_y, end_x, end_y;
    cin >> start_x >> start_y >> end_x >> end_y;
    random_question_bfs(grid, start_x, start_y, end_x, end_y);
}
bool cycle = false;
void dfs_check_cycle(int curr_node, vector<int> &parents, vector<bool> &visited, unordered_map<int, vector<int>> &adj_list)
{
    visited[curr_node] = true;
    for (auto neig : adj_list[curr_node])
    {
        if (visited[neig] == false)
        {
            parents[neig] = curr_node;
            dfs_check_cycle(neig, parents, visited, adj_list);
        }
        else if (neig != parents[curr_node])
        {
            cycle = true;
            return;
        }
    }
}
void check_cycle()
{
    ll n, m;
    cin >> n >> m;
    vector<int> parents(n + 1, -1);
    vector<bool> visited(n + 1);
    unordered_map<int, vector<int>> adj_list;
    for (int x = 0; x < m; x++)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    for (int x = 1; x <= n; x++)
    {
        if (visited[x] == false)
        {
            dfs_check_cycle(x, parents, visited, adj_list);
            if (cycle)
            {
                cout << "YES \n";
                return;
            }
        }
    }
    cout << "NO \n";
}
bool is_cycle_present = false;
vector<int> any_cycle;
void finding_cycles_dfs(int node, int parent, vector<int> &parents, vector<int> &color, unordered_map<int, vector<int>> &adj_list, vector<bool> &visited)
{

    color[node] = 2;
    parents[node] = parent;
    for (auto neig : adj_list[node])
    {
        // if (neig == parents[node])
        //     continue;
        if (color[neig] == 1)
        {
            // Forward edge .
            finding_cycles_dfs(neig, node, parents, color, adj_list, visited);
        }
        else if (color[neig] == 2)
        {
            // Back edge .
            if (is_cycle_present == false)
            {
                int temp = node;
                while (temp != neig)
                {
                    any_cycle.push_back(temp);
                    temp = parents[temp];
                }

                any_cycle.push_back(neig);
                any_cycle.push_back(node);
                reverse(any_cycle.begin(), any_cycle.end());
            }
            is_cycle_present = true;
        }
        else if (color[neig] == 3)
        {
            // Cross edge .
        }
    }
    color[node] = 3;
}
void finding_cycles()
{
    ll n, m;
    cin >> n >> m;
    vector<int> parents(n + 1);
    vector<int> color(n + 1, 1);
    vector<bool> visited(n + 1, 0);
    unordered_map<int, vector<int>> adj_list;
    for (int x = 0; x < m; x++)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    for (int x = 1; x <= n; x++)
    {
        if (color[x] == 1)
        {
            finding_cycles_dfs(x, 0, parents, color, adj_list, visited);
            if (is_cycle_present)
            {
                cout << "YES" << "\n";
                return;
            }
        }
    }
    cout << "NO \n";
}
void kahn()
{
    ll n, m;
    cin >> n >> m;
    unordered_map<int, vector<int>> adj_list;
    vector<int> indegree(n + 1, 0);
    for (int x = 0; x < m; x++)
    {
        int u, v;
        cin >> u >> v;
        indegree[v]++;
        adj_list[u].push_back(v);
    }
    queue<int> q;
    for (int x = 1; x <= n; x++)
    {
        if (indegree[x] == 0)
        {
            q.push(x);
        }
    }
    vector<int> topo_order;
    while (!q.empty())
    {
        int curr_node = q.front();
        q.pop();
        topo_order.push_back(curr_node);
        for (auto nei : adj_list[curr_node])
        {
            indegree[nei]--;
            if (indegree[nei] == 0)
            {
                q.push(nei);
            }
        }
    }
    if (topo_order.size() != n)
    {
        cout << "IMPOSSIBLE" << "\n";
    }
    else
    {
        for (auto i : topo_order)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
}
ll component_size = 0;
bool small_check(int row, int col, int n)
{
    if (row < 0 || col < 0 || row >= n || col >= 10)
    {
        return false;
    }
    return true;
}
vector<pair<ll, ll>> vertical_grid(ll start_row, ll start_col, vector<vector<ll>> &grid, vector<vector<ll>> &visited)
{
    vector<pair<ll, ll>> cells;
    queue<pair<pair<ll, ll>, ll>> q;
    visited[start_row][start_col] = 1;
    q.push({{start_row, start_col}, grid[start_row][start_col]});
    while (!q.empty())
    {
        ll row = q.front().first.first;
        ll col = q.front().first.second;
        ll color = q.front().second;
        q.pop();
        component_size++;
        cells.push_back({row, col});
        vector<ll> dx = {1, -1, 0, 0};
        vector<ll> dy = {0, 0, 1, -1};
        for (ll x = 0; x < 4; x++)
        {
            ll nei_row = row + dx[x];
            ll nei_col = col + dy[x];
            if (small_check(nei_row, nei_col, grid.size()) && visited[nei_row][nei_col] == -1 && grid[nei_row][nei_col] == color)
            {
                visited[nei_row][nei_col] = 1;
                q.push({{nei_row, nei_col}, color});
            }
        }
    }
    return cells;
}
void zero_one_bfs()
{
    ll n, m;
    cin >> n >> m;
    unordered_map<int, vector<pair<int, int>>> adj_list;
    for (int x = 0; x < m; x++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        adj_list[u].push_back({v, c});
        adj_list[v].push_back({u, c});
    }
    vector<bool> visited(n + 1, false);
    vector<int> dist(n + 1, INT_MAX);
    visited[1] = true;
    deque<pair<int, int>> dq;
    dq.push_front({1, 0});
    dist[1] = 0;
    while (!dq.empty())
    {
        int curr_node = dq.front().first;
        int cost = dq.front().second;
        dq.pop_front();
        for (auto &[nei, nei_cost] : adj_list[curr_node])
        {
            if (!visited[nei] && dist[nei] > dist[curr_node] + nei_cost)
            {
                if (nei_cost == 0)
                {
                    dq.push_front({nei, nei_cost});
                }
                else
                {
                    dq.push_back({nei, nei_cost});
                }
                dist[nei] = dist[curr_node] + nei_cost;
            }
        }
    }
}
bool check_one_piece(int row, int col, int n, int m)
{
    if (row < 0 || col < 0 || col >= m || row >= n)
    {
        return false;
    }
    return true;
}
void one_piece()
{
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> grid(n, vector<ll>(m, 0));
    vector<vector<ll>> dist(n, vector<ll>(m, LLONG_MAX));
    for (ll x = 0; x < n; x++)
    {
        for (ll y = 0; y < m; y++)
        {
            ll num;
            cin >> num;
            grid[x][y] = num;
        }
    }
    deque<pair<int, int>> dq;
    dist[0][0] = 0;
    dq.push_front({0, 0});
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};

    while (!dq.empty())
    {
        int curr_node_row = dq.front().first;
        int curr_node_col = dq.front().second;
        int symbol = grid[curr_node_row][curr_node_col];
        dq.pop_front();
        for (int x = 0; x < dx.size(); x++)
        {
            int w = 1;
            int r1 = curr_node_row + dx[x];
            int c1 = curr_node_col + dy[x];
        }
    }
    cout << (dist[n - 1][m - 1] == LLONG_MAX ? -1 : dist[n - 1][m - 1]) << "\n";
}
void burn_all()
{
    long long n, m;
    cin >> n >> m;
    vector<long long> dist(n + 1, LLONG_MAX);
    vector<bool> visited(n + 1, false);
    unordered_map<long long, vector<pair<long long, long long>>> adj_list;
    for (int x = 0; x < m; x++)
    {
        long long u, v, d;
        cin >> u >> v >> d;
        adj_list[u].push_back({v, d});
        adj_list[v].push_back({u, d});
    }
    long long start_node;
    cin >> start_node;
    priority_queue<pair<long long, long long>> pq;
    pq.push({0, start_node});
    dist[start_node] = 0;
    while (!pq.empty())
    {
        long long cost = -1 * pq.top().first;
        long long node = pq.top().second;
        pq.pop();
        if (visited[node])
            continue;
        visited[node] = true;
        for (auto i : adj_list[node])
        {
            if (!visited[i.first] && dist[i.first] > (dist[node] + i.second))
            {
                dist[i.first] = dist[node] + i.second;
                pq.push({-1 * dist[i.first], i.first});
            }
        }
    }
    long double ans = 0.0;
    for (auto it : adj_list)
    {
        long long u = it.first;
        for (auto nei : it.second)
        {
            long double t1 = dist[u];
            long double t2 = dist[nei.first];
            if (abs(t1 - t2) >= nei.second)
            {
                // One of them will already burn it before other end
                // catches fire .
                ans = max(ans, (min(t1, t2) + nei.second));
            }
            else
            {
                // Both ends will meet somewhere in between
                // the thread at an instance `t` . (x-t1) + (x-t2) = X
                // 2x = X+t1+t2 x = (X+t1+t2)/2 .
                ans = max(ans, ((t1 + t2 + nei.second) / 2));
            }
        }
    }
    cout << (10 * ans) << "\n";
}
vector<ll> dist;
void bellman_ford(vector<vector<ll>> &edges, int n, int start_node)
{
    /*
    As we have discussed earlier that, we need (V - 1) relaxations of all the edges to achieve single source shortest path. If one additional relaxation (Vth) for any edge is possible, it indicates that some edges with overall negative weight has been traversed once more. This indicates the presence of a negative weight cycle in the graph.
    */
    dist[start_node] = 0;
    for (int x = 1; x <= n; x++)
    {
        for (auto i : edges)
        {
            int u = i[0];
            int v = i[1];
            int c = i[2];
            if (dist[v] > dist[u] + c)
            {
                dist[v] = (dist[u] + c);
            }
        }
    }
    for (auto i : dist)
    {
        cout << i << " ";
    }
    cout << "\n";
}
void snake_ladders()
{
}
class Solution
{
public:
    vector<int> rearrangeArray(vector<int> &nums)
    {
        vector<int> ans;

        return ans;
    }
};
void solve()
{
    /*
        1)Skewer.
        2)Casteling.
        3)Forking.
    */
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

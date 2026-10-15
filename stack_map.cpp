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
vector<int> distance_list;
vector<int> parent_list;

// No need of visited since in tree there will never be a backedge.
void tree_dfs(int curr_node, int parent_node, unordered_map<int, vector<int>> &adj_list, int dist)
{
    // updating the new distance to the child node by the previously added
    // distance of 1 unit by parent node .
    cout << curr_node << " " << parent_node << " " << dist << "\n";
    distance_list[curr_node] = dist;
    for (auto nei : adj_list[curr_node])
    {
        if (nei != parent_node)
        {
            // being a tree it will always be reachable from
            // parent by extending distance by unit 1 due to which both dfs and bfs produces the single unique simple path that can exist
            // between a pair of nodes .
            parent_list[nei] = curr_node;
            tree_dfs(nei, curr_node, adj_list, dist + 1);
        }
    }
}
const int n = 1e6;
vector<int> prime_numbers;
bool flag = false;
void sieve()
{
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i] && (long long)i * i <= n)
        {
            for (int j = i * i; j <= n; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
    for (int x = 2; x < is_prime.size(); x++)
    {
        if (is_prime[x] == true)
        {
            prime_numbers.push_back(x);
        }
    }
}
vector<int> maxPrimes(int n, int s)
{
    if (flag == false)
    {
        sieve();
        flag = true;
    }
    long long sum = 0;
    vector<int> ans;
    for (int x = 0; x < prime_numbers.size(); x++)
    {
        if (prime_numbers[x] > n)
            break;
        if ((sum + prime_numbers[x]) <= s)
        {
            sum += prime_numbers[x];
            ans.push_back(prime_numbers[x]);
        }
        else
        {
            return ans;
        }
    }
    return ans;
}
void tree_based_question()
{
    int n;
    cin >> n;
    distance_list.resize(n + 1, 0);
    parent_list.resize(n + 1, 0);
    unordered_map<int, vector<int>> adj_list;
    for (int x = 1; x <= n - 1; x++)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    tree_dfs(1, 0, adj_list, 0);
    for (int x = 2; x <= n; x++)
    {
        cout << "Shortest possible distance existing between 1 and " << x << " is " << distance_list[x] << "\n";
    }

    // Finding the longest possible shortest path will give us the diameter of a tree .
    // either we can go around on each vertice and apply dfs and then iterate over distance and update
    // the maximum value or we can also use double dfs approach by applying that x ----> y and then y ----> z
    // this will maximize the distance between any 2 nodes in a tree and thus the diameter .
    int maxi_dist_node = 0;
    int maxi_dist = 0;
    for (int x = 1; x < distance_list.size(); x++)
    {
        if (distance_list[x] > maxi_dist)
        {
            maxi_dist = distance_list[x];
            maxi_dist_node = x;
        }
    }
    tree_dfs(maxi_dist_node, 0, adj_list, 0);
    int diameter = 0;
    for (int x = 1; x < distance_list.size(); x++)
    {
        if (distance_list[x] > diameter)
            diameter = distance_list[x];
    }
    cout << "Diameter for the given tree is - " << diameter << "\n";

    // Finding center of tree that will be atmost 2 in case of odd length
    // and in case of even length of diameter will be a single center that can be found out
    // by iterating by middle point node .
    for (int x = 1; x < parent_list.size(); x++)
    {
        cout << parent_list[x];
    }
    cout << "\n";
    cout << maxi_dist_node << "\n";
    int center_node = 0;
    if (diameter % 2)
    {
        for (int x = 0; x < diameter / 2; x++)
        {
            center_node = parent_list[maxi_dist_node];
            maxi_dist_node = center_node;
        }
        cout << center_node << parent_list[center_node] << "\n";
        int c1 = center_node;
        int c2 = parent_list[center_node];
        distance_list.assign(n + 1, 0);
        tree_dfs(c1, c2, adj_list, 0);
        for (int x = 1; x <= n; x++)
        {
            if (distance_list[x] == diameter / 2)
            {
                cout << distance_list[x] << " " << x << " ";
            }
        }
        cout << " ------------------------------------ \n";
        distance_list.assign(n + 1, 0);
        tree_dfs(c2, c1, adj_list, 0);
        for (int x = 1; x <= n; x++)
        {
            if (distance_list[x] == diameter / 2)
            {
                cout << distance_list[x] << " " << x << " ";
            }
        }
        cout << " ------------------------------------ \n";
    }
    else
    {
        for (int x = 0; x < diameter / 2; x++)
        {
            center_node = parent_list[maxi_dist_node];
            maxi_dist_node = center_node;
        }
        cout << center_node << '\n';
        for (auto child : adj_list[center_node])
        {
            distance_list.assign(n + 1, 0);
            tree_dfs(child, center_node, adj_list, 0);
            for (int x = 1; x <= n; x++)
            {
                if (distance_list[x] == diameter / 2)
                {
                    cout << distance_list[x] << " " << x << " ";
                }
            }
            cout << " ------------------------------------ \n";
        }
    }
}
class BusBooking
{
public:
    /*
        Size of (n*4) seat matrix where n are rows and 4 are seats A,B,C,D
        in each row.
        Booking a middle seat ("B" or "C") always takes 1 second.
        Booking a window seat ("A" or "D") takes 1 second if its adjacent middle
       seat is not booked, or 3 seconds (an extra delay of 2 seconds) if its
       adjacent middle seat is already booked.
    */
    vector<vector<int>> grid;
    vector<vector<int>> costs;
    map<char, int> m;
    multiset<pair<int, int>> window_seats;
    multiset<pair<int, int>> middle_seats;
    int cost_till_now;

    BusBooking(int n)
    {
        // cout << "BusBooking: rows = " << n << "\n";
        cost_till_now = 0;
        grid.resize(n, vector<int>(4, -1));
        costs.resize(n, vector<int>(4, 0));
        m['A'] = 0;
        m['B'] = 1;
        m['C'] = 2;
        m['D'] = 3;
        // cout << "Initial total time = " << cost_till_now << "\n";
    }
    void toggle(string seat)
    {
        // cout << "toggle: seat = " << seat << "\n";
        int seat_idx = this->m[seat[0]];
        int row_num = stoi(seat.substr(1, seat.size())) - 1;
        // cout << "Row index = " << row_num << ", seat index = " << seat_idx
        //      << "\n";
        // Not booked then we will add the cost of booking .
        if (grid[row_num][seat_idx] == -1)
        {
            // cout << "Booking seat " << seat << "\n";
            grid[row_num][seat_idx] = 1;

            if (seat_idx == 0 || seat_idx == 3)
            {
                // Window seat .
                window_seats.insert({row_num, seat_idx});
                if (seat_idx == 0)
                {
                    if (grid[row_num][1] == 1)
                    {
                        cost_till_now += 3;
                        costs[row_num][seat_idx] = 3;
                        // cout
                        // << "Adjacent middle seat booked: added 3 seconds\n";
                    }
                    else
                    {
                        cost_till_now++;
                        costs[row_num][seat_idx] = 1;
                        // cout << "Adjacent middle seat free: added 1 second\n";
                    }
                }
                else
                {
                    if (grid[row_num][2] == 1)
                    {
                        cost_till_now += 3;
                        costs[row_num][seat_idx] = 3;
                        // cout
                        // << "Adjacent middle seat booked: added 3 seconds\n";
                    }
                    else
                    {
                        cost_till_now++;
                        costs[row_num][seat_idx] = 1;
                        // cout << "Adjacent middle seat free: added 1 second\n";
                    }
                }
            }
            else
            {
                middle_seats.insert({row_num, seat_idx});
                costs[row_num][seat_idx] = 1;
                cost_till_now++;
                // cout << "Middle seat: added 1 second\n";
            }
        }
        // Already booked then we will make it free and no cost is added.
        else if (grid[row_num][seat_idx] == 1)
        {
            // cout << "Freeing seat " << seat << ": added 0 seconds\n";
            grid[row_num][seat_idx] = -1;
            if (seat_idx == 0 || seat_idx == 3)
            {
                // Window seat unallocation.
                window_seats.erase(window_seats.find({row_num, seat_idx}));
                cost_till_now -= costs[row_num][seat_idx];
            }
            else
            {
                // Middle seat unallocation .
                middle_seats.erase(middle_seats.find({row_num, seat_idx}));
                cost_till_now -= costs[row_num][seat_idx];
            }
            costs[row_num][seat_idx] = 0;
        }
        // cout << "Total time = " << cost_till_now << "\n";
        // cout << "Booked window seats = " << window_seats.size()
        //      << ", booked middle seats = " << middle_seats.size() << "\n";
    }

    int getTotalTime()
    {
        // cout << "getTotalTime: " << cost_till_now << "\n";
        return cost_till_now;
    }
    // Booking the window seat before any middle seat of each row that will
    // allow us to get minimum cost.
    int getMinTime()
    {
        // cout << "getMinTime: "
        //      << (int)window_seats.size() + (int)middle_seats.size() << "\n";
        return (int)window_seats.size() + (int)middle_seats.size();
    }
};
int resilientSubarray(vector<int> &nums, int k)
{
}
// Constructing the binary lifting data structure being used to
// compute the ancestore afterwards stored upto logn powers for each node.
vector<vector<int>> ancestors;
vector<int> parent_nodes;
vector<int> distances;
void dfs_binary_lifting(int node, int parent_node, int dist, unordered_map<int, vector<int>> &adj_list)
{
    parent_nodes[node] = parent_node;
    distances[node] = dist;
    ancestors[node][0] = parent_node;
    // Upto 2^19 .
    for (int x = 1; x <= 19; x++)
    {
        // Splitting 2^jth ancestor  = 2^j-1th and then that ancestors 2^jth ancestor .
        ancestors[node][x] = ancestors[ancestors[node][x - 1]][x - 1];
    }
    for (auto nei : adj_list[node])
    {
        if (nei != parent_node)
        {
            dfs_binary_lifting(nei, node, dist + 1, adj_list);
        }
    }
}
/*
    1) Bringing all the nodes onto the same level/depth.
    2) Then apply the jth binary lifting .
    3) Finding lca and then finding combined query across simple paths
        such as finding minima,maxima,gcd etc  coming under the category of path aggregates.
    4) Prefix sum on trees.
    5) Partial sums on trees .
    6) More ideas on binary lifting .
*/
int binary_lifting_lca()
{
    // Finding kth instance of a previously precomputed values by
    // splitting it in powers of such that the jth power can be computed
    // by (j-1)th and (j-1)th power respectively .
    int n;
    cin >> n;
    unordered_map<int, vector<int>> adj_list;
    for (int x = 1; x <= n - 1; x++)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    // Finding LCA the trivial method to find is
    // to trace path to root node from each pair of (u,v) and
    // iterating longest suffix array for each ancestors path will give use the answer .
    // but here we will use the binaray lifting on ancestor by firstly
    // getting both at same level and then iterating in powers of 2 until the node becomes none .
    dfs_binary_lifting(1, 0, 0, adj_list);
    // Pair between lca has to be found .
    int u, v;
    cin >> u >> v;
    // We consider that uth node is at a lower depth or higher level and v is at greater depth but
    // lower level .
    if (distances[v] > distances[u])
    {
        swap(u, v);
    }
    // Bringing both the nodes to same level .
    int k = distances[v] - distances[u];
    for (int x = 19; x >= 1; x--)
    {
        // Taking each set bit and moving the lower node by 2^jth ancestor .
        // checking if set bit .
        if (k & (1 << x))
        {
            u = ancestors[u][x];
        }
    }
    for (int x = 19; x >= 1; x--)
    {
        if (u != v)
        {
            u = ancestors[u][x];
            v = ancestors[v][x];
        }
    }
    return ancestors[u][0];
}

int gcd(int a, int b)
{
    if (a == 1)
        return 1;
    return gcd(b % a, a);
}
vector<vector<int>> ancestors_gcd;
vector<vector<int>> ancestors;

void dfs_gcd_binary_lifting(int node, int parent_node, int dist, unordered_map<int, vector<int>> &adj_list)
{
    parent_nodes[node] = parent_node;
    distances[node] = dist;
    ancestors_gcd[node][0] = node;
    ancestors[node][0] = parent_node;
    // Upto 2^19 .
    for (int x = 1; x <= 19; x++)
    {
        // Splitting 2^jth ancestor  = 2^j-1th and then that ancestors_gcd 2^jth ancestor .
        ancestors[node][x] = ancestors[ancestors[node][x - 1]][x - 1];
        ancestors_gcd[node][x] = gcd(ancestors_gcd[ancestors[node][x - 1]][x - 1], ancestors_gcd[node][x - 1]);
    }
    for (auto nei : adj_list[node])
    {
        if (nei != parent_node)
        {
            dfs_binary_lifting(nei, node, dist + 1, adj_list);
        }
    }
}
int finding_gcd_tree_simple_path()
{
    int n;
    cin >> n;
    unordered_map<int, vector<int>> adj_list;
    for (int x = 1; x <= n - 1; x++)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    dfs_binary_lifting(1, 0, 0, adj_list);
    // Pair between lca has to be found .
    int u, v;
    cin >> u >> v;
    // We consider that uth node is at a lower depth or higher level and v is at greater depth but
    // lower level .
    if (distances[v] > distances[u])
    {
        swap(u, v);
    }
    // Bringing both the nodes to same level .
    int k = distances[v] - distances[u];
    int ans = 0;
    for (int x = 19; x >= 1; x--)
    {
        // Taking each set bit and moving the lower node by 2^jth ancestor .
        // checking if set bit .
        if (k & (1 << x))
        {
            u = ancestors[u][x];
            ans = ancestors_gcd[u][x];
        }
    }
    if (u == v)
    {
        return ans;
    }
    for (int x = 19; x >= 1; x--)
    {
        if (u != v)
        {
            ans = gcd(ans, ancestors_gcd[u][x]);
            ans = gcd(ans, ancestors_gcd[v][x]);
            u = ancestors[u][x];
            v = ancestors[v][x];
        }
    }
    ans = gcd(u, ans);
    ans = gcd(v, ans);
    ans = gcd(parent_nodes[u], ans);
    return ans;
}
void solve()
{
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
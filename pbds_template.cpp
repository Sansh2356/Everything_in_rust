#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef long long ll;
// and pairs are compared lexicographically:
#define ordered_set tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update>

using namespace std;
long long distantSubarrays(vector<int> &nums, int goal, int k)
{
    /*
        abs(prefix[r]-prefix[l-1]-goal) >= k
        // Opening with - and then multiplying both sides with -1 and reversing
        // inequality sign .
        (prefix[r]-prefix[l-1]-goal) <= -k
        // All prefixes which are greater than  (current_prefix+k-goal) are valid .
        prefix[r]+k-goal<= prefix[l-1]
        // Opening with +
        prefix[r]-prefix[l-1]-goal >= k
        // All prefixes which are less than (current_prefix-goal-k) are valid .
        prefix[r]-goal-k >= prefix[l-1]
    */

    ordered_set st;
    ll idx = -1;
    st.insert({0, idx});
    vector<long long> prefix_arr(nums.size());
    prefix_arr[0] = nums[0];
    for (int x = 1; x < nums.size(); x++)
    {
        prefix_arr[x] = prefix_arr[x - 1] + nums[x];
    }
    long long ans = 0;
    for (int x = 0; x < prefix_arr.size(); x++)
    {
        // All prefixes which are less than (current_prefix-goal-k) are valid .
        idx++;
        long long cnt_1 = st.order_of_key({prefix_arr[x] - goal - k, idx});
        // All prefixes which are greater than  (current_prefix+k-goal) are valid .
        idx++;
        long long cnt_2 = (st.size() - st.order_of_key({prefix_arr[x] - goal + k, idx}));
        ans += (cnt_1 + cnt_2);
        idx++;
        st.insert({prefix_arr[x], idx});
    }
    return ans;
}
void solve()
{
    // long long q;
    // cin >> q;
    // ordered_set st;
    // while (q--)
    // {
    //     string s;
    //     cin >> s;
    //     if (s == "add")
    //     {
    //         long long x;
    //         cin >> x;
    //         st.insert(x);
    //     }
    //     else if (s == "remove")
    //     {
    //         long long x;
    //         cin >> x;
    //         if (st.find(x) != st.end())
    //         {
    //             st.erase(x);
    //         }
    //     }
    //     else if (s == "find")
    //     {
    //         long long x;
    //         cin >> x;
    //         auto val = st.find_by_order(x);
    //         if (val != st.end())
    //         {
    //             cout << *val << "\n";
    //         }
    //         else
    //         {
    //             cout << -1 << "\n";
    //         }
    //     }
    //     else if (s == "findpos")
    //     {
    //         long long x;
    //         cin >> x;
    //         cout << st.order_of_key(x) << "\n";
    //     }
    // }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long t;
    cin >> t;
    // t = 1;
    while (t--)
    {
        solve();
    }
}

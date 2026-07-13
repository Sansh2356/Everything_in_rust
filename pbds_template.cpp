#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

using namespace std;
void solve()
{
    long long q;
    cin >> q;
    ordered_set st;
    while (q--)
    {
        string s;
        cin >> s;
        if (s == "add")
        {
            long long x;
            cin >> x;
            st.insert(x);
        }
        else if (s == "remove")
        {
            long long x;
            cin >> x;
            if (st.find(x) != st.end())
            {
                st.erase(x);
            }
        }
        else if (s == "find")
        {
            long long x;
            cin >> x;
            auto val = st.find_by_order(x);
            if (val != st.end())
            {
                cout << *val << "\n";
            }
            else
            {
                cout << -1 << "\n";
            }
        }
        else if (s == "findpos")
        {
            long long x;
            cin >> x;
            cout << st.order_of_key(x) << "\n";
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}

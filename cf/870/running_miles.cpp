#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct block {
    int max_end;
    int max_mid;
};

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<block> st;
    st.push_back({nums[n - 1] - (n - 1), nums[n - 2]});
    set<int> rest;

    auto merge_iter = [&]() {
        while (st.size() >= 2) {
            int sz = st.size();
            if (st[sz - 1].max_mid >= st[sz - 2].max_mid) {
                st[sz - 2].max_end = max(st[sz - 1].max_end, st[sz - 2].max_end);
                st[sz - 2].max_mid = max(st[sz - 1].max_mid, st[sz - 2].max_mid);
                rest.insert(st[sz - 2].max_mid + st[sz - 2].max_end);
                st.pop_back();
            } else {
                break;
            }
        }
    };

    int cur_best_end = -INF;
    int ans = -INF;
    for (int l = n - 3; l >= 0; l--) {
        cur_best_end = max(cur_best_end, nums[l + 2] - (l + 2));
        st.push_back({cur_best_end, nums[l + 1]});
        rest.insert(cur_best_end + nums[l + 1]);
        merge_iter();

        ans = max(ans, nums[l] + l + *rest.rbegin());
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

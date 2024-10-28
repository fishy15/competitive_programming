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

void solve() {
    int n, l, r;
    cin >> n >> l >> r;

    vector<ll> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    vector<ll> psum(n+1);
    for (int i = 0; i < n; i++) {
        psum[i+1] = psum[i] + nums[i];
    }

    multiset<int, greater<>> cur_trans = {0};
    vector<vector<int>> start_at(n+2);
    vector<vector<int>> end_at(n+2);

    vector<int> ans(n + 1);
    for (int i = 0; i <= n; i++) {
        for (auto x : start_at[i]) {
            cur_trans.insert(x);
        }
        
        for (auto x : end_at[i]) {
            cur_trans.erase(cur_trans.find(x));
        }

        // either we take an interval or just previous
        ans[i] = *cur_trans.begin();
        cur_trans.insert(ans[i]);

        auto start_idx = lower_bound(psum.begin(), psum.end(), psum[i]+l) - psum.begin();
        auto end_idx = upper_bound(psum.begin(), psum.end(), psum[i]+r) - psum.begin();
        start_at[start_idx].push_back(ans[i] + 1);
        end_at[end_idx].push_back(ans[i] + 1);
    }

    cout << ans.back() << '\n';
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

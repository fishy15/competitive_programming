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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<ll> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    // height, len
    vector<pair<ll, int>> st;
    rep(i, 0, n) {
        auto x = nums[i];
        int len = 1;
        ll extra = 0;
        while (!st.empty() && st.back().first > x) {
            auto [old_x, old_len] = st.back();
            st.pop_back();

            auto tot_elems = old_x * old_len + x * len + extra;
            auto new_len = old_len + len;

            extra = tot_elems % new_len;
            x = tot_elems / new_len;
            len = new_len;
        }

        if (extra > 0) {
            st.push_back({x, len - extra});
            st.push_back({x + 1, extra});
        } else {
            st.push_back({x, len});
        }
    }

    auto mini = st[0].first;
    auto maxi = st.back().first;
    cout << maxi - mini << '\n';
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

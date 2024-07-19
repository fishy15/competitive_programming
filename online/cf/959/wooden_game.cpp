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

int msb(int x) {
    for (int i = 30; i >= 0; i--) {
        if ((x & (1 << i))) {
            return i;
        }
    }
    return -1;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
        rep(j, 0, nums[i]-1) {
            int trash;
            cin >> trash;
        }
    }

    array<vector<int>, 31> by_msb;
    for (auto x : nums) {
        by_msb[msb(x)].push_back(x);
    }

    int ans = 0;
    for (int i = 30; i >= 0; i--) {
        for (auto x : by_msb[i]) {
            if (ans & (1 << i)) {
                // if msb is already set, then go lower
                ans |= (1 << i) - 1;
            } else {
                // else shift problem down for later
                ans |= 1 << i;
                auto nxt_x = x ^ (1 << i);
                auto nxt_msb = msb(nxt_x);
                if (nxt_msb >= 0) {
                    by_msb[nxt_msb].push_back(nxt_x);
                }
            }
        }
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

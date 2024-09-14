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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    // a value can be a median if there exist at least n/2+1 values geq it
    auto check = [&](int med) {
        vector<array<int, 2>> dp(n + 1, array<int, 2>{INF, INF});
        dp[0][0] = 0;
        rep(i, 0, n) {
            // cost of no skip
            ckmin(dp[i + 1][1], dp[i][0] + (nums[i] < med ? 1 : 0));
            ckmin(dp[i + 1][1], dp[i][1] + (nums[i] < med ? 1 : 0));

            // cost of skip
            if (i+1 >= k) {
                ckmin(dp[i + 1][0], dp[i + 1 - k][0]);
                ckmin(dp[i + 1][1], dp[i + 1 - k][1]);
            }
        }

        auto leftover = n % k;
        if (leftover == 0) {
            leftover = k;
        }

        auto geq = leftover - dp[n][1];
        return geq >= leftover / 2 + 1;
    };

    auto l = *min_element(all(nums));
    auto r = *max_element(all(nums));
    int ans = -1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1; 
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

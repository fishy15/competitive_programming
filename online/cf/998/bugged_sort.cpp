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

array<int, 2> flip(const array<int, 2> &x) {
    return array{x[1], x[0]};
}

bool fits(const array<int, 2> &a, const array<int, 2> &b) {
    return a[0] < b[0] && a[1] < b[1];
}

void solve() {
    int n;
    cin >> n;

    vector<array<int, 2>> nums(n);
    rep(i, 0, n) {
        cin >> nums[i][0];
    }
    rep(i, 0, n) {
        cin >> nums[i][1];
    }

    sort(all(nums), [](const auto &a, const auto &b) {
        return min(a[0], a[1]) < min(b[0], b[1]);
    });

    // dp[using i+1][even/odd][not flipped/flipped]
    vector dp(n, array<array<bool, 2>, 2>{});
    dp[0][0][0] = true;
    dp[0][1][1] = true;
    rep(i, 1, n) {
        if (fits(nums[i-1], nums[i])) {
            dp[i][0][0] |= dp[i-1][0][0];
            dp[i][1][0] |= dp[i-1][1][0];
        }
        if (fits(flip(nums[i-1]), nums[i])) {
            dp[i][0][0] |= dp[i-1][0][1];
            dp[i][1][0] |= dp[i-1][1][1];
        }
        if (fits(nums[i-1], flip(nums[i]))) {
            dp[i][0][1] |= dp[i-1][1][0];
            dp[i][1][1] |= dp[i-1][0][0];
        }
        if (fits(flip(nums[i-1]), flip(nums[i]))) {
            dp[i][0][1] |= dp[i-1][1][1];
            dp[i][1][1] |= dp[i-1][0][1];
        }
    }

    auto ans = dp[n-1][0][0] || dp[n-1][0][1];
    if (ans) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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

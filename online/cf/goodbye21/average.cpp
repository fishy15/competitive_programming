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
    ll n; cin >> n;
    vector<ll> nums(n);

    // 0 = not picked
    // 1 = big, picked none
    // 2 = big, picked left
    // 3 = big, picked right
    // 4 = big, picked both
    // 5 = small, picked
    vector<array<ll, 6>> dp(n);

    for (ll i = 0; i < n; i++) {
        cin >> nums[i];
        dp[i].fill(0);
    }

    ll x; cin >> x;
    for (ll i = 0; i < n; i++) {
        // case 0
        if (i > 0) {
            dp[i][0] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2], dp[i - 1][5]});
        }

        // case 1
        if (nums[i] >= x) {
            if (i > 0) dp[i][1] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
            dp[i][1] += 1;
        }

        // case 2
        if (i > 0 && nums[i] >= x && nums[i - 1] < x && (nums[i] + nums[i - 1]) >= 2 * x) {
            if (i > 2) dp[i][2] = max({dp[i - 2][0], dp[i - 2][3], dp[i - 2][4]});
            dp[i][2] += 2;
        }

        // case 3
        if (i < n - 1 && nums[i] >= x && nums[i + 1] < x && (nums[i] + nums[i + 1]) >= 2 * x) {
            if (i > 1) dp[i][3] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
            dp[i][3] += 1; // 1 more will be added later
        }

        // case 4
        if (i > 0 && i < n - 1 && nums[i - 1] < x && nums[i] >= x && nums[i + 1] < x
                && (nums[i - 1] + nums[i] + nums[i + 1]) >= 3 * x) {
            if (i > 2) dp[i][4] = max({dp[i - 2][0], dp[i - 2][3], dp[i - 2][4]});
            dp[i][4] += 2; // 1 more will be added later
        }

        // case 5
        if (nums[i] < x) {
            if (i > 0) dp[i][5] = max({dp[i - 1][0], dp[i - 1][3], dp[i - 1][4]});
            dp[i][5] += 1;
        }

        /* for (ll j = 0; j < 6; j++) { */
        /*     cout << dp[i][j] << ' '; */
        /* } */
        /* cout << '\n'; */
    }

    cout << *max_element(dp[n - 1].begin(), dp[n - 1].end()) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll t; cin >> t;
    while (t--) solve();

    return 0;
}

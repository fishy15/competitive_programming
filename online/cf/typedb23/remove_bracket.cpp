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
    int n, s;
    cin >> n >> s;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    auto get_opt = [s](int n) -> pair<ll, ll> {
        if (n < s) {
            return {0, n};
        } else {
            return minmax(s, n - s);
        }
    };

    vector dp(n, array<ll, 2>{});
    auto snd = get_opt(nums[1]);
    dp[1][0] = nums[0] * snd.first;
    dp[1][1] = nums[0] * snd.second;

    for (int i = 2; i < n - 1; i++) {
        auto p = get_opt(nums[i - 1]);
        auto cur = get_opt(nums[i]);

        dp[i][0] = min(dp[i - 1][0] + p.second * cur.first, dp[i - 1][1] + p.first * cur.first);
        dp[i][1] = min(dp[i - 1][0] + p.second * cur.second, dp[i - 1][1] + p.first * cur.second);
    }

    auto last = get_opt(nums[n - 2]);
    auto ans = min(dp[n - 2][0] + last.second * nums[n - 1], dp[n - 2][1] + last.first * nums[n - 1]);
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

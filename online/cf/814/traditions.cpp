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
    int n;
    cin >> n;

    vector<pair<int, int>> comp_nums(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (comp_nums.empty() || comp_nums.back().first != x) {
            comp_nums.push_back({x, 1});
        } else {
            comp_nums.back().second++;
        }
    }

    int sz = comp_nums.size();
    vector<array<int, 3>> dp(sz + 1, {-1, -1, -1});

    auto add_set = [&](int &res, int old, int to_add) {
        if (old != -1) {
            if (res == -1) {
                res = old + to_add;
            } else {
                res = min(res, old + to_add);
            }
        }
    };

    dp[0][0] = 0;

    for (int i = 0; i < sz; i++) {
        if (comp_nums[i].first == 0) {
            add_set(dp[i + 1][0], dp[i][0], 0);
        } else {
            add_set(dp[i + 1][0], dp[i][0], (comp_nums[i].second + 1) / 2);
        }

        if (comp_nums[i].second % 2 == 0) {
            dp[i + 1][1] = dp[i + 1][0];
        } else {
            dp[i + 1][2] = dp[i + 1][0];
        }

        if (i >= 2) {
            if ((comp_nums[i - 2].first ^ comp_nums[i].first) == comp_nums[i - 1].first) {
                for (int j = 0; j < 2; j++) {
                    int sum1 = j + comp_nums[i - 1].second;
                    int sum2 = comp_nums[i - 1].second + comp_nums[i].second;

                    add_set(dp[i + 1][(sum2 % 2) + 1], dp[i - 2][j], (sum1 + 1) / 2 + (sum2 + 1) / 2);
                }
            }
        }

        /* cout << dp[i + 1] << '\n'; */
    }

    int ans = -1;
    add_set(ans, dp[sz][0], 0);
    add_set(ans, dp[sz][1], 0);
    add_set(ans, dp[sz][2], 0);

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

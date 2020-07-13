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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int ckmin(int &a, int b) {
    return a = min(a, b);
}

void solve() {
    int n; cin >> n;
    vector<int> nums;
    vector<array<int, 4>> dp(n, {INF, INF, INF, INF});
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[0][2] = 0;
    dp[0][3] = 0;

    for (int i = 1; i < n; i++) {
        for (int prev = 0; prev < 4; prev++) {
            for (int nxt = 0; nxt < 4; nxt++) {
                if (nums[i - 1] < nums[i]) {
                    if (prev < nxt) ckmin(dp[i][nxt], dp[i - 1][prev]);
                    else ckmin(dp[i][nxt], dp[i - 1][prev] + 1);
                } else if (nums[i - 1] == nums[i]) {
                    if (prev == nxt) ckmin(dp[i][nxt], dp[i - 1][prev]);
                    else ckmin(dp[i][nxt], dp[i - 1][prev] + 1);
                } else {
                    if (prev > nxt) ckmin(dp[i][nxt], dp[i - 1][prev]);
                    else ckmin(dp[i][nxt], dp[i - 1][prev] + 1);
                }
            }
        }
    }

    cout << min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2], dp[n - 1][3]}) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

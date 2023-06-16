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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200000

using namespace std;

int n, m;
int nums[MAXN];
ll dp[MAXN][102];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    if (!nums[0]) {
        for (int i = 1; i <= m; i++) {
            dp[0][i] = 1;
        }
    } else {
        dp[0][nums[0]] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (nums[i]) {
            for (int d = -1; d <= 1; d++) {
                dp[i][nums[i]] += dp[i - 1][nums[i] + d];
                if (dp[i][nums[i]] >= MOD) dp[i][nums[i]] -= MOD;
            }
        } else {
            for (int j = 1; j <= m; j++) {
                for (int d = -1; d <= 1; d++) {
                    dp[i][j] += dp[i - 1][j + d];
                    if (dp[i][j] >= MOD) dp[i][j] -= MOD;
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += dp[n - 1][i];
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans << '\n';

    return 0;
}

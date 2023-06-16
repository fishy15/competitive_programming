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
#define MAXN 1000000

using namespace std;

ll n, w, b, x;
ll dp[1001][10001];
ll c[1000];
ll cost[1000];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> w >> b >> x;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= 10000; j++) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = w;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 10000; j++) {
            if (dp[i][j] == -1) break;
            for (int k = 0; k <= c[i]; k++) {
                ll cc = dp[i][j] - k * cost[i];
                if (cc < 0) break;
                dp[i + 1][j + k] = max(dp[i + 1][j + k], min(w + (j + k) * b, cc + x));
            }
        }
    }

    for (int i = 10000; i >= 0; i--) {
        if (dp[n][i] != -1) {
            cout << i << '\n';
            return 0;
        }
    }

    return 0;
}

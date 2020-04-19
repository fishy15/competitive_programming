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
#define MAXN 100000

using namespace std;

int n, k;
ll dp[501][5001];
int h[11];
int cardcnt[MAXN + 1];
int favcnt[MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n * k; i++) {
        int x; cin >> x;
        cardcnt[x]++;
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        favcnt[x]++;
    }

    for (int i = 1; i <= k; i++) {
        cin >> h[i];
    }

    for (int i = 0; i <= 500; i++) {
        for (int j = 0; j <= 5000; j++) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n * k; j++) {
            if (dp[i][j] == -1) continue;
            for (int d = 0; d <= k; d++) {
                if (j + d <= n * k) {
                    dp[i + 1][j + d] = max(dp[i + 1][j + d], dp[i][j] + h[d]);
                }
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= n * k; j++) {
            dp[i][j] = max(dp[i][j], dp[i][j - 1]);
        }
    }

    ll ans = 0;
    for (int i = 1; i <= MAXN; i++) {
        ll v = dp[favcnt[i]][cardcnt[i]];
        if (v != -1) ans += v;
    }

    cout << ans << '\n';

    return 0;
}

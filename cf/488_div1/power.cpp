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
#define eps 1e-7
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n;
pair<ll, ll> task[110];
// dp[current index][available >][available =]
ld dp[110][110][110];

ld ckmin(ld &a, ld b) {
    return a = min(a, b);
}

bool check(ld val) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                dp[i][j][k] = INFLL;
            }
        }
    }

    dp[0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        ld pp = task[i].first - task[i].second * val;
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                // count this in final sum
                if (task[i].first == task[i + 1].first) {
                    ckmin(dp[i + 1][j][k + 1], dp[i][j][k] + pp);
                } else {
                    ckmin(dp[i + 1][j + k + 1][0], dp[i][j][k] + pp);
                }

                // count this as secondary
                if (j > 0) {
                    if (task[i].first == task[i + 1].first) {
                        ckmin(dp[i + 1][j - 1][k], dp[i][j][k]);
                    } else {
                        ckmin(dp[i + 1][j + k - 1][0], dp[i][j][k]);
                    }
                }
            }
        }
    }

    /* for (int i = n; i <= n; i++) { */
    /*     for (int j = 0; j <= n; j++) { */
    /*         for (int k = 0; k < n; k++) { */
    /*             if (dp[i][j][k] < 100) */
    /*                 cout << dp[i][j][k] << ' '; */
    /*         } */
    /*     } */
    /*     cout << '\n'; */
    /*     cout << '\n'; */
    /* } */
    
    ld ans = INFLL;
    for (int j = 0; j <= n; j++) {
        for (int k = 0; k <= n; k++) {
            ckmin(ans, dp[n][j][k]);
        }
    }

    return ans <= eps;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> task[i].first;
    }

    for (int i = 0; i < n; i++) {
        cin >> task[i].second;
    }

    sort(task, task + n, greater<pair<ll, ll>>());

    ld l = 0;
    ld r = INFLL / 1000;
    ll ans = -1;

    for (int i = 0; i < 500; i++) {
        ld m = (l + r) / 2;
        bool res = check(m);
        if (res) {
            ans = (ll)(ceil(1000 * m));
            r = m;
        } else {
            l = m;
        }
    }

    cout << ans << '\n';

    return 0;
}

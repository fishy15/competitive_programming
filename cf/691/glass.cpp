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
#define MAXN 110

using namespace std;

int n;
array<int, 2> cup[MAXN];
int dp[MAXN][MAXN * MAXN]; // store double of answer
int sum, tot_cap;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cup[i][0] >> cup[i][1];
        sum += cup[i][1];
        tot_cap += cup[i][0];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < MAXN * MAXN; j++) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int k = n; k >= 1; k--) {
            for (int tot = cup[i][0]; tot <= tot_cap; tot++) {
                int &cur = dp[k - 1][tot - cup[i][0]];
                if (cur == -1) continue;
                dp[k][tot] = max(dp[k][tot], cur + cup[i][1]);
            }
        }
    }

    cout << fixed << setprecision(12);
    for (int i = 1; i <= n; i++) {
        int ans = 0;
        for (int tot = 0; tot <= tot_cap; tot++) {
            if (dp[i][tot] == -1) continue;
            ans = max(ans, min(2 * tot, sum + dp[i][tot]));
        }
        cout << ans / 2.0L << ' ';
    }
    cout << '\n';

    return 0;
}

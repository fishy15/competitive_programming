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

int n, l;
ld p;

ld refuse[3010];
ld dp[3010][3010];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> l >> p;

    ld cur_p = 1;
    for (int i = 1; i <= n; i++) {
        cur_p *= p;
        refuse[i] = cur_p;
        dp[l][i] = 1;
    }

    for (int i = l - 1; i >= 0; i--) {
        dp[i][1] = 0.5 * dp[i + 1][1];

        for (int j = 2; j <= n; j++) {
            ld pr = refuse[j];
            ld nxt = 0.5 * dp[i + 1][j] + 0.5 * dp[i + 1][j - 1];
            dp[i][j] = pr * dp[i][j - 1] + (1 - pr) * nxt;
        }
    }

    cout << fixed << setprecision(10) << dp[0][n] << '\n';

    return 0;
}

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

int n, m;
ld dp[210][210][210];
int val[110];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    sort(val, val + n, greater<>());

    m = 2 * n;
    dp[0][0][0] = 1;
    for (int s = 0; s <= m; s++) {
        for (int a = 0; a <= s; a++) {
            int b = s - a;

            for (int x = 0; x <= b; x++) {
                ld pa = (ld) (n - a) / (m - a - b);
                if (a == n) {
                    pa = 0;
                } else if (b == n) {
                    pa = 1;
                }
                if (x == b) {
                    dp[a + 1][b][x] += pa * dp[a][b][x];
                } else {
                    dp[a + 1][b][x + 1] += pa * dp[a][b][x];
                }

                dp[a][b + 1][x] += (1 - pa) * dp[a][b][x];
            }
        }
    }

    ll sum = 0;
    ld ans = 0;
    for (int i = 0; i < n; i++) {
        sum += val[i];
        ans += sum * dp[n][n][i];
    }

    cout << fixed << setprecision(1) << ans << '\n';

    return 0;
}

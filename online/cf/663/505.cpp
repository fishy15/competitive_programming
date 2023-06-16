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
vector<string> grid;
bool s = false;
int dp[MAXN][8];

char g(int i, int j) {
    if (s) swap(i, j);
    return grid[i][j] - '0';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    memset(dp, 0x3f, sizeof dp);

    if (n >= 4 && m >= 4) {
        cout << "-1\n";
        return 0;
    }

    if (n == 1 || m == 1) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    if (m > n) {
        swap(n, m);
        s = true;
    }

    for (int i = 0; i < (1 << m); i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            if (g(0, j) != ((i >> j) & 1)) {
                cnt++;
            }
        }
        dp[0][i] = cnt;
    }

    for (int k = 1; k < n; k++) {
        for (int i = 0; i < (1 << m); i++) {
            int cnt = 0;
            for (int j = 0; j < m; j++) {
                if (g(k, j) != ((i >> j) & 1)) {
                    cnt++;
                }
            }
            int nn = INF;
            for (int p = 0; p < (1 << m); p++) {
                bool ok = true;
                if ((((i & 1) + ((i >> 1) & 1) + (p & 1) + ((p >> 1) & 1)) & 1) == 0) {
                    ok = false;
                }

                if (m == 3 && ((((i >> 2) & 1) + ((i >> 1) & 1) + ((p >> 2) & 1) + ((p >> 1) & 1)) & 1) == 0) {
                    ok = false;
            }

                if (ok && dp[k - 1][p] != INF) {
                    nn = min(nn, dp[k - 1][p] + cnt);
                }

            }

            dp[k][i] = nn;
        }
    }

    int ans = INF;
    for (int i = 0; i < (1 << m); i++) {
        ans = min(ans, dp[n - 1][i]);
    }

    cout << ans << '\n';

    return 0;
}

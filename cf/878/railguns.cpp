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
    int n, m;
    cin >> n >> m;
    
    int r;
    cin >> r;
    map<int, vector<pair<int, int>>> shots;
    
    for (int i = 0; i < r; i++) {
        int t, d, c;
        cin >> t >> d >> c;
        shots[t].push_back({d, c});
    }

    shots[INF] = {};

    int pt = 0;
    vector ok(n + 1, vector(m + 1, false));
    ok[0][0] = true;

    vector min_t(n + 1, vector(m + 1, INF));

    for (auto &[t, v] : shots) {
        queue<pair<int, int>> q;

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (ok[i][j]) {
                    min_t[i][j] = pt;
                    q.push({i, j});
                }
            }
        }

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (min_t[x][y] == t) break;

            if (x < n && min_t[x + 1][y] == INF) {
                min_t[x + 1][y] = min_t[x][y] + 1;
                q.push({x + 1, y});
            }

            if (y < m && min_t[x][y + 1] == INF) {
                min_t[x][y + 1] = min_t[x][y] + 1;
                q.push({x, y + 1});
            }
        }

        if (min_t[n][m] < t) {
            cout << min_t[n][m] << '\n';
            return;
        }

        for (auto [d, c] : v) {
            if (d == 1) {
                for (int j = 0; j <= m; j++) {
                    min_t[c][j] = INF;
                }
            } else {
                for (int i = 0; i <= n; i++) {
                    min_t[i][c] = INF;
                }
            }
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                ok[i][j] = (min_t[i][j] != INF);
            }
        }

        pt = t;
    }
    
    cout << "-1\n";
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

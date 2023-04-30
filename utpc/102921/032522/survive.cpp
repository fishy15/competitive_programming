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

int n, m, k;
bool ok_g[110][110][841];
bool vis[110][110][841];
int dist[110][110][841];

int dx[] = {0, 1, 0, -1, 0};
int dy[] = {1, 0, -1, 0, 0};

bool ok(int x, int y, int t) {
    return x >= 0 && y >= 0 && x < n && y < m && !vis[x][y][t] && ok_g[x][y][t];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            for (int t = 0; t < 840; t++) {
                ok_g[i][j][t] = (s[j] == '.');
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int x, y, k; char d;
        cin >> x >> y >> k >> d;
        x--; y--;

        pair<int, int> dd;
        if (d == 'N') {
            dd = {-1, 0};
        } else if (d == 'S') {
            dd = {1, 0};
        } else if (d == 'E') {
            dd = {0, 1};
        } else {
            dd = {0, -1};
        }

        int cnt = 1;
        int mul = 1;
        for (int t = 0; t < 840; t++) {
            ok_g[x][y][t] = false;

            if (k != 1) {
                if (cnt == k) {
                    cnt = 1;
                    mul *= -1;
                }

                x += dd.first * mul;
                y += dd.second * mul;
                cnt++;
            }
        }
    }

    queue<array<int, 3>> q;
    q.push({0, 0, 0});

    while (!q.empty()) {
        auto [x, y, t] = q.front(); q.pop();

        if (x == n - 1 && y == m - 1) {
            cout << dist[x][y][t] << '\n';;
            return 0;
        }

        for (int i = 0; i < 5; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nt = t + 1;
            if (nt >= 840) nt -= 840;

            if (ok(nx, ny, nt)) {
                vis[nx][ny][nt] = true;
                dist[nx][ny][nt] = dist[x][y][t] + 1;
                q.push({nx, ny, nt});
            }
        }
    }

    cout << "-1\n";

    return 0;
}

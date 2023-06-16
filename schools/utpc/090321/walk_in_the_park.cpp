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
string grid[510];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct dist {
    int x, y;
    vector<vector<int>> d;

    dist(int x, int y) : x(x), y(y) {
        d = vector<vector<int>>(n, vector<int>(m, INF)); 
        bfs();
    }

    bool ok(int a, int b) {
        return a >= 0 && b >= 0 && a < n && b < m && d[a][b] == INF && grid[a][b] != '#';
    }

    void bfs() {
        queue<array<int, 3>> q;
        q.push({0, x, y});

        while (!q.empty()) {
            auto [d2, a, b] = q.front();
            q.pop();

            if (d[a][b] != INF) continue;
            d[a][b] = d2;

            for (int i = 0; i < 4; i++) {
                int nx = a + dx[i];
                int ny = b + dy[i];
                if (ok(nx, ny)) {
                    q.push({d2 + 1, nx, ny});
                }
            }
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    array<int, 2> as, ae, bs, be;
    cin >> as[0] >> as[1];
    cin >> ae[0] >> ae[1];
    cin >> bs[0] >> bs[1];
    cin >> be[0] >> be[1];

    dist das(as[0], as[1]);
    dist dae(ae[0], ae[1]);
    dist dbs(bs[0], bs[1]);
    dist dbe(be[0], be[1]);

    ll ans = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ll d = (ll) das.d[i][j] + dae.d[i][j] + dbs.d[i][j] + dbe.d[i][j];
            ans = min(ans, d);
        }
    }

    if (ans == INF) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}

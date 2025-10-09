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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

array dx = {1, 0, -1, 0};
array dy = {0, 1, 0, -1};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<array<int, 2>> slabs(k);
    vector by_pos(n, vector(m, -1));
    rep(i, 0, k) {
        auto &[x, y] = slabs[i];
        cin >> x >> y;
        x--;
        y--;
        by_pos[x][y] = i;
    }

    int u1, v1, u2, v2;
    cin >> u1 >> v1 >> u2 >> v2;
    u1--;
    v1--;
    u2--;
    v2--;

    int max_bad = -1;
    rep(i, 0, k) {
        auto [x, y] = slabs[i];
        if (u1 <= x && x <= u2 && v1 <= y && y <= v2) {
            max_bad = i;
        }
    }

    if (max_bad == -1) {
        cout << "0\n";
        return;
    }

    vector vis(n, vector<bool>(m));

    // can move up to limit
    auto check = [&](int limit) {
        for (auto &v : vis) {
            fill(all(v), false);
        }

        rep(i, limit+1, k) {
            auto [x, y] = slabs[i];
            vis[x][y] = true;
        }

        auto ok = [&](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < m && !vis[x][y];
        };

        int comp = 0;
        queue<pair<int, int>> q;
        q.push({u1, v1});
        vis[u1][v1] = true;
        int inside = 0;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            comp++;

            if (by_pos[x][y] != -1 && by_pos[x][y] <= limit) {
                inside++;
            }

            rep(i, 0, 4) {
                auto nx = x + dx[i];
                auto ny = y + dy[i];
                if (ok(nx, ny)) {
                    vis[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }

        auto box_size = (u2 - u1 + 1) * (v2 - v1 + 1);
        return comp - box_size >= inside;
    };

    int l = max_bad;
    int r = k - 1;
    int ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    if (ans == -1) {
        cout << "-1\n";
    } else {
        cout << ans + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    solve();

    return 0;
}

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

struct edge {
    pair<int, int> loc;
    int cost;
};

array dx = {0, 1, 0, -1};
array dy = {1, 0, -1, 0};

array diagx = {1, 1, -1, -1};
array diagy = {1, -1, 1, -1};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    rep(i, 0, n) {
        cin >> grid[i];
    }

    auto ok = [&](int x, int y) {
        return x >= 0 && y >= 0 && x < n && y < m;
    };

    auto filled = [&](int x, int y) {
        return ok(x, y) && grid[x][y] == '#';
    };

    auto placeable = [&](int x, int y) {
        if (!ok(x, y)) return false;
        rep(i, 0, 4) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (filled(nx, ny)) {
                return false;
            }
        }
        return true;
    };

    vector dist(n, vector(m, INF));
    vector par(n, vector(m, pair{-1, -1}));
    deque<pair<int, int>> q;
    rep(i, 0, n) {
        if (placeable(i, 0)) {
            if (grid[i][0] == '#') {
                dist[i][0] = 0;
                q.push_front({i, 0});
            } else {
                dist[i][0] = 1;
                q.push_back({i, 0});
            }
        }
    }

    int last_x = -1;
    int last_y = -1;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();

        if (y == m - 1) {
            tie(last_x, last_y) = pair{x, y};
            break;
        }

        rep(i, 0, 4) {
            int nx = x + diagx[i];
            int ny = y + diagy[i];
            if (placeable(nx, ny) && dist[nx][ny] == INF) {
                if (grid[nx][ny] == '#') {
                    dist[nx][ny] = dist[x][y];
                    par[nx][ny] = {x, y};
                    q.push_front({nx, ny});
                } else {
                    dist[nx][ny] = dist[x][y] + 1;
                    par[nx][ny] = {x, y};
                    q.push_back({nx, ny});
                }
            }
        }
    }

    if (last_x == -1 && last_y == -1) {
        cout << "NO\n";
    } else {
        while (last_x != -1) {
            grid[last_x][last_y] = '#';
            tie(last_x, last_y) = par[last_x][last_y];
        }

        cout << "YES\n";
        for (const auto &row : grid) {
            cout << row << '\n';
        }
    }
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

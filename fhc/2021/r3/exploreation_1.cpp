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

struct DSU {
    int n, m;
    vector<int> dsu;
    vector<int> sz;
    vector<bool> robot;

    DSU(int n, int m) : n(n), m(m) {
        dsu.resize(n * m);
        sz.resize(n * m);
        robot.resize(n * m);
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
    }

    int conv(int x, int y) {
        return x * m + y;
    }

    int find(array<int, 2> x) {
        return find(conv(x[0], x[1]));
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void add_robot(array<int, 2> x) {
        robot[find(x)] = true;
    }

    bool has_robot(array<int, 2> x) {
        return robot[find(x)];
    }

    void join(array<int, 2> x, array<int, 2> y) {
        join(conv(x[0], x[1]), conv(y[0], y[1]));
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
            robot[x] = robot[x] || robot[y];
        }
    }

    int get_sz(int x) {
        return sz[find(x)];
    }
};

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void solve() {
    int r, c; cin >> r >> c;
    vector<vector<int>> h(r, vector<int>(c));
    vector<vector<int>> s(r, vector<int>(c));
    map<int, vector<array<int, 3>>> events;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> h[i][j];
            events[h[i][j]].push_back({1, i, j});
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> s[i][j];
            events[s[i][j]].push_back({0, i, j});
        }
    }

    for (auto &[t, v] : events) {
        sort(v.begin(), v.end());
    }

    auto ok = [&](int x, int y) {
        return x >= 0 && y >= 0 && x < r && y < c;
    };

    DSU dsu(r, c);
    int loc_cnt = 0;
    int bot_cnt = 0;

    for (auto it = events.rbegin(); it != events.rend(); it++) {
        auto &[t, v] = *it;
        for (auto [a, x, y] : v) {
            if (a == 1) {
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (ok(nx, ny) && h[nx][ny] >= t) {
                        dsu.join({x, y}, {nx, ny});
                    }
                }
            } else {
                if (s[x][y] < h[x][y]) {
                    loc_cnt++;
                    if (!dsu.has_robot({x, y})) {
                        dsu.add_robot({x, y});
                        bot_cnt++;
                    }
                }
            }
        }
    }

    cout << loc_cnt << ' ' << bot_cnt << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

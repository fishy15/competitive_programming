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
#include <cassert>

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

array dx = {0, 1, 0, -1};
array dy = {1, 0, -1, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int r, c;
    cin >> r >> c;

    vector<string> grid(r);
    rep(i, 0, r) {
        cin >> grid[i];
    }

    auto ok = [&](int x, int y) {
        return (0 <= x && x < r) && (0 <= y && y < c);
    };

    auto is_sight = [&](int x, int y) {
        return ok(x, y) && grid[x][y] == '#';
    };

    auto is_land = [&](int x, int y) {
        return ok(x, y) && (grid[x][y] == '.' || grid[x][y] == '#');
    };

    auto is_water = [&](int x, int y) {
        return ok(x, y) && !is_land(x, y);
    };

    auto next = [&](int x, int y) {
        assert(is_water(x, y));
        if (grid[x][y] == '^') {
            x--;
        } else if (grid[x][y] == '<') {
            y--;
        } else if (grid[x][y] == 'v') {
            x++;
        } else {
            y++;
        }
        return pair{x, y};
    };

    auto get_adj = [&](int x, int y) {
        vector<pair<int, int>> res;
        rep(i, 0, 4) {
            auto nx = x + dx[i];
            auto ny = y + dy[i];
            if (is_sight(nx, ny)) {
                res.push_back({nx, ny});
            }
        }
        return res;
    };

    int ans = 0;
    vector vis(r, vector<bool>(c));

    auto find_cycle = [&](int sx, int sy) {
        vector<pair<int, int>> vis_states;
        vector<pair<int, int>> cyc;
        int cx, cy;
        tie(cx, cy) = {sx, sy};
        while (true) {
            vis[cx][cy] = true;
            vis_states.push_back({cx, cy});
            auto [nx, ny] = next(cx, cy);
            if (!is_water(nx, ny)) {
                vis_states.pop_back();
                cyc = {{cx, cy}};
                break;
            } else if (vis[nx][ny]) {
                while (cyc.empty() || cyc.back() != pair{nx, ny}) {
                    cyc.push_back(vis_states.back());
                    vis_states.pop_back();
                }
                break;
            }

            tie(cx, cy) = {nx, ny};
        }

        // leave everything outside of cycle untouched
        for (auto [x, y] : vis_states) {
            vis[x][y] = false;
        }
        return cyc;
    };

    auto process_cycle = [&](vector<pair<int, int>> &cyc) {
        set<pair<int, int>> cur_set;
        for (auto [x, y] : cyc) {
            for (auto p : get_adj(x, y)) {
                cur_set.insert(p);
            }
        }

        ans = max(ans, sz(cur_set));
        auto dfs = [&](auto &&self, int x, int y) -> void {
            vis[x][y] = true;
            vector<pair<int, int>> added;
            for (auto p : get_adj(x, y)) {
                if (!cur_set.count(p)) {
                    cur_set.insert(p);
                    added.push_back(p);
                }
            }

            ans = max(ans, sz(cur_set));

            rep(i, 0, 4) {
                auto nx = x + dx[i];
                auto ny = y + dy[i];
                if (is_water(nx, ny) && next(nx, ny) == pair{x, y} && !vis[nx][ny]) {
                    self(self, nx, ny);
                }
            }

            for (auto p : added) {
                cur_set.erase(p);
            }
        };

        for (auto [x, y] : cyc) {
            dfs(dfs, x, y);
        }
    };

    rep(i, 0, r) {
        rep(j, 0, c) {
            if (is_water(i, j) && !vis[i][j]) {
                auto cyc = find_cycle(i, j);
                process_cycle(cyc);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}

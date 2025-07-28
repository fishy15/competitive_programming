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

constexpr array dx = {1, 0, -1, 0};
constexpr array dy = {0, 1, 0, -1};

using vi = vector<int>;

template<class F> vi scc(const vector<vi> &adj, F f) {
    int n = sz(adj);
    vi val(n), comp(n, -1), z, cont;
    int time = 0, ncomps = 0;
    auto dfs = [&](auto &&self, int u) -> int {
        int low = val[u] = ++time, x; z.push_back(u);
        for (auto e : adj[u]) if (comp[e] < 0)
            low = min(low, val[e] ?: self(self, e));
        if (low == val[u]) {
            do {
                x = z.back(); z.pop_back();
                comp[x] = ncomps;
                cont.push_back(x);
            } while (x != u);
            f(cont); cont.clear();
            ncomps++;
        }
        return val[u] = low;
    };
    rep(i, 0, n) {
        if (comp[i] < 0) dfs(dfs, i);
    }
    return comp;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    rep(i, 0, n) {
        cin >> grid[i];
    }

    vector<int> a(m);
    rep(i, 0, m) {
        cin >> a[i];
    }

    auto ok = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    vector color(n, vector<int>(m, -1));

    queue<pair<int, int>> q;
    int ccs = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (grid[i][j] == '#' && color[i][j] == -1) {
                q.push({i, j});
                color[i][j] = ccs;
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    rep(i, 0, 4) {
                        auto nx = x + dx[i];
                        auto ny = y + dy[i];
                        if (ok(nx, ny) && grid[nx][ny] == '#' && color[nx][ny] == -1) {
                            color[nx][ny] = ccs;
                            q.push({nx, ny});
                        }
                    }
                }
                ccs++;
            }
        }
    }

    vector<vector<pair<int, int>>> locs(m);
    rep(j, 0, m) {
        rep(i, 0, n) {
            if (color[i][j] != -1) {
                locs[j].push_back({i, color[i][j]});
            }
        }
    }

    auto get_above = [&](int x, int y) {
        auto it = upper_bound(rbegin(locs[y]), rend(locs[y]), pair{x, -1}, greater<>{});
        if (it != rend(locs[y])) {
            return it->second;
        }
        return -1;
    };

    vector<vector<int>> radj(ccs);
    rep(i, 0, n) {
        rep(j, 0, m) {
            auto c = color[i][j];
            if (c != -1) {
                auto p1 = get_above(i, j);
                if (p1 != -1 && p1 != c) {
                    radj[c].push_back(p1);
                }
                if (j > 0) {
                    auto p2 = get_above(i, j-1);
                    if (p2 != -1 && p2 != c) {
                        radj[c].push_back(p2);
                    }
                }
                if (j < m-1) {
                    auto p3 = get_above(i, j+1);
                    if (p3 != -1 && p3 != c) {
                        radj[c].push_back(p3);
                    }
                }
            }
        }
    }

    for (auto &v : radj) {
        sort(all(v));
        v.erase(unique(all(v)), end(v));
    }

    vector<vector<int>> comps;
    auto comp_id = scc(radj, [&](const vector<int> &comp) {
        comps.push_back(comp);
    });

    int ans = 0;
    rep(i, 0, sz(comps)) {
        bool ok = true;
        for (auto v : comps[i]) {
            for (auto e : radj[v]) {
                if (comp_id[e] != i) {
                    ok = false;
                    break;
                }
            }
        }

        if (ok) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}

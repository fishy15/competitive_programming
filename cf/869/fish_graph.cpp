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

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) : dsu(n), sz(n) {
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
};

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto check = [&](int u) {
        DSU dsu(n);
        for (int v = 0; v < n; v++) {
            for (auto w : adj[v]) {
                if (v != u && w != u) {
                    dsu.join(v, w);
                }
            }
        }

        map<int, vector<int>> out_set;
        for (auto v : adj[u]) {
            out_set[dsu.find(v)].push_back(v);
        }

        if (out_set.size() < adj[u].size() && (int) adj[u].size() >= 4) {
            cout << "YES\n";

            vector<int> p(n, -1);
            vector<bool> vis(n);
            vector<int> tin(n);

            int t = 0;
            auto dfs = y_combinator([&](auto self, int v, int par) -> void {
                tin[v] = t++;
                vis[v] = true;
                p[v] = par;

                for (auto w : adj[v]) {
                    if (v != u && w != u && !vis[w]) {
                        self(w, v);
                    }
                }
            });

            vector<pair<int, int>> edge_set;
            set<int> used;
            for (auto &[_, grp] : out_set) {
                if ((int) grp.size() >= 2) {
                    int s = grp[0];
                    dfs(s, -1);

                    int e = -1;
                    int vt = INF;
                    for (auto w : grp) {
                        if (w != s) {
                            if (tin[p[w]] < vt) {
                                vt = tin[p[w]];
                                e = w;
                            }
                        }
                    }

                    edge_set.push_back({u, s});
                    edge_set.push_back({u, e});
                    used.insert(s);
                    used.insert(e);

                    int cur = e;
                    while (cur != s) {
                        edge_set.push_back({cur, p[cur]});
                        cur = p[cur];
                    }

                    break;
                }
            }

            int added = 0;
            for (auto e : adj[u]) {
                if (!used.count(e)) {
                    added++;
                    edge_set.push_back({u, e});

                    if (added == 2) {
                        break;
                    }
                }
            }

            cout << edge_set.size() << '\n';
            for (auto [a, b] : edge_set) {
                cout << a + 1 << ' ' << b + 1 << '\n';
            }

            return true;
        }

        return false;
    };

    for (int i = 0; i < n; i++) {
        if (check(i)) return;
    }

    cout << "NO\n";
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

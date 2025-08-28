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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

struct DSU {
    vector<int> dsu;
    vector<bool> zerod;

    DSU(int n) : dsu(n), zerod(n) {
        iota(all(dsu), 0);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int p, int c) {
        if ((p = find(p)) != (c = find(c))) {
            dsu[c] = p;
            zerod[p] = zerod[p] || zerod[c];
        }
    }
};

void solve() {
    int n, m, V;
    cin >> n >> m >> V;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    vector<vector<int>> adj(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 0 = unvisited
    // 1 = in the process of visiting (back edge)
    // 2 = done processing
    vector<int> vis(n);
    vector<int> par(n, -1);
    vector<int> dist(n);
    DSU dsu(n);
    auto dfs = [&](auto &&self, int v, int p) -> void {
        par[v] = p;
        vis[v] = 1;
        for (auto e : adj[v]) {
            if (e != p) {
                if (vis[e] == 0) {
                    dist[e] = dist[v] + 1;
                    self(self, e, v);
                } else if (vis[e] == 1) {
                    // join everything in the cycle, e to v
                    int cur_v = v;
                    while (dsu.find(e) != dsu.find(cur_v)) {
                        dsu.join(par[cur_v], cur_v);
                        cur_v = dsu.find(cur_v);
                    }
                    if (dist[v] % 2 == dist[e] % 2) {
                        // represents an odd cycle
                        dsu.zerod[dsu.find(e)] = true;
                    }
                }
            }
        }
        vis[v] = 2;
    };
    dfs(dfs, 0, 0);

    vector<vector<int>> comps(n);
    rep(i, 0, n) {
        comps[dsu.find(i)].push_back(i);
    }

    mi ans = 1;
    for (auto &c : comps) {
        if (!c.empty()) {
            if (sz(c) == 1) {
                if (a[c[0]] == -1) {
                    ans *= V;
                }
            } else {
                // all these values need to be the same
                set<int> poss;
                int neg_one_cnt = 0;
                for (auto x : c) {
                    if (a[x] == -1) {
                        neg_one_cnt++;
                    } else {
                        poss.insert(a[x]);
                    }
                }

                auto needs_zero = dsu.zerod[dsu.find(c[0])];
                if (sz(poss) > 1) {
                    ans = 0;
                } else if (sz(poss) == 1 && needs_zero) {
                    if (*begin(poss) != 0) {
                        ans = 0;
                    }
                } else if (sz(poss) == 0) {
                    if (!needs_zero) {
                        ans *= V;
                    }
                }
            }
        }
    }

    cout << ans.v << '\n';
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

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

constexpr int L = 20;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    set<int> not_deleted;
    rep(i, 0, n) {
        not_deleted.insert(i);
    }

    vector<bool> deleted(n);
    vector<array<int, 3>> ord;

    vector<int> in(n), out(n);
    vector<array<int, L>> up(n);
    int t = 0;
    auto dfs1 = [&](auto &&self, int v, int p) -> void {
        in[v] = t++;
        up[v][0] = p;
        rep(i, 1, L) {
            up[v][i] = up[up[v][i-1]][i-1];
        }

        for (auto e : adj[v]) {
            if (e != p) {
                self(self, e, v);
            }
        }

        out[v] = t++;
    };
    dfs1(dfs1, 0, 0);

    auto anc = [&](int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    };

    auto lca = [&](int u, int v) {
        if (anc(u, v)) return u;
        if (anc(v, u)) return v;
        for (int i = L-1; i >= 0; i--) {
            if (!anc(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    };

    auto mark_path = [&](int u, int v) {
        auto l = lca(u, v);
        while (u != l) {
            deleted[u] = true;
            not_deleted.erase(u);
            u = up[u][0];
        }
        while (v != l) {
            deleted[v] = true;
            not_deleted.erase(v);
            v = up[v][0];
        }
        deleted[l] = true;
        not_deleted.erase(l);
    };

    while (!not_deleted.empty()) {
        auto x = *begin(not_deleted);
        auto dfs = [&](auto &&self, int v, int p, int d) -> pair<int, int> {
            pair<int, int> best = {d, v};
            for (auto e : adj[v]) {
                if (e != p && !deleted[e]) {
                    best = max(best, self(self, e, v, d+1));
                }
            }
            return best;
        };

        auto [_, d1] = dfs(dfs, x, x, 0);
        auto [d, d2] = dfs(dfs, d1, d1, 1);
        mark_path(d1, d2);

        if (d1 < d2) {
            swap(d1, d2);
        }
        ord.push_back({d, d1, d2});
    }

    sort(all(ord), greater<>{});

    for (auto [a, b, c] : ord) {
        cout << a << ' ' << b+1 << ' ' << c+1 << ' ';
    }
    cout << '\n';
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

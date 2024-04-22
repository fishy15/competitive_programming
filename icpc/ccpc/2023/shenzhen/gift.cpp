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

void add_to(map<int, int> &m, int x) {
    if (m[x] == 1) {
        m.erase(x);
    } else {
        m[x]--;
    }

    m[x + 1]++;
}

void sub_from(map<int, int> &m, int x) {
    if (m[x] == 1) {
        m.erase(x);
    } else {
        m[x]--;
    }

    m[x - 1]++;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    vector<int> deg(n);
    vector<pair<int, int>> edge;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        deg[x]++;
        deg[y]++;
        adj[x].push_back(y);
        adj[y].push_back(x);
        edge.push_back({x, y});
    }

    vector<bool> vis(n);
    vector<int> in(n), out(n);
    int t = 0;
    pair<int, int> extra;
    auto dfs = [&](auto &&self, int v, int p) -> void {
        vis[v] = true;
        in[v] = t++;

        for (auto e : adj[v]) {
            if (!vis[e]) {
                self(self, e, v);
            } else if (e != p) {
                extra = {e, v};
            }
        }
        
        out[v] = t++;
    };

    auto anc = [&](int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    };

    map<int, int> degm;
    for (auto d : deg) {
        degm[d]++;
    }

    dfs(dfs, 0, 0);

    // u is lower, v is higher
    auto [u, v] = extra;

    auto not_strict_anc = [&](int u, int v) {
        return u == v || !anc(u, v);
    };

    ll ans = 0;
    for (auto e : edge) {
        auto [a, b] = e;
        auto ok = [&](int x) {
            return anc(x, u) && not_strict_anc(x, v);
        };

        if (ok(a) && ok(b)) {
            sub_from(degm, deg[a]);
            sub_from(degm, deg[b]);

            if (degm.upper_bound(4) != degm.end()) {
                // at least smth w deg >= 5
                // do nothing
            } else {
                auto it = degm.find(4);
                if (it != degm.end()) {
                    ans += n - it->second;
                } else {
                    ans += n;
                }
            }

            add_to(degm, deg[a] - 1);
            add_to(degm, deg[b] - 1);
        }
    }

    cout << ans << '\n';

    return 0;
}

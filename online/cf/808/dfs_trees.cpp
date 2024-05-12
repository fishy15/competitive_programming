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
    vector<int> dsu, sz;

    DSU(int n) : dsu(n), sz(n, 1) {
        iota(dsu.begin(), dsu.end(), 0);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    bool join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
            return true;
        }
        return false;
    }
};

struct tree {
    constexpr static int L = 20;

    vector<vector<int>> adj;
    vector<int> in, out;
    vector<array<int, L>> up;
    int t = 0;

    tree(int n) : adj(n), in(n), out(n), up(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p) {
        in[v] = t++;

        up[v][0] = p;
        for (int i = 1; i < L; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (auto e : adj[v]) {
            if (e != p) {
                dfs(e, v);
            }
        }

        out[v] = t++;
    }

    // assumed u is a strict ancestor of v
    int one_below(int u, int v) {
        for (int i = L - 1; i >= 0; i--) {
            if (!anc(up[v][i], u)) v = up[v][i];
        }
        return v;
    }

    bool anc(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }
};

struct BIT {
    int n;
    vector<int> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void upd(int x, int v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    
    int qry(int r) {
        int res{};
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }

    int qry(int l, int r) {
        return qry(r) - qry(l);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edges.push_back({u, v});
    }

    DSU dsu(n);
    tree t(n);
    vector<pair<int, int>> extra;
    for (auto [u, v] : edges) {
        if (dsu.join(u, v)) {
            t.add_edge(u, v);
        } else {
            extra.push_back({u, v});
        }
    }

    t.dfs(0, 0);

    vector<int> ok(2*n);
    auto add_away = [&](int u, int v) {
        if (t.anc(u, v)) {
            int below = t.one_below(u, v);
            ok[0]++;
            ok[2*n-1]--;
            ok[t.in[below]]--;
            ok[t.out[below]]++;
        } else {
            ok[t.in[u]]++;
            ok[t.out[u]]--;
        }
    };

    for (auto [u, v] : extra) {
        add_away(u, v);
        add_away(v, u);
    }

    for (int i = 1; i < 2 * n; i++) {
        ok[i] += ok[i - 1];
    }

    for (int i = 0; i < n; i++) {
        if (ok[t.in[i]] == (int) extra.size()) {
            cout << 1;
        } else {
            cout << 0;
        }
    }
    cout << '\n';

    return 0;
}

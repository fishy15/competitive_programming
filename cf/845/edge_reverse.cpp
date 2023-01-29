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

struct SCC {
    int sz;
    vector<vector<int>> adj;
    vector<vector<int>> radj;
    vector<int> comp;
    vector<bool> vis;
    vector<int> ord;
    vector<int> cur_comp;
    vector<vector<int>> in_comp;

    SCC(int n) : sz(n), adj(n), radj(n), comp(n), vis(n) {}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    void dfs_ord(int v) {
        vis[v] = true;
        for (int e : adj[v]) {
            if (!vis[e]) {
                dfs_ord(e);
            }
        }
        ord.push_back(v);
    }

    void dfs_scc(int v) {
        vis[v] = true;
        cur_comp.push_back(v);
        for (int e : radj[v]) {
            if (!vis[e]) {
                dfs_scc(e);
            }
        }
    }

    int find_scc() {
        for (int i = 0; i < sz; i++) {
            if (!vis[i]) {
                dfs_ord(i);
            }
        }

        fill(vis.begin(), vis.end(), false);
        reverse(ord.begin(), ord.end());

        int cnt = 0;
        for (int v : ord) {
            if (!vis[v]) {
                cur_comp = {};
                dfs_scc(v);
                for (int i : cur_comp) {
                    comp[i] = cnt;
                }
                cnt++;
                in_comp.push_back(cur_comp);
            }
        }

        return cnt;
    }
};

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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<array<int, 3>> edges;
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;

        edges.push_back({a, b, w});
    }

    auto check_conn = [&]() {
        DSU dsu(n);
        for (auto [a, b, _] : edges) {
            dsu.join(a, b);
        }

        int ok = dsu.find(0);
        for (int i = 1; i < n; i++) {
            if (dsu.find(i) != ok) {
                return false;
            }
        }

        return true;
    };

    if (!check_conn()) {
        cout << "-1\n";
        return;
    }

    auto check = [&](ll m) {
        SCC scc(n);

        for (auto [a, b, w] : edges) {
            scc.add_edge(b, a);
            
            if (w <= m) {
                scc.add_edge(a, b);
            }
        }

        auto num_comps = scc.find_scc();

        vector<bool> works(num_comps);
        
        works.back() = true;

        for (int i = num_comps - 2; i >= 0; i--) {
            for (auto x : scc.in_comp[i]) {
                for (auto v : scc.adj[x]) {
                    if (works[scc.comp[v]]) {
                        works[i] = true;
                        goto done;
                    }
                }
            }

done:
            if (!works[i]) {
                return false;
            }
        }

        return true;
    };

    ll l = 0;
    ll r = 1'000'000'001;

    while (l < r) {
        ll m = l + (r - l) / 2;
        if (check(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << r << '\n';
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

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

template<bool op_edges = false>
struct hld {
    vector<vector<int>> adj;
    vector<int> par;
    vector<int> sz;
    vector<int> in;
    vector<int> head;
    vector<int> d;
    int t{};

    hld(int n) : adj(n), par(n), sz(n), in(n), head(n), d(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs_size(int v = 0, int p = 0) {
        sz[v] = 1;
        for (int &e : adj[v]) {
            if (e != p) {
                d[e] = d[v] + 1;
                par[e] = v;
                dfs_size(e, v);
                sz[v] += sz[e];
                if (sz[e] > sz[adj[v][0]] || adj[v][0] == p) swap(e, adj[v][0]);
            }
        }
    }

    void dfs_hld(int v = 0, int p = 0) {
        in[v] = t++;
        for (int e : adj[v]) {
            if (e != p) {
                if (e == adj[v][0]) {
                    head[e] = head[v];
                } else {
                    head[e] = e;
                }
                dfs_hld(e, v);
            }
        }
    }

    template<typename F, bool enabled = !op_edges, enable_if_t<enabled, bool> = true>
    void op_node(int x, F op) {
        op(in[x]);
    }

    template<typename F, bool enabled = op_edges, enable_if_t<enabled, bool> = true>
    void op_edge(int x, int y, F op) {
        if (d[x] < d[y]) swap(x, y);
        op(in[x]);
    }

    template<typename F>
    void op_path(int x, int y, F op) {
        while (head[x] != head[y]) {
            if (d[head[x]] > d[head[y]]) swap(x, y);
            op(in[head[y]], in[y] + 1);
            y = par[head[y]];
        }
        if (d[x] > d[y]) swap(x, y);
        op(in[x] + (op_edges ? 1 : 0), in[y] + 1);
    }

    template<typename F>
    void op_subtree(int x, F op) { 
        op(in[x] + (op_edges ? 1 : 0), in[x] + sz[x]);
    }
};

struct segtree {
    int n;
    vector<pair<int, int>> st;
    segtree(int n) : n(n), st(4 * n, {INF, -1}) {}
    void upd(int x, pair<int, int> y) { upd(1, 0, n, x, y); }
    void upd(int v, int l, int r, int x, pair<int, int> y) {
        if (l + 1 == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2 * v, l, m, x, y);
            } else {
                upd(2 * v + 1, m, r, x, y);
            }
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) const { return qry(1, 0, n, x, y).second; }
    pair<int, int> qry(int v, int l, int r, int x, int y) const {
        if (r <= x || y <= l) return {INF, -1};
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return min(qry(2 * v, l, m, x, y), qry(2 * v + 1, m, r, x, y));
    }
};

struct tree {
    vector<vector<int>> adj;
    int ans;
    int cur;

    tree(int n) : adj(n), ans{}, cur{} {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p, hld<> &b, segtree &st) {
        int on_path = -1;

        b.op_path(0, v, [&](int x, int y) {
            auto res = st.qry(x, y);
            if (res != -1) {
                on_path = res;
            }
        });

        auto set = [&](int x) {
            b.op_node(x, [&](int y) { st.upd(y, {b.d[x], x}); });
        };

        auto unset = [&](int x) {
            b.op_node(x, [&](int y) { st.upd(y, {INF, -1}); });
        };

        if (on_path == -1) {
            // unconditionally we add this
            cur++;
            set(v);
        } else if (b.d[on_path] < b.d[v]) {
            unset(on_path);
            set(v);
        }

        ans = max(ans, cur);

        for (auto e : adj[v]) {
            if (e != p) {
                dfs(e, v, b, st);
            }
        }

        // have to reset
        if (on_path == -1) {
            unset(v);
            cur--;
        } else if (b.d[on_path] < b.d[v]) {
            unset(v);
            set(on_path);
        }
    }
};

void solve() {
    int n;
    cin >> n;

    tree a(n);
    for (int v = 1; v < n; v++) {
        int p;
        cin >> p;
        p--;
        a.add_edge(p, v);
    }

    hld<> b(n);
    for (int v = 1; v < n; v++) {
        int p;
        cin >> p;
        p--;
        b.add_edge(p, v);
    }

    b.dfs_size();
    b.dfs_hld();

    segtree st(n);

    a.dfs(0, -1, b, st);
    cout << a.ans << '\n';
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

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
#include <functional>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct tree {
    vector<vector<int>> adj;
    vector<int> par;
    vector<int> sz;
    vector<int> in;
    vector<int> head;
    vector<int> d;
    int t = 0;

    tree(int n) {
        adj.resize(n);
        par.resize(n);
        sz.resize(n);
        in.resize(n);
        head.resize(n);
        d.resize(n);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs_size(int v = 0, int p = -1) {
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

    void dfs_hld(int v = 0, int p = -1) {
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

    void op_path(int x, int y, function<void(int,int)> op) {
        while (head[x] != head[y]) {
            if (d[head[x]] > d[head[y]]) swap(x, y);
            op(in[head[y]], in[y]);
            y = par[head[y]];
        }
        if (d[x] > d[y]) swap(x, y);
        op(in[x] + 1, in[y]);
    }
};

struct segtree {
    int n;
    vector<ll> st;
    segtree(int n) : n(n) { st.resize(4 * n); }
    void upd(int x, ll y) { upd(x, y, 1, 0, n - 1); }
    void upd(int x, ll y, int v, int l, int r) {
        if (l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m + 1, r);
            }
            st[v] = gcd(st[2 * v], st[2 * v + 1]);
        }
    }
    ll qry(int x, int y) { return qry(x, y, 1, 0, n - 1); }
    ll qry(int x, int y, int v, int l, int r) {
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        ll q = gcd(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
        return q;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    tree t(n);
    segtree st(n);

    vector<array<ll, 4>> edge;
    vector<ll> ans(q);
    for (int i = 0; i < n - 1; i++) {
        ll x, y, l, a; cin >> x >> y >> l >> a;
        x--; y--;
        t.add_edge(x, y);
        edge.push_back({x, y, l, a});
    }

    t.dfs_size();
    t.dfs_hld();

    vector<array<ll, 4>> qry;
    for (auto [x, y, l, a] : edge) {
        if (t.par[x] == y) {
            qry.push_back({l, 0, x, a});
        } else {
            qry.push_back({l, 0, y, a});
        }
    }

    for (int i = 0; i < q; i++) {
        ll c, w; cin >> c >> w;
        c--;
        qry.push_back({w, 1, c, i});
    }

    sort(qry.begin(), qry.end());
    for (auto [w, ty, a, b] : qry) {
        if (ty == 0) {
            st.upd(t.in[a], b);
        } else {
            ll res = 0;
            t.op_path(0, a, [&](int u, int v) { res = gcd(res, st.qry(u, v)); });
            ans[b] = res;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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

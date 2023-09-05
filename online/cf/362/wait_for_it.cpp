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
        static int t = 0;
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

struct girl {
    ll weight;
    int loc;
    int index;
    bool operator<(const girl &other) const { 
        return tie(weight, index) < tie(other.weight, other.index);
    }
    girl operator+(ll x) const {
        girl res = *this;
        return res += x;
    }
    girl &operator+=(ll x) {
        weight += x;
        return *this;
    }
};

struct lazy_segtree {
    int n;
    mutable vector<girl> st;
    mutable vector<ll> lazy;
    mutable vector<ll> lazy_acc;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n), lazy_acc(n) { build(1, 0, n); }
    void build(int v, int l, int r) {
        if (l + 1 == r) {
            st[v] = {INFLL, -1, -1};
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m, r);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) const {
        if (l + 1 != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        } else {
            lazy_acc[l] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, ll q) { upd(x, y, q, 1, 0, n); }
    void upd(int x, int y, ll q, int v, int l, int r) {
        push(v, l, r);
        if (r <= x || l >= y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m, r);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    void set(int x, girl g) { set(x, g, 1, 0, n); }
    void set(int x, girl g, int v, int l, int r) {
        push(v, l, r);
        if (l > x || x >= r) return;
        if (l + 1 == r) {
            st[v] = g + lazy_acc[l];
        } else {
            int m = (l + r) / 2;
            set(x, g, 2 * v, l, m);
            set(x, g, 2 * v + 1, m, r);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    girl qry(int x, int y) const { return qry(x, y, 1, 0, n); }
    girl qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r <= x || l >= y) return {INFLL, -1, -1};
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return min(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m, r));
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    hld<> t(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        t.add_edge(u, v);
    }

    t.dfs_size();
    t.dfs_hld();

    vector<deque<girl>> init_locs(n);

    for (int i = 0; i < m; i++) {
        int c;
        cin >> c;
        c--;
        girl g{i + 1, c, i};
        init_locs[c].push_back(g);
    }

    lazy_segtree st(n);
    for (int i = 0; i < n; i++) {
        if (!init_locs[i].empty()) {
            auto top_girl = init_locs[i].front();
            t.op_node(i, [&st, &top_girl](int x) {
                st.set(x, top_girl);
            });
        }
    }

    while (q--) {
        int tt;
        cin >> tt;

        if (tt == 1) {
            int u, v, k;
            cin >> u >> v >> k;
            u--;
            v--;

            vector<girl> res;
            for (int i = 0; i < k; i++) {
                girl g = {INFLL, -1, -1};
                t.op_path(u, v, [&g, &st](int x, int y) {
                    g = min(g, st.qry(x, y));
                });

                if (g.loc == -1) {
                    break;
                }
                res.push_back(g);

                // delete it
                auto &cur = init_locs[g.loc];
                assert(!cur.empty());
                assert(cur.front().index == g.index);
                cur.pop_front();

                girl nxt_girl;
                if (cur.empty()) {
                    nxt_girl = {INFLL, -1, -1};
                } else {
                    nxt_girl = cur.front();
                }

                t.op_node(g.loc, [&nxt_girl, &st](int x) {
                    st.set(x, nxt_girl);
                });
            }

            cout << res.size() << ' ';
            for (auto &g : res) {
                cout << g.index + 1 << ' ';
            }
            cout << '\n';
        } else {
            int v;
            ll k;
            cin >> v >> k;
            v--;
            t.op_subtree(v, [k, &st](int u, int v) {
                st.upd(u, v, k);
            });
        }
    }

    return 0;
}


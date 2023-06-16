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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

struct segtree {
    int n;
    vector<int> st;

    segtree(int n) : n(n), st(2 * n) {}
    segtree(int n, vector<int> &nums) : segtree(n) { 
        copy(nums.begin(), nums.end(), st.begin() + n);
        for (int i = n - 1; i > 0; i--) {
            st[i] = max(st[i << 1], st[i << 1 | 1]);
        }
    }

    void upd(int x, int y) { 
        x += n;
        st[x] = y;
        while (x > 1) {
            st[x >> 1] = max(st[x], st[x ^ 1]);
            x >>= 1;
        }
    }

    int qry(int l, int r) const {
        int ans = 0;
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                ans = max(ans, st[l]);
                l++;
            }

            if (r & 1) {
                r--;
                ans = max(ans, st[r]);
            }

            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    segtree st(n, val);
    hld<> tree(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        tree.add_edge(a, b);
    }

    tree.dfs_size();
    tree.dfs_hld();

    auto upd_node = [&tree, &st](int v, int val) {
        tree.op_node(v, [val, &st](int v) { st.upd(v, val); });
    };

    auto qry_path = [&tree, &st](int x, int y) {
        int res = 0;
        tree.op_path(x, y, [&res, &st](int x, int y) { res = max(res, st.qry(x, y)); });
        return res;
    };

    for (int i = 0; i < n; i++) {
        upd_node(i, val[i]);
    }

    while (q--) {
        int t, a, b; 
        cin >> t >> a >> b;

        if (t == 1) {
            a--;
            upd_node(a, b);
        } else {
            a--;
            b--;
            cout << qry_path(a, b) << ' ';
        }
    }
    cout << '\n';

    return 0;
}

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

struct lazy_segtree {
    int n;
    mutable vector<ll> st;
    mutable vector<ll> lazy;
    lazy_segtree() : lazy_segtree(0) {}
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) {}
    void push(int v, int l, int r) const {
        if (r - l != 1) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
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
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    ll qry(int x, int y) const { return qry(x, y, 1, 0, n); }
    ll qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r <= x || l >= y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m, r));
    }
};


struct CD {
    vector<vector<pair<int, ll>>> adj;
    vector<int> size, vis;
    vector<vector<int>> pars; // parents in centroid tree
    vector<map<int, int>> in;
    vector<vector<int>> out;
    vector<vector<int>> orig;
    vector<multiset<ll, greater<>>> best_branches;
    vector<lazy_segtree> segtrees;
    multiset<ll, greater<>> centroid_ans;

    CD(int n) : adj(n), size(n), vis(n), pars(n), in(n), out(n), orig(n), best_branches(n), segtrees(n) {}

    void add_edge(int u, int v, ll w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int dfs_size(int v, int p) {
        size[v] = 1;
        for (auto [e, _] : adj[v]) {
            if (e != p && !vis[e]) {
                size[v] += dfs_size(e, v);
            }
        }
        return size[v];
    }

    int dfs_root(int v, int p, int n) {
        for (auto [e, _] : adj[v]) {
            if (e != p && !vis[e] && 2 * size[e] > n) {
                return dfs_root(e, v, n);
            }
        }
        return v;
    }

    void dfs_build(int v, int p, int c, int orig, int &t, ll up_w) {
        auto idx = in[c][v] = t++;
        pars[v].push_back(c);
        this->orig[c][idx] = orig;
        for (auto [e, w] : adj[v]) {
            if (!vis[e] && e != p) {
                dfs_build(e, v, c, orig, t, w);
            }
        }
        out[c][idx] = t;
        segtrees[c].upd(idx, t, up_w);

        // if we are the start of a branch, add ourself to best branches set
        if (v == orig) {
            best_branches[c].insert(segtrees[c].qry(idx, t));
        }
    }

    void build(int c, int size) {
        out[c].resize(size);
        orig[c].resize(size);
        segtrees[c] = lazy_segtree(size);

        int t = 0;
        in[c][c] = t++;
        pars[c].push_back(c);
        orig[c][0] = -1;
        for (auto [e, w] : adj[c]) {
            if (!vis[e]) {
                dfs_build(e, c, c, e, t, w);
            }
        }
        out[c][0] = t;

        centroid_ans.insert(get_ans(c));
    }

    ll get_ans(int c) {
        if (sz(best_branches[c]) == 0) {
            return 0;
        } else if (sz(best_branches[c]) == 1) {
            return *begin(best_branches[c]);
        } else {
            return *begin(best_branches[c]) + *next(begin(best_branches[c]));
        }
    }

    void centroid(int v, int p) {
        int comp_size = dfs_size(v, p);
        int c = dfs_root(v, p, size[v]);
        build(c, comp_size);

        vis[c] = true;
        for (auto [e, _] : adj[c]) {
            if (!vis[e]) {
                centroid(e, c);
            }
        }
    }

    void upd_in_c(int c, int u, int v, ll diff) {
        int in_idx = max(in[c][u], in[c][v]);
        int out_idx = out[c][in_idx];
        int orig = this->orig[c][in_idx];
        int orig_in = in[c][orig];
        int orig_out = out[c][orig_in];

        centroid_ans.erase(centroid_ans.find(get_ans(c)));
        best_branches[c].erase(best_branches[c].find(segtrees[c].qry(orig_in, orig_out)));
        segtrees[c].upd(in_idx, out_idx, diff);
        best_branches[c].insert(segtrees[c].qry(orig_in, orig_out));
        centroid_ans.insert(get_ans(c));
    }

    void upd_weight(int u, int v, ll diff) {
        for (auto c : pars[u]) {
            if (in[c].count(v)) {
                upd_in_c(c, u, v, diff);
            }
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    ll W;
    cin >> n >> q >> W;

    CD tree(n);
    vector<array<ll, 3>> edges;
    rep(i, 0, n-1) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--;
        v--;
        tree.add_edge(u, v, w);
        edges.push_back({u, v, w});
    }

    tree.centroid(0, 0);

    ll last = 0;
    while (q--) {
        ll dp, ep;
        cin >> dp >> ep;

        auto idx = (dp + last) % (n - 1);
        auto [u, v, cur_w] = edges[idx];
        auto new_w = (ep + last) % W;
        tree.upd_weight(u, v, new_w - cur_w);
        edges[idx][2] = new_w;

        last = *begin(tree.centroid_ans);
        cout << last << '\n';
    }

    return 0;
}

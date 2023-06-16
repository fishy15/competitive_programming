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
    int t;

    tree(int n) : adj(n), par(n), sz(n), in(n), head(n), d(n), t(0) {}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void dfs_size(int v, int p) {
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

    void dfs_hld(int v, int p) {
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
        op(in[x], in[y]); // if vals in edges, add 1 to in[x] to exclude parent edge
    }

    void op_subtree(int x, function<void(int,int)> op) {
        op(in[x], in[x] + sz[x] - 1); // if vals in edges, add 1 to in[x] to exclude parent edge
    }
};

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

struct segtree {
    int n;
    vector<mi> st;

    segtree(int n) : n(n), st(4 * n) {}

    void upd(int x, mi q) { upd(1, 0, n - 1, x, q); }
    void upd(int v, int l, int r, int x, mi q) {
        if (l == r) {
            st[v] = q;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(2 * v, l, m, x, q);
            } else {
                upd(2 * v + 1, m + 1, r, x, q);
            }
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    mi qry(int x, int y) { return qry(1, 0, n - 1, x, y); }
    mi qry(int v, int l, int r, int x, int y) {
        if (r < x || l > y) {
            return 0;
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return qry(2 * v, l, m, x, y) + qry(2 * v + 1, m + 1, r, x, y);
        }
    }
};

void solve() {
    int n; cin >> n;

    tree t(n);
    segtree st(n);

    for (int i = 0; i < n - 1; i++) {
        int p; cin >> p; p--;
        t.add_edge(p, i + 1);
    }

    vector<pair<int, int>> rating(n);
    for (int i = 0; i < n; i++) {
        cin >> rating[i].first;
        rating[i].second = i;
    }

    sort(rating.rbegin(), rating.rend());

    t.dfs_size(0, 0);
    t.dfs_hld(0, 0);

    for (auto [r, v] : rating) {
        mi cur = 0;
        t.op_path(0, v, [&](int x, int y) { cur += st.qry(x, y); });
        t.op_subtree(v, [&](int x, int y) { cur += st.qry(x, y); });
        cur += 1;
        st.upd(t.in[v], cur);
    }

    mi ans = 0;
    t.op_subtree(0, [&](int x, int y) { ans += st.qry(x, y); });
    ans -= n;
    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

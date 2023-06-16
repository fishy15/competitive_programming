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

struct M {
    const static int n = 2;
    mi m[n][n]; 
    M operator*(const M &m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    res[i][j] += m[i][a] * m2[a][j];
                }
            }
        }
        return res;
    }
    mi *operator[](const int x) { return m[x]; }
    const mi *operator[](const int x) const { return m[x]; }
    static M pow(M m, ll e) {
        M res = I();
        while (e > 0) {
            if (e & 1) res = res * m;
            m = m * m;
            e >>= 1;
        }
        return res;
    }
    static M I() {
        M m;
        for (int i = 0; i < n; i++) m[i][i] = 1;
        return m;
    }
};

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

struct sparse_table {
    int n;
    vector<vector<M>> st;

    sparse_table(vector<M> v) : n(v.size()) {
        st = vector<vector<M>>(20, vector<M>(n)); 
        st[0] = v;

        for (int p = 1; p < 20; p++) {
            for (int i = 0; i + (1 << p) <= n; i++) {
                st[p][i] = st[p - 1][i] * st[p][i + (1 << (p - 1))];
            }
        }
    }

    M qry(int l, int r) {
        M res = M::I();
        for (int i = 19; i >= 0; i--) {
            if ((1 << i) <= r - l + 1) {
                res = res * st[i][l];
                l += 1 << i;
            }
        }
        return res;
    }
};

struct tree {
    vector<vector<int>> adj;
    vector<int> par;
    vector<int> sz;
    vector<int> in;
    vector<int> out;
    vector<int> head;
    vector<int> d;
    vector<array<int, 20>> up;
    int t;

    tree(int n) : adj(n), par(n), sz(n), in(n), out(n), head(n), d(n), up(n, array<int, 20>()), t(0) {}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
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
        up[v][0] = p;

        for (int i = 1; i < 20; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

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
        out[v] = t;
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

    bool anc(int a, int b) {
        return in[a] <= in[b] && out[b] <= out[a];
    }

    int lca(int a, int b) {
        if (anc(a, b)) return a;
        if (anc(b, a)) return b;
        return par[one_below(a, b)];
    }

    int one_below(int a, int b) {
        for (int i = 19; i >= 0; i--) {
            if (!anc(up[a][i], b)) a = up[a][i];
        }
        return a;
    }
};

void pr(M m) {
    cout << m[0][0].v << ' ' << m[0][1].v << ' ' << m[1][0].v << ' ' << m[1][1].v << '\n';
}

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<int>> adj(n);
    vector<M> prob(n);

    mi div = mi(1000000).inv();
    int k; cin >> k;
    prob[0][0][0] = div * k;
    prob[0][1][1] = prob[0][0][0] * -1;

    tree t(n);
    for (int i = 1; i < n; i++) {
        int p, a, b; cin >> p >> a >> b;
        mi p1 = div * a;
        mi q1 = p1 * -1;
        mi p2 = div * b;
        mi q2 = p2 * -1;

        prob[i][0][0] = p1;
        prob[i][1][0] = q1;
        prob[i][0][1] = p2;
        prob[i][1][1] = q2;

        p--;
        t.add_edge(p, i);
    }

    t.dfs_size(0, 0);
    t.dfs_hld(0, 0);

    vector<M> before(n);
    for (int i = 0; i < n; i++) {
        before[t.in[i]] = prob[i];
    }
    sparse_table st(before);

    while (q--) {
        int u, v; cin >> u >> v;
        u--; v--;

        bool upup = false;
        if (t.anc(u, v)) {
            upup = true;
        } else if (t.anc(v, u)) {
            swap(u, v);
            upup = true;
        }

        if (upup) {
            M path_u = M::I();
            t.op_path(0, u, [&](int x, int y) { path_u = path_u * st.qry(x, y); });

            M path_v = M::I();
            t.op_path(t.one_below(u, v), v, [&](int x, int y) { path_v = path_v * st.qry(x, y); });

            mi ans = path_u[0][0] * path_v[0][0];
            cout << ans.v << '\n';
        } else {
            int l = t.lca(u, v);

            M path_u = M::I();
            t.op_path(l, u, [&](int x, int y) { path_u = path_u * st.qry(x, y); });

            M path_v = M::I();
            t.op_path(l, v, [&](int x, int y) { path_v = path_v * st.qry(x, y); });

            M to_lca = M::I();
            t.op_path(0, t.par[l], [&](int x, int y) { to_lca = to_lca * st.qry(x, y); });

            /* pr(to_lca); */
            /* pr(path_u); */
            /* pr(path_v); */

            /* mi ans = to_lca[0][0] * (path_u[0][0] * path_v[0][0]) */ 
            /*     + to_lca[1][1] * (path_u[1][0] * path_v[1][0]); */
            /* cout << ans.v << '\n'; */
        }
    }
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

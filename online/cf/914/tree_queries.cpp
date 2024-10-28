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

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(std::forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), std::forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(std::forward<F>(f));
}

struct lazy_segtree {
    int n;
    mutable vector<ll> st;
    mutable vector<ll> lazy;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) {}
    lazy_segtree(int n, vector<int> &nums) : lazy_segtree(n) { build(1, 0, n, nums); }
    void build(int v, int l, int r, const vector<int> &nums) {
        if (l + 1 == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m, r, nums);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) const {
        if (l + 1 != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, int q) { upd(x, y, q, 1, 0, n); }
    void upd(int x, int y, int q, int v, int l, int r) {
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
        if (r <= x || l >= y) return -INFLL;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m, r));
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector adj(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<pair<int, vector<int>>>> queries_at(n);
    for (int i = 0; i < q; i++) {
        int x, k;
        cin >> x >> k;
        x--;

        vector<int> others(k);
        for (auto &y : others) {
            cin >> y;
            y--;
        }

        queries_at[x].push_back({i, others});
    }

    vector<int> d(n);
    vector<int> in(n);
    vector<int> out(n);
    vector<array<int, 20>> up(n);
    int t = 0;

    auto dfs_d = y_combinator([&](auto self, int v, int p) -> void {
        in[v] = t++;
        up[v][0] = p;
        for (int i = 1; i < 19; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        for (auto e : adj[v]) {
            if (e != p) {
                d[e] = d[v] + 1;
                self(e, v);
            }
        }
        out[v] = t++;
    });
    dfs_d(0, 0);

    auto anc = [&](int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    };
    
    // one step from u to v, u is ancestor of v
    auto one_step = [&](int u, int v) {
        for (int i = 19; i >= 0; i--) {
            if (!anc(up[v][i], u)) {
                v = up[v][i];
            }
        }
        return v;
    };

    vector<int> d2(2 * n);
    for (int i = 0; i < n; i++) {
        d2[in[i]] = d[i];
    }

    lazy_segtree st(2 * n, d2);

    // from u to v
    auto reroot = [&](int u, int v) {
        if (up[v][0] == u) {
            st.upd(0, in[v], +1);
            st.upd(in[v], out[v] + 1, -1);
            st.upd(out[v] + 1, 2 * n, +1);
        } else {
            st.upd(0, in[u], -1);
            st.upd(in[u], out[u] + 1, +1);
            st.upd(out[u] + 1, 2 * n, -1);
        }
    };

    vector<int> ans(q);
    auto solve = y_combinator([&](auto self, int v, int p) -> void {
        for (const auto &[idx, other] : queries_at[v]) {
            for (auto y : other) {
                if (anc(y, v)) {
                    auto v2 = one_step(y, v);
                    // delete everything outside of subtree
                    st.upd(0, in[v2], -n);
                    st.upd(out[v2] + 1, 2 * n, -n);
                } else {
                    // delete only within subtree
                    st.upd(in[y], out[y] + 1, -n);
                }
            }

            ans[idx] = st.qry(0, 2 * n);

            for (auto y : other) {
                if (anc(y, v)) {
                    auto v2 = one_step(y, v);
                    st.upd(0, in[v2], +n);
                    st.upd(out[v2] + 1, 2 * n, +n);
                } else {
                    st.upd(in[y], out[y] + 1, +n);
                }
            }
        }

        for (auto e : adj[v]) {
            if (e != p) {
                reroot(v, e);
                self(e, v);
                reroot(e, v);
            }
        }

    });

    solve(0, 0);

    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}

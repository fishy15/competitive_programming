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

struct node {
    int ans, pre, suf, sum;
    node() : ans(0), pre(0), suf(0), sum(0) {}
    node(int x) : ans(x), pre(max(x, 0)), suf(max(x, 0)), sum(x) {}
    node(int a, int b, int c, int d) : ans(a), pre(b), suf(c), sum(d) {}
};

node comb(const node &a, const node &b) {
    return {
        max({a.ans, b.ans, a.suf + b.pre}),
        max(a.pre, a.sum + b.pre),
        max(a.suf + b.sum, b.suf),
        a.sum + b.sum,
    };
}

template<typename T, typename F>
struct segtree {
    int n;
    vector<T> st;
    F op;
    T id;
    segtree(int n, F op, T id) : n(n), st(2 * n, id), op(op), id(id) {}
    segtree(vector<T> &nums, F op, T id) : segtree(sz(nums), op, id) {
        copy(all(nums), begin(st) + n);
        for (int i = n-1; i >= 0; i--) {
            st[i] = op(st[i<<1], st[i<<1|1]);
        }
    }
    void upd(int x, T y) {
        for (x += n, st[x] = y; x >>= 1;) {
            st[x] = op(st[x<<1], st[x<<1|1]);
        }
    }
    T qry(int l, int r) const {
        T ans_l = id, ans_r = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans_l = op(ans_l, st[l++]);
            if (r & 1) ans_r = op(st[--r], ans_r);
        }
        return op(ans_l, ans_r);
    }
};

struct rms_segtree {
    int n;
    vector<int> st;
    rms_segtree(int n) : n(n), st(4 * n) {}
    void upd(int x, int y, int val) { upd(1, 0, n, x, y, val); }
    void upd(int v, int l, int r, int x, int y, int val) {
        if (r <= x || y <= l) return;
        if (x <= l && r <= y) { st[v] = max(st[v], val); return; }
        int m = (l + r) / 2;
        upd(2 * v, l, m, x, y, val);
        upd(2 * v + 1, m, r, x, y, val);
    }
    int qry(int x) const { return qry(1, 0, n, x); }
    int qry(int v, int l, int r, int x) const {
        if (l + 1 == r) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                return max(st[v], qry(2 * v, l, m, x));
            } else {
                return max(st[v], qry(2 * v + 1, m, r, x));
            }
        }
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    vector<vector<int>> init(n);
    vector<vector<array<int, 3>>> upds(n);

    rep(i, 0, n) {
        cin >> a[i];
        a[i]--;
        init[a[i]].push_back(i);
    }

    rep(t, 0, q) {
        int i, x;
        cin >> i >> x;
        i--;
        x--;
        if (a[i] != x) {
            upds[a[i]].push_back({t, i, -1});
            a[i] = x;
            upds[a[i]].push_back({t, i, +1});
        }
    }

    rms_segtree ans(q);
    vector all_neg(n, node{-1});
    segtree st(all_neg, &comb, node{});
    rep(i, 0, n) {
        set<int> cur;
        for (auto x : init[i]) {
            cur.insert(x);
            st.upd(x, node{1});
        }

        int init_end = upds[i].empty() ? q : upds[i][0][0];
        ans.upd(0, init_end, st.qry(0, n).ans);

        rep(j, 0, sz(upds[i])) {
            auto [t, idx, typ] = upds[i][j];
            st.upd(idx, node{typ});

            auto nxt = (j + 1 == sz(upds[i])) ? q : upds[i][j + 1][0];
            ans.upd(t, nxt, st.qry(0, n).ans);

            if (typ == +1) {
                cur.insert(idx);
            } else {
                cur.erase(idx);
            }
        }

        // reset
        for (auto x : cur) {
            st.upd(x, node{-1});
        }
    }

    rep(i, 0, q) {
        cout << ans.qry(i) / 2 << ' ';
    }
    cout << '\n';
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

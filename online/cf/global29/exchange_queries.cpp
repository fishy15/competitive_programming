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
    int min_val;
    int left, right;
    ll within_pairs;
};

ll choose2(ll n) {
    return n * (n - 1) / 2;
}

node comb(const node &a, const node &b) {
    if (a.min_val < b.min_val) {
        return a;
    } else if (a.min_val > b.min_val) {
        return b;
    } else {
        return {
            a.min_val,
            a.left,
            b.right,
            a.within_pairs + b.within_pairs + choose2(b.left - a.right),
        };
    }
}

struct lazy_segtree {
    int n;
    mutable vector<node> st;
    mutable vector<int> lazy;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) { build(1, 0, n); }
    void build(int v, int l, int r) {
        if (r - l == 1) {
            st[v] = {
                0,
                l,
                l,
                0
            };
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m, r);
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) const {
        if (r - l != 1) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v].min_val += lazy[v];
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
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }
    ll qry(int x, int y) const { 
        auto res = qry(x, y, 1, 0, n);
        return res.within_pairs + choose2(res.left - x + 1) + choose2(y - res.right - 1);
    }
    node qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r <= x || l >= y) return node{INF, 0, 0, 0};
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return comb(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m, r));
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> p(n), inv_p(n), s(n), inv_s(n);
    rep(i, 0, n) {
        cin >> p[i];
        p[i]--;
        inv_p[p[i]] = i;
    }
    rep(i, 0, n) {
        cin >> s[i];
        s[i]--;
        inv_s[s[i]] = i;
    }

    // compose s p^-1
    vector<int> ord(n);
    rep(i, 0, n) {
        ord[i] = s[inv_p[i]];
    }

    lazy_segtree st(n);
    auto set_val = [&](int x, int v, int delta) {
        if (x < v) {
            st.upd(x, v, delta);
        }
    };

    auto swap_st = [&](int x, int y) {
        set_val(x, ord[x], -1);
        set_val(y, ord[y], -1);
        swap(ord[x], ord[y]);
        set_val(x, ord[x], +1);
        set_val(y, ord[y], +1);
    };

    rep(i, 0, n) {
        set_val(i, ord[i], +1);
    }

    while (q--) {
        int t, i, j;
        cin >> t >> i >> j;
        i--;
        j--;

        if (t == 1) {
            swap_st(p[i], p[j]);
            swap(inv_p[p[i]], inv_p[p[j]]);
            swap(p[i], p[j]);
        } else {
            swap_st(p[i], p[j]);
            swap(inv_s[s[i]], inv_s[s[j]]);
            swap(s[i], s[j]);
        }

        auto ans = st.qry(0, n) + n + choose2(n);
        cout << ans << '\n';
    }
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

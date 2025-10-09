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

struct node_state {
    pair<ll, ll> min_ops_left;
    ll resets;
    ll one_count;

    static node_state I() {
        return node_state {
            {INFLL, -1}, 0, 0
        };
    }
};

struct lazy_state {
    ll to_decrease;
    ll ops;

    static lazy_state I() {
        return lazy_state {
            0, 0
        };
    }
};

node_state comb(const node_state &a, const node_state &b) {
    return {
        min(a.min_ops_left, b.min_ops_left),
        a.resets + b.resets,
        a.one_count + b.one_count,
    };
}

lazy_state comb(const lazy_state &a, const lazy_state &b) {
    return {
        a.to_decrease + b.to_decrease,
        a.ops + b.ops,
    };
}

node_state comb(const node_state &a, const lazy_state &b) {
    return {
        {a.min_ops_left.first - b.to_decrease, a.min_ops_left.second},
        a.resets + (a.one_count * b.ops),
        a.one_count,
    };
}

struct lazy_segtree {
    int n;
    mutable vector<node_state> st;
    // amt to decrease, how many operations is it
    mutable vector<lazy_state> lazy;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) {}
    lazy_segtree(int n, vector<node_state> &nums) : lazy_segtree(n) { build(1, 0, n, nums); }
    void build(int v, int l, int r, const vector<node_state> &nums) {
        if (r - l == 1) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m, r, nums);
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) const {
        if (r - l > 1) {
            lazy[2 * v] = comb(lazy[2 * v], lazy[v]);
            lazy[2 * v + 1] = comb(lazy[2 * v + 1], lazy[v]);
        }
        st[v] = comb(st[v], lazy[v]);
        lazy[v] = lazy_state::I();
    }
    void upd(int x, int y, lazy_state q) { upd(x, y, q, 1, 0, n); }
    void upd(int x, int y, lazy_state q, int v, int l, int r) {
        push(v, l, r);
        if (r <= x || l >= y) return;
        if (x <= l && r <= y) {
            lazy[v] = comb(lazy[v], q);
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m, r);
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }
    void set(int x, ll q) { set(x, q, 1, 0, n); }
    void set(int x, ll q, int v, int l, int r) {
        push(v, l, r);
        if (x < l || x >= r) return;
        if (r - l == 1) {
            if (q == 1) {
                st[v].min_ops_left.first = INFLL;
                st[v].one_count++;
            } else {
                st[v].min_ops_left.first = q;
            }
            st[v].resets++;
        } else {
            int m = (l + r) / 2;
            set(x, q, 2 * v, l, m);
            set(x, q, 2 * v + 1, m, r);
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }
    node_state qry(int x, int y) const { return qry(x, y, 1, 0, n); }
    node_state qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r <= x || l >= y) return node_state::I();
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return comb(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m, r));
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> p(n);
    vector<int> resets_done(n);
    vector<node_state> init;
    rep(i, 0, n) {
        cin >> p[i];
        if (p[i] == 1) {
            init.push_back(node_state { {INFLL, i},  0, 1 });
        } else {
            init.push_back(node_state { {p[i], i},  0, 0 });
        }
    }

    lazy_segtree st(n, init);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            l--;

            st.upd(l, r, lazy_state { k, 1 });

            auto cur = st.qry(l, r);
            while (cur.min_ops_left.first <= 0) {
                auto idx = cur.min_ops_left.second;  
                p[idx] = max(p[idx] / 2, 1);
                resets_done[idx]++;
                st.set(idx, p[idx]);
                cur = st.qry(l, r);
            }
        } else {
            int l, r;
            cin >> l >> r;
            l--;

            auto ans = st.qry(l, r);
            cout << ans.resets << '\n';
        }
    }

    return 0;
}

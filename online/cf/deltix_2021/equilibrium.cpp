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
#define MAXN 100010

using namespace std;

struct val {
    ll tt, td, dt, dd;
    val() : tt{}, td{}, dt{}, dd{} {}

    val operator+(val v2) const {
        val v1 = *this;
        val res;

        {
            ll new_td_1 = min(v1.td, v2.td);
            v1.td -= new_td_1;
            v2.td -= new_td_1; 

            ll new_td_2 = min(v1.tt, v2.dd);
            v1.tt -= new_td_2;
            v2.dd -= new_td_2;

            res.td = new_td_1 + new_td_2;
        }

        {
            ll new_tt_1 = min(v1.tt, v2.dt);
            v1.tt -= new_tt_1;
            v2.dt -= new_tt_1;

            ll new_tt_2 = min(v1.td, v2.tt);
            v1.td -= new_tt_2;
            v2.tt -= new_tt_2;

            res.tt = new_tt_1 + new_tt_2;
        }

        {
            ll new_dt_1 = min(v1.dd, v2.tt);
            v1.dd -= new_dt_1;
            v2.tt -= new_dt_1;

            ll new_dt_2 = min(v1.dt, v2.dt);
            v1.dt -= new_dt_2;
            v2.dt -= new_dt_2;

            res.dt = new_dt_1 + new_dt_2;
        }

        {
            ll new_dd_1 = min(v1.dt, v2.dd);
            v1.dt -= new_dd_1;
            v2.dd -= new_dd_1;

            ll new_dd_2 = min(v1.dd, v2.td);
            v1.dd -= new_dd_2;
            v2.td -= new_dd_2;

            res.dd = new_dd_1 + new_dd_2;
        }

        res.tt += v1.tt;
        res.td += v1.td;
        res.dt += v1.dt;
        res.dd += v1.dd;

        res.tt += v2.tt;
        res.td += v2.td;
        res.dt += v2.dt;
        res.dd += v2.dd;

        return res;
    }
};

struct segtree {
    int n;
    vector<val> st;

    segtree(int n) : n(n), st(4 * n) {}

    void upd(int x, val q) { upd(1, 0, n - 1, x, q); }
    void upd(int v, int l, int r, int x, val q) {
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

    val qry(int x, int y) { return qry(1, 0, n - 1, x, y); }
    val qry(int v, int l, int r, int x, int y) {
        if (r < x || l > y) {
            return val{};
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return qry(2 * v, l, m, x, y) + qry(2 * v + 1, m + 1, r, x, y);
        }
    }
};

int n, q;
int nums[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums[i] -= x;
    }

    segtree st(n);

    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            val v;
            v.dd = nums[i];
            st.upd(i, v);
        } else if (nums[i] < 0) {
            val v;
            v.tt = -nums[i];
            st.upd(i, v);
        }
    }

    while (q--) {
        int l, r; cin >> l >> r;
        auto v = st.qry(l - 1, r - 1);

        if (v.tt == 0 && v.dt == 0 && v.dd == 0) {
            cout << v.td << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}

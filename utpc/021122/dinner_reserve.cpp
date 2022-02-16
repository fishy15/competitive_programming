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

struct tr {
    array<int, 60> t{};
    bool empty = true;

    tr operator+(const tr &t2) const {
        if (empty) return t2;
        if (t2.empty) return *this;

        tr res;
        res.empty = false;
        for (int i = 0; i < 60; i++) {
            int tt = t[i];
            res.t[i] = tt + t2.t[(tt + i) % 60];
        }
        return res;
    }

    void init(int k) {
        empty = false;
        t.fill(1);
        for (int i = 0; i < 60; i += k) {
            t[i]++;
        }
    }
};

struct segtree {
    int n;
    vector<tr> st;

    segtree(int n, vector<int> &a) : n(n), st(4 * n) {
        build(1, 0, n, a);
    }

    void build(int v, int l, int r, vector<int> &a) {
        if (l + 1 == r) {
            st[v].init(a[l]);
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m, r, a);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    void upd(int x, int y) {
        upd(1, 0, n, x, y);
    }

    void upd(int v, int l, int r, int x, int y) {
        if (l + 1 == r) {
            st[v].init(y);
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2 * v, l, m, x, y);
            } else {
                upd(2 * v + 1, m, r, x, y);
            }
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    int qry(int x, int y, int t) {
        auto val = qry(1, 0, n, x, y);
        return val.t[t % 60];
    }

    tr qry(int v, int l, int r, int x, int y) {
        if (x <= l && r <= y) {
            return st[v];
        } else if (r <= x || l >= y) {
            return tr{};
        } else {
            int m = (l + r) / 2;
            return qry(2 * v, l, m, x, y) + qry(2 * v + 1, m, r, x, y);
        }
    }
};

int n;
vector<int> a;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.push_back(x);
    }

    segtree st(n, a);

    int q; cin >> q;
    while (q--) {
        int w; cin >> w;
        if (w == 1) {
            int x, y, t; cin >> x >> y >> t;
            x--; y--;
            cout << st.qry(x, y, t) << '\n';
        } else {
            int s, b; cin >> s >> b;
            s--;
            st.upd(s, b);
        }
    }

    return 0;
}

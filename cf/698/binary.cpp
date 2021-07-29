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

struct lazy_segtree {
    int n;
    vector<int> st;
    vector<int> lazy;
    vector<int> to_set;
    lazy_segtree(int n) : n(n) {
        st.resize(4 * n);
        lazy.resize(4 * n);
        to_set.resize(4 * n);
    }
    void push(int v, int l, int r) {
        if (!to_set[v]) return;
        if (l != r) {
            lazy[2 * v] = lazy[v];
            to_set[2 * v] = true;
            lazy[2 * v + 1] = lazy[v];
            to_set[2 * v + 1] = true;
        }
        st[v] = (r - l + 1) * lazy[v];
        lazy[v] = 0;
        to_set[v] = false;
    }
    void build(int v, int l, int r, vector<int> &vec) {
        if (l == r) {
            st[v] = vec[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, vec);
            build(2 * v + 1, m + 1, r, vec);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }
    void upd(int x, int y, int q) { upd(x, y, q, 1, 0, n - 1); }
    void upd(int x, int y, int q, int v, int l, int r) {
        push(v, l, r);
        if (r < x || y < l) return;
        if (x <= l && r <= y) {
            lazy[v] = q;
            to_set[v] = true;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }
    int qry(int x, int y) { return qry(x, y, 1, 0, n - 1); }
    int qry(int x, int y, int v, int l, int r) {
        push(v, l, r);
        if (r < x || y < l) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return qry(x, y, 2 * v, l, m) + qry(x, y, 2 * v + 1, m + 1, r);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    string a, b; cin >> a >> b;
    vector<array<int, 2>> qry(q);
    for (int i = 0; i < q; i++) {
        cin >> qry[i][0] >> qry[i][1];
        qry[i][0]--; qry[i][1]--;
    }

    lazy_segtree st(n);
    for (int i = 0; i < n; i++) {
        st.upd(i, i, b[i] - '0');
    }

    for (int i = q - 1; i >= 0; i--) {
        auto [l, r] = qry[i];
        int tot = st.qry(l, r);
        int sz = r - l + 1;
        if (2 * tot < sz) {
            st.upd(l, r, 0);
        } else if (2 * (sz - tot) < sz) {
            st.upd(l, r, 1);
        } else {
            cout << "NO\n";
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i] - '0' != st.qry(i, i)) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

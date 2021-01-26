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
#define MAXN 1000010

using namespace std;

const int maxn = 1000000;
struct lazy_segtree {
    int st[4 * MAXN];
    int lazy[4 * MAXN];
    void build(int v, int l, int r) {
        if (l == r) {
            st[v] = 0;
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m + 1, r);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, int q, int v = 1, int l = 0, int r = maxn) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y, int v = 1, int l = 0, int r = maxn) {
        push(v, l, r);
        if (r < x || l > y) return INF;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return min(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
    int search(int v, int l, int r) {
        push(v, l, r);
        if (l == r) {
            if (st[v] < 0) {
                return l;
            } else {
                return -1;
            }
        } else {
            int m = (l + r) / 2;
            push(2 * v, l, m);
            push(2 * v + 1, m + 1, r);
            if (st[2 * v + 1] < 0) {
                return search(2 * v + 1, m + 1, r);
            } else {
                return search(2 * v, l, m);
            }
        }
    }
};

int n, m;
int a[300010];
int b[300010];
lazy_segtree st;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    st.build(1, 0, maxn);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        st.upd(0, a[i], -1);
    }

    for (int i = 0; i < m; i++) {
        cin >> b[i];
        st.upd(0, b[i], 1);
    }

    int q; cin >> q;
    while (q--) {
        int t, i, x; cin >> t >> i >> x;
        i--;
        if (t == 1) {
            st.upd(0, a[i], 1);
            a[i] = x;
            st.upd(0, a[i], -1);
        } else {
            st.upd(0, b[i], -1);
            b[i] = x;
            st.upd(0, b[i], 1);
        }
        cout << st.search(1, 0, maxn) << '\n';
    }

    return 0;
}

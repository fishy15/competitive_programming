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

struct segtree {
    int n;
    vector<ll> st;

    segtree(int n, vector<int> &arr, bool add) : n(n) {
        st.resize(4 * n);
        build(1, 0, n - 1, arr, add);
    }

    void build(int v, int l, int r, const vector<int> &arr, bool add) {
        if (l == r) {
            st[v] = arr[l] + (add ? l : -l);
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, arr, add);
            build(2 * v + 1, m + 1, r, arr, add);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }

    void upd(int x, int y) { upd(1, x, y, 0, n - 1); }
    void upd(int v, int x, int y, int l, int r) {
        if (l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(2 * v, x, y, l, m);
            } else {
                upd(2 * v + 1, x, y, m + 1, r);
            }
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }

    ll qry(int x, int y) const { return qry(1, x, y, 0, n - 1); }
    ll qry(int v, int x, int y, int l, int r) const {
        if (y < l || x > r) {
            return INFLL;
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return min(qry(2 * v, x, y, l, m), qry(2 * v + 1, x, y, m + 1, r));
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    segtree low(n, nums, false);
    segtree high(n, nums, true);

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int k, x; cin >> k >> x;
            k--;
            low.upd(k, x - k);
            high.upd(k, x + k);
        } else {
            int k; cin >> k;
            k--;
            /* cout << low.qry(0, k) + k << ' ' << high.qry(k, n - 1) - k << '\n'; */
            cout << min(low.qry(0, k) + k, high.qry(k, n - 1) - k) << '\n';
        }
    }

    return 0;
}

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

struct node {
    ll ans;
    ll left_len;
    ll right_len;
    int l, r;
    int len;

    node() : node(-1) {}
    node(int x) : ans(1), left_len(1), right_len(1), l(x), r(x), len(1) {}

    node operator+(const node &n) const {
        if (l == -1) return n;
        if (n.l == -1) return *this;

        node res;
        res.l = l;
        res.r = n.r;
        res.len = len + n.len;
        res.ans = ans + n.ans;
        res.left_len = left_len;
        res.right_len = n.right_len;

        if (r <= n.l) {
            res.ans += right_len * n.left_len;

            // extend if possible
            if (left_len == len) {
                res.left_len += n.left_len;
            }

            if (n.right_len == n.len) {
                res.right_len += right_len;
            }
        }

        return res;
    }
};

struct segtree {
    int n;
    vector<node> st;

    segtree(int n, int* nums) : n(n), st(4 * n) {
        build(1, 0, n - 1, nums);
    }

    void build(int v, int l, int r, int* nums) {
        if (l == r) {
            st[v] = node(nums[l]);
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m + 1, r, nums);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    void upd(int x, int q) { upd(1, 0, n - 1, x, q); }
    void upd(int v, int l, int r, int x, int q) {
        if (l == r) {
            st[v] = node(q);
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

    node qry(int x, int y) { return qry(1, 0, n - 1, x, y); }
    node qry(int v, int l, int r, int x, int y) {
        if (r < x || l > y) {
            return node();
        } else if (x <= l && r <= y) {
            /* cout << l << ' ' << r << ' ' << st[v].ans << '\n'; */
            return st[v];
        } else {
            int m = (l + r) / 2;
            auto v2 = qry(2 * v, l, m, x, y) + qry(2 * v + 1, m + 1, r, x, y);
            /* cout << l << ' ' << r << ' ' << v2.ans << '\n'; */
            return v2;
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
    
    segtree st(n, nums);
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x, y; cin >> x >> y;
            st.upd(x - 1, y);
        } else {
            int l, r; cin >> l >> r;
            cout << st.qry(l - 1, r - 1).ans << '\n';
        }
    }

    return 0;
}

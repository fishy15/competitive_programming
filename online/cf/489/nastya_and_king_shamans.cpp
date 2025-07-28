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

struct lazy_segtree {
    int n;
    mutable vector<ll> st;
    mutable vector<ll> lazy;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) {}
    void push(int v, int l, int r) const {
        if (r - l != 1) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, ll q) { upd(x, y, q, 1, 0, n); }
    void upd(int x, int y, ll q, int v, int l, int r) {
        push(v, l, r);
        if (r <= x || l >= y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m, r);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    int find_zero() const { return find_zero(1, 0, n); }
    int find_zero(int v, int l, int r) const {
        push(v, l, r);
        if (st[v] > 0) {
            return -1;
        } else if (r - l == 1) {
            return st[v] == 0 ? l : -1;
        } else {
            int m = (l + r) / 2;
            auto left_ans = find_zero(2*v, l, m);
            return left_ans == -1 ? find_zero(2*v+1, m, r) : left_ans;
        }
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<ll> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    lazy_segtree st(n);

    auto adjust = [&](int x, ll v) {
        st.upd(x, x+1, -v);
        st.upd(x+1, n, v);
    };

    rep(i, 0, n) {
        adjust(i, nums[i]);
    }

    while (q--) {
        int x, v;
        cin >> x >> v;
        x--;

        adjust(x, -nums[x]);
        nums[x] = v;
        adjust(x, nums[x]);

        auto ans = st.find_zero();
        if (ans == -1) {
            cout << "-1\n";
        } else {
            cout << ans+1 << '\n';
        }
    }

    return 0;
}

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

struct info {
    pair<int, int> low;
    pair<int, int> high;

    info() : info({-1, INF}, {-1, -1}) {}
    info(int idx, int val) : low{val, idx}, high{val, idx} {}
    info(pair<int, int> l, pair<int, int> h) : low(l), high(h) {}

    info operator+(const info &other) const {
        return {min(low, other.low), max(high, other.high)};
    }

    info &operator*=(int mul) {
        if (mul == -1) {
            swap(low, high);
            low.first = MOD - low.first;
            high.first = MOD - high.first;
        }
        return *this;
    }
};

struct lazy_segtree {
    int n;
    mutable vector<info> st;
    mutable vector<int> lazy;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n, 1) {}
    lazy_segtree(int n, vector<int> &nums) : lazy_segtree(n) { build(1, 0, n - 1, nums); }
    void build(int v, int l, int r, const vector<int> &nums) {
        if (l == r) {
            st[v] = info(l, nums[l]);
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m + 1, r, nums);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }
    void push(int v, int l, int r) const {
        if (l != r) {
            lazy[2 * v] *= lazy[v];
            lazy[2 * v + 1] *= lazy[v];
        }
        st[v] *= lazy[v];
        lazy[v] = 1;
    }
    void upd(int x, int y, int q) { upd(x, y, q, 1, 0, n - 1); }
    void upd(int x, int y, int q, int v, int l, int r) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] *= q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }
    int qry(int x, int y) const { return qry(x, y, 1, 0, n - 1).high.second; }
    info qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r < x || l > y) return info{};
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return qry(x, y, 2 * v, l, m) + qry(x, y, 2 * v + 1, m + 1, r);
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) cin >> x;

    lazy_segtree st(n, nums);

    int q;
    cin >> q;
    ll ans = 0;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        st.upd(l, r, -1);
        ans += st.qry(0, n - 1) + 1;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

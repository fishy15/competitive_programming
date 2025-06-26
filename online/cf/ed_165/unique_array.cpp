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

// lazy segtree (range add update, range min query)
struct lazy_segtree {
    int n;
    mutable vector<pair<int, int>> st;
    mutable vector<int> lazy;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) { build(1, 0, n); }
    void build(int v, int l, int r) {
        if (r - l == 1) {
            st[v].second = l;
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m, r);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) const {
        if (r - l != 1) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v].first += lazy[v];
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
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    pair<int, int> qry(int x, int y) const { return qry(x, y, 1, 0, n); }
    pair<int, int> qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r <= x || l >= y) return {INF, -1};
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return min(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m, r));
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    vector<vector<int>> by_num(n);
    rep(i, 0, n) {
        cin >> nums[i];
        nums[i]--;
        by_num[nums[i]].push_back(i);
    }

    vector<int> cur(n);
    lazy_segtree st(n);
    auto set_value = [&](int idx, int v) {
        int delta = v - cur[idx];
        st.upd(idx, n, delta);
        cur[idx] = v;
    };

    vector<int> pos(n);
    rep(i, 0, n) {
        if (sz(by_num[i]) >= 1) {
            set_value(by_num[i][0], 1);
            pos[i] = 1;
        }
        if (sz(by_num[i]) >= 2) {
            set_value(by_num[i][1], -1);
        }
    }

    auto move_forward = [&](int c) {
        auto p = pos[c];
        if (p-1 < sz(by_num[c])) {
            set_value(by_num[c][p-1], 0);
        }
        if (p < sz(by_num[c])) {
            set_value(by_num[c][p], 1);
        }
        if (p+1 < sz(by_num[c])) {
            set_value(by_num[c][p+1], -1);
        }
        pos[c]++;
    };

    vector<pair<int, int>> ints;
    rep(i, 0, n) {
        auto [val, pos] = st.qry(i, n);
        if (val == 0) {
            ints.push_back({i, pos});
        }
        move_forward(nums[i]);
    }

    sort(all(ints), [](const auto &i1, const auto &i2) {
        return tie(i1.second, i1.first) < tie(i2.second, i2.first);
    });

    int last = -1;
    int ans = 0;
    for (auto [x, y] : ints) {
        if (!(x <= last && last <= y)) {
            ans++;
            last = y;
        }
    }

    cout << ans << '\n';
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

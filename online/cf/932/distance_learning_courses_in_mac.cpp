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

template<typename T, typename F>
struct segtree {
    int n;
    vector<int> st;
    F op;
    T id;
    segtree(int n, F op, T id) : n(n), st(2 * n, id), op(op), id(id) {}
    segtree(vector<int> &nums, F op, T id) : segtree(sz(nums), op, id) {
        copy(all(nums), begin(st) + n);
        for (int i = n-1; i >= 0; i--) {
            st[i] = op(st[i<<1], st[i<<1|1]);
        }
    }
    void upd(int x, T y) {
        for (x += n, st[x] = y; x > 1; x >>= 1) {
            st[x>>1] = op(st[x], st[x^1]);
        }
    }
    T qry(int l, int r) const {
        T ans = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = op(ans, st[l++]);
            if (r & 1) ans = op(st[--r], ans);
        }
        return ans;
    }
};

int get_bit(int x, int e) {
    return (x >> e) & 1;
}

tuple<int, int, int> split(int x, int y) {
    for (int i = 29; i >= 0; i--) {
        if (get_bit(x, i) != get_bit(y, i)) {
            int total_mask = (1 << 30) - 1;
            int bottom_mask = (1 << (i + 1)) - 1;
            int top_mask = total_mask ^ bottom_mask;
            return {y & top_mask, i, y & bottom_mask};
        }
    }
    return {y, -1, 0};
}

void solve() {
    int n;
    cin >> n;

    vector<int> x(n), y(n);
    rep(i, 0, n) {
        cin >> x[i] >> y[i];
    }

    vector<int> top(n), bottom(n);
    array<vector<int>, 30> pos;
    rep(i, 0, n) {
        int p;
        tie(top[i], p, bottom[i]) = split(x[i], y[i]);
        if (p != -1) {
            pos[p].push_back(i);
        }
    }

    segtree st(top, bit_or{}, 0);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;

        auto ans = st.qry(l, r);

        array<vector<int>, 30> local{};
        for (int p = 29; p >= 0; p--) {
            auto start_it = lower_bound(all(pos[p]), l);
            auto end_it = lower_bound(all(pos[p]), r);
            for (auto it = start_it; it != end_it && sz(local[p]) < 2; it++) {
                local[p].push_back(bottom[*it]);
            }

            if (sz(local[p]) >= 2) {
                ans |= (1 << (p + 1)) - 1;
            } else if (sz(local[p]) == 1) {
                if (get_bit(ans, p) == 1) {
                    ans |= (1 << p) - 1;
                } else {
                     ans |= 1 << p;
                     auto [_, np, nb] = split(1 << p, local[p][0]);
                     if (np != -1) {
                         local[np].push_back(nb);
                     }
                }
            }
        }

        cout << ans << ' ';
    }
    cout << '\n';
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

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
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) { build(1, 0, n - 1); }

    pair<int, int> comb(pair<int, int> a, pair<int, int> b) const {
        if (a.first == b.first) {
            return {a.first, a.second + b.second};
        } else {
            return min(a, b);
        }
    }

    void build(int v, int l, int r) {
        if (l == r) {
            st[v] = {0, 1};
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m + 1, r);
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }

    void push(int v, int l, int r) const {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v].first += lazy[v];
        lazy[v] = 0;
    }

    void upd(int x, int y, int q) { upd(x, y, q, 1, 0, n - 1); }
    void upd(int x, int y, int q, int v, int l, int r) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }

    pair<int, int> qry(int x, int y) const { return qry(x, y, 1, 0, n - 1); }
    pair<int, int> qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r < x || l > y) return {INF, 0};
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return comb(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<array<int, 4>> segs(n);
    for (auto &[a, b, c, d] : segs) {
        cin >> a >> b >> c >> d;
    }

    int p;
    cin >> p;

    int land_x1, land_y1, land_x2, land_y2;
    cin >> land_x1 >> land_y1 >> land_x2 >> land_y2;

    auto check = [&](int r) {
        // {x, y1, y2, delta}
        vector<array<int, 4>> events;
        for (auto [x1, y1, x2, y2] : segs) {
            auto rect_x1 = max(land_x1, x1 - r) - land_x1;
            auto rect_y1 = max(land_y1, y1 - r) - land_y1;
            auto rect_x2 = min(land_x2, x2 + r) - land_x1;
            auto rect_y2 = min(land_y2, y2 + r) - land_y1;
            events.push_back({rect_x1, rect_y1, rect_y2, +1});
            events.push_back({rect_x2, rect_y1, rect_y2, -1});
        }

        sort(all(events));

        auto range = land_y2 - land_y1;
        lazy_segtree st(range);
        int prev = 0;
        ll area = 0;
        for (auto [x, y1, y2, delta] : events) {
            auto [typ, count] = st.qry(0, range - 1);
            auto num_empty = typ == 0 ? count : 0;
            auto num_filled = range - num_empty;
            area += (ll) num_filled * (x - prev);
            st.upd(y1, y2 - 1, delta);
            prev = x;
        }

        ll total_area = (ll) range * (land_x2 - land_x1);
        // area / total_area >= p / 100, so 100 * area >= p * total_area
        return 100 * area >= p * total_area;
    };

    ll lo = 1;
    ll hi = 100'000;
    ll ans = -1;

    while (lo <= hi) {
        auto m = lo + (hi - lo) / 2;
        if (check(m)) {
            hi = m - 1;
            ans = m;
        } else {
            lo = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}

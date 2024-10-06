#include <bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

template<bool is_max>
struct segtree {
    int n;
    using node = pair<ll, ll>;
    vector<pair<node, node>> st;

    static constexpr node ID = is_max ? node{-INF, -1} : node{INF, -1};

    segtree(int n, vector<ll> &nums) : n(n), st(4 * n) {
        build(1, 0, n - 1, nums);
    }

    pair<node, node> comb(pair<node, node> a, pair<node, node> b) {
        if (is_max) {
            if (a.first < b.first) swap(a, b);
            return {a.first, max(a.second, b.first)};
        } else {
            if (a.first > b.first) swap(a, b);
            return {a.first, min(a.second, b.first)};
        }
    }

    void build(int v, int l, int r, const vector<ll> &nums) {
        if (l == r) {
            st[v] = {{nums[l], l}, ID};
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m + 1, r, nums);
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }

    pair<node, node> qry(int l, int r) {
        return qry(1, 0, n - 1, l, r);
    }

    pair<node, node> qry(int v, int l, int r, int x, int y) {
        if (y < l || x > r) return {ID, ID};
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        auto left = qry(2 * v, l, m, x, y);
        auto right = qry(2 * v + 1, m + 1, r, x, y);
        return comb(left, right);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);;

    int n, q;
    cin >> n >> q;

    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    segtree<true> max_x(n, x), max_y(n, y);
    segtree<false> min_x(n, x), min_y(n, y);

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        auto min2x = min_x.qry(a, b);
        auto max2x = max_x.qry(a, b);
        auto min2y = min_y.qry(a, b);
        auto max2y = max_y.qry(a, b);

        vector<ll> chk = {
            min2x.first.second,
            max2x.first.second,
            min2y.first.second,
            max2y.first.second
        };

        ll ans = INF;
        for (auto i : chk) {
            auto my_minx = (i == min2x.first.second ? min2x.second.first : min2x.first.first);
            auto my_maxx = (i == max2x.first.second ? max2x.second.first : max2x.first.first);
            auto my_miny = (i == min2y.first.second ? min2y.second.first : min2y.first.first);
            auto my_maxy = (i == max2y.first.second ? max2y.second.first : max2y.first.first);
            ans = min(ans, max(my_maxx - my_minx, my_maxy - my_miny));
        }

        cout << ans << '\n';
    }

    return 0;
}

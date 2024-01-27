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

struct lazy_segtree {
    int n;
    mutable vector<ll> st;
    mutable vector<pair<ll, ll>> lazy; // {mx + b}
    mutable vector<bool> lazy_valid;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n), lazy_valid(4 * n) {}
    void push(int v, int l, int r) const {
        if (lazy_valid[v]) {
            if (r - l != 1) {
                int m = (l + r) / 2;
                lazy[2 * v] = lazy[v];
                lazy[2 * v + 1] = lazy[v];

                // backwards, so first part gets shifted up
                lazy[2 * v].second += lazy[v].first * (r - m);
                lazy_valid[2 * v] = lazy_valid[2 * v + 1] = true;
            }

            ll sz = r - l;
            st[v] = (sz * (sz - 1) / 2 * lazy[v].first) + (sz * lazy[v].second);
            lazy[v] = {0, 0};
            lazy_valid[v] = false;
        }
    }
    void upd(int x, int y, ll q) { upd(x, y, q, 1, 0, n); }
    void upd(int x, int y, ll q, int v, int l, int r) {
        push(v, l, r);
        if (r <= x || l >= y) return;
        if (x <= l && r <= y) {
            lazy[v] = {q, q * (y - r)};
            lazy_valid[v] = true;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m, r);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }
    ll qry(int x, int y) const { return qry(x, y, 1, 0, n); }
    ll qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r <= x || l >= y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return qry(x, y, 2 * v, l, m) + qry(x, y, 2 * v + 1, m, r);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    vector<pair<int, ll>> init(m);

    for (int i = 0; i < m; i++) {
        cin >> init[i].first;
        init[i].first--;
    }

    for (int i = 0; i < m; i++) {
        cin >> init[i].second;
    }

    // {idx, v}
    set<pair<int, ll>> harbors;

    ll zero_value;
    for (auto [idx, v] : init) {
        if (idx == 0) {
            zero_value = v;
        }

        // also initially add 0 and n-1 to set
        if (idx == 0 || idx == n - 1) {
            harbors.insert({idx, v});
        }
    }

    lazy_segtree st(n);
    st.upd(1, n, zero_value);

    auto add = [&](int idx, ll v) {
        auto after = harbors.lower_bound({idx, 0});
        auto before = prev(after);

        st.upd(idx + 1, after->first + 1, v);
        st.upd(before->first + 1, idx + 1, before->second);
        harbors.insert({idx, v});
    };

    // add the rest
    for (auto [idx, v] : init) {
        if (idx != 0 && idx != n - 1) {
            add(idx, v);
        }
    }


    while (q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int x;
            ll v;
            cin >> x >> v;
            x--;
            add(x, v);
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            cout << st.qry(l, r) << '\n';
        }
    }

    return 0;
}

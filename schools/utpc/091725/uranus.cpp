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

struct segtree {
    int n;
    vector<int> st;
    segtree(int n) : n(n), st(4 * n, INF) {}
    void upd(int x, int y) { upd(1, 0, n, x, y); }
    void upd(int v, int l, int r, int x, int y) {
        if (l + 1 == r) {
            st[v] = min(st[v], y);
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2 * v, l, m, x, y);
            } else {
                upd(2 * v + 1, m, r, x, y);
            }
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) const { return qry(1, 0, n, x, y + 1); }
    int qry(int v, int l, int r, int x, int y) const {
        if (r <= x || y <= l) return INF;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return min(qry(2 * v, l, m, x, y), qry(2 * v + 1, m, r, x, y));
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<array<int, 3>> probes(n);
    vector<int> xs(n), ys(n);
    rep(i, 0, n) {
        cin >> probes[i][0];
        xs[i] = probes[i][0];
    }
    rep(i, 0, n) {
        cin >> probes[i][1];
        ys[i] = probes[i][1];
    }
    rep(i, 0, n) {
        cin >> probes[i][2];
    }

    vector<pair<int, int>> qry(q);
    for (auto &[x, y] : qry) {
        cin >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
    }

    sort(all(xs));
    xs.erase(unique(all(xs)), end(xs));

    sort(all(ys));
    ys.erase(unique(all(ys)), end(ys));

    auto get_x = [&](int x) { return lower_bound(all(xs), x) - begin(xs); };
    auto get_y = [&](int y) { return lower_bound(all(ys), y) - begin(ys); };

    vector<vector<int>> probe_at(sz(xs));
    rep(i, 0, n) {
        auto x = get_x(probes[i][0]);
        probe_at[x].push_back(i);
    }

    vector<vector<int>> qry_at(sz(xs));
    rep(i, 0, q) {
        auto x = get_x(qry[i].first);
        qry_at[x].push_back(i);
    }

    segtree st(sz(ys));
    vector<int> ans(q);
    for (int i = sz(xs)-1; i >= 0; i--) {
        for (auto idx : probe_at[i]) {
            auto [_, y, c] = probes[idx];
            y = get_y(y);
            st.upd(y, c);
        }

        for (auto idx : qry_at[i]) {
            auto y = get_y(qry[idx].second);
            ans[idx] = st.qry(y, sz(ys));
        }
    }

    for (auto x : ans) {
        if (x == INF) {
            cout << "-1\n";
        } else {
            cout << x << '\n';
        }
    }

    return 0;
}

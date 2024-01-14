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

struct segtree {
    int n;
    mutable vector<int> st;
    mutable vector<int> lazy;

    segtree(int n) : n(n), st(4 * n), lazy(4 * n) {}

    void push(int v, int l, int r) const {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }

    void upd(int l, int r, int q) { upd(1, 0, n - 1, l, r, q); }
    void upd(int v, int l, int r, int x, int y, int q) {
        push(v, l, r);
        if (r < x || y < l) {
            return;
        } else if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(2 * v, l, m, x, y, q);
            upd(2 * v + 1, m + 1, r, x, y, q);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }

    int qry(int l, int r) const { return qry(1, 0, n - 1, l, r); }
    int qry(int v, int l, int r, int x, int y) const {
        push(v, l, r);
        if (r < x || y < l) {
            return 0;
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            auto v1 = qry(2 * v, l, m, x, y);
            auto v2 = qry(2 * v + 1, m + 1, r, x, y);
            return max(v1, v2);
        }
    }
};

vector<pair<int, int>> sort_relevant(vector<pair<int, int>> &&ints) {
    sort(ints.begin(), ints.end(), [](auto p1, auto p2) {
        if (p1.first == p2.first) {
            return p1.second > p2.second;
        }
        return p1.first < p2.first;
    });

    vector<pair<int, int>> res;
    for (auto [x, y] : ints) {
        if (res.empty() || res.back().second < y) {
            res.push_back({x, y});
        }
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    int q;
    cin >> q;

    vector<pair<int, int>> intervals(q);
    for (auto &[x, y] : intervals) {
        cin >> x >> y;
        x--;
        y--;
    }

    intervals = sort_relevant(std::move(intervals));
    q = intervals.size();

    auto leftmost_in = [&](int x) {
        int l = 0;
        int r = q - 1;
        int ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (x <= intervals[m].second) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        if (ans == -1 || x < intervals[ans].first) {
            return -1;
        }
        return ans;
    };

    auto rightmost_in = [&](int x) {
        int l = 0;
        int r = q - 1;
        int ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (intervals[m].first <= x) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        if (ans == -1 || intervals[ans].second < x) {
            return -1;
        }
        return ans;
    };

    vector<pair<int, int>> upd_pts(n);
    for (int i = 0; i < n; i++) {
        upd_pts[i] = {a[i], i};
    }

    sort(upd_pts.begin(), upd_pts.end(), greater<>{});

    segtree st(q);

    ll ans = 0;
    for (auto [v, i] : upd_pts) {
        auto l = leftmost_in(i);
        auto r = rightmost_in(i);
        if (l != -1) {
            ans = max(ans, (ll) v * st.qry(l, r));
            st.upd(l, r, 1);
        }
    }

    cout << ans << '\n';

    return 0;
}

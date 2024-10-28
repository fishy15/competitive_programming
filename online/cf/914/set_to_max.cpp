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

template<typename Node>
struct segtree {
    int n;
    vector<typename Node::value> st;
    segtree(int n) : n(n), st(4 * n) {}
    segtree(int n, vector<typename Node::value> &nums) : segtree(n) { build(1, 0, n, nums); }
    void build(int v, int l, int r, vector<int> &nums) {
        if (l + 1 == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m, r, nums);
            st[v] = Node::combine(st[2 * v], st[2 * v + 1]);
        }
    }
    void upd(int x, int y) { upd(1, 0, n, x, y); }
    void upd(int v, int l, int r, int x, int y) {
        if (l + 1 == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2 * v, l, m, x, y);
            } else {
                upd(2 * v + 1, m, r, x, y);
            }
            st[v] = Node::combine(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) const { return qry(1, 0, n, x, y); }
    int qry(int v, int l, int r, int x, int y) const {
        if (r <= x || y <= l) return Node::I;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return Node::combine(qry(2 * v, l, m, x, y), qry(2 * v + 1, m, r, x, y));
    }
};

struct MaxInt {
    using value = int;
    static auto combine(int x, int y) { return max(x, y); }
    static int I;
};
int MaxInt::I = 0;

struct MinInt {
    using value = int;
    static auto combine(int x, int y) { return min(x, y); }
    static int I;
};
int MinInt::I = INF;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (auto &x : a) {
        cin >> x;
    }
    for (auto &x : b) {
        cin >> x;
    }

    map<int, vector<int>> a_locs;
    for (int i = 0; i < n; i++) {
        a_locs[a[i]].push_back(i);
    }

    auto a_st = segtree<MaxInt>(n, a);
    auto b_st = segtree<MinInt>(n, b);

    for (int i = 0; i < n; i++) {
        auto v = b[i];
        auto &locs = a_locs[v];

        auto it = lower_bound(locs.begin(), locs.end(), i);
        bool ok = false;
        // previous match
        if (it != locs.begin()) {
            auto j = *prev(it);
            if (a_st.qry(j, i + 1) <= v && b_st.qry(j, i + 1) >= v) {
                ok = true;
            }
        }

        // current match
        if (it != locs.end()) {
            auto j = *it;
            if (a_st.qry(i, j + 1) <= v && b_st.qry(i, j + 1) >= v) {
                ok = true;
            }
        }

        if (!ok) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
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

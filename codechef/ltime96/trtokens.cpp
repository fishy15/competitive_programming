/*
 * Suppose that we are at some empty node and there are various "chains" of filled nodes below. In order to
 * move the most up, we can greedily pick the deepest node and move the chain that it belongs to up. We can
 * query for the deepest node using segtree and process in post-order traversal, so the time complexity is
 * O(n log n).
 */

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
    vector<pair<int, int>> st;

    segtree(int n) : n(n) {
        st.assign(4 * n, {-1, 0});
    }

    void upd(int x, pair<int, int> y) { upd(1, x, y, 0, n - 1); }
    void upd(int v, int x, pair<int, int> y, int l, int r) {
        if (l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(2 * v, x, y, l, m);
            } else {
                upd(2 * v + 1, x, y, m + 1, r);
            }
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }

    pair<int, int> qry(int x, int y) { return qry(1, x, y, 0, n - 1); }
    pair<int, int> qry(int v, int x, int y, int l, int r) {
        if (y < l || x > r) {
            return {-1, 0};
        } else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return max(qry(2 * v, x, y, l, m), qry(2 * v + 1, x, y, m + 1, r));
        }
    }
};

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    vector<vector<int>> child(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        child[p].push_back(i);
    }

    int t = -1;
    vector<int> in(n);
    vector<int> rev_in(n);
    vector<int> out(n);
    segtree st(n);

    function<void(int, int)> dfs = [&](int v, int d) {
        in[v] = ++t;
        rev_in[in[v]] = v;
        
        if (s[v] == '1') {
            st.upd(in[v], {d, in[v]});
        }

        for (int e : child[v]) {
            dfs(e, d + 1);
        }

        out[v] = t;
    };

    dfs(0, 0);

    ll ans = 0;
    function<void(int, int)> dfs2 = [&](int v, int d) {
        for (int e : child[v]) {
            dfs2(e, d + 1);
        }

        if (s[v] == '0') {
            auto [tag, in_idx] = st.qry(in[v], out[v]);
            if (tag != -1) {
                int u = rev_in[in_idx];
                s[v] = '1';
                s[u] = '0';
                ans += tag - d;
                st.upd(in_idx, {-1, 0});
                st.upd(in[v], {d, in[v]});
            }
        }
    };

    dfs2(0, 0);

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

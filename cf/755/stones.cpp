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
    vector<array<ll, 2>> st;

    array<ll, 2> comb(array<ll, 2> a, array<ll, 2> b) {
        return {min(a[0], b[0]), max(a[1], b[1])};
    }

    segtree(int n) : n(n), st(4 * n, {INFLL, -INFLL}) {}

    void upd(int x, ll y) { upd(x, y, 1, 0, n); }
    void upd(int x, ll y, int v, int l, int r) {
        if (l + 1 == r) {
            st[v] = {y, y};
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m, r);
            }
            st[v] = comb(st[2 * v], st[2 * v + 1]);
        }
    }

    array<ll, 2> qry(int x, int y) { return qry(x, y, 1, 0, n); }
    array<ll, 2> qry(int x, int y, int v, int l, int r) {
        if (r <= x || y <= l) return {INFLL, -INFLL};
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return comb(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m, r));
    }
};

void solve() {
    int n; cin >> n;
    vector<int> nums(n);

    vector<ll> alt(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (i % 2 == 0) {
            alt[i + 1] = alt[i] + nums[i];
        } else {
            alt[i + 1] = alt[i] - nums[i];
        }
    }

    segtree st(n + 1), st2(n + 1);

    for (int i = 0; i <= n; i++) {
        if (i % 2 == 0) {
            st.upd(i, alt[i]);
        } else {
            st2.upd(i, alt[i]);
        }
    }

    map<ll, int> prev;
    vector<ll> dp(n + 1);

    alt[0] = 0;
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        if (prev.count(alt[i])) {
            int p = prev[alt[i]];
            auto leq = st.qry(p, i + 1);
            auto geq = st2.qry(p, i + 1);

            if (leq[1] <= alt[i] && geq[0] >= alt[i]) {
                dp[i] = dp[p] + 1;
            }
        }

        ans += dp[i];
        prev[alt[i]] = i;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

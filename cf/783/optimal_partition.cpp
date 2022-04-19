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
    vector<ll> st;

    segtree(int n) : n(n), st(4 * n, -INFLL) {}

    void upd(int x, ll y) { upd(1, 0, n, x, y); }
    void upd(int v, int l, int r, int x, ll y) {
        if (l + 1 == r) {
            st[v] = max(y, st[v]);
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2 * v, l, m, x, y);
            } else {
                upd(2 * v + 1, m, r, x, y);
            }
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }

    ll qry(int x, int y) { return qry(1, 0, n, x, y); }
    ll qry(int v, int l, int r, int x, int y) const {
        if (r <= x || l >= y) return -INFLL;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(2 * v, l, m, x, y), qry(2 * v + 1, m, r, x, y));
    }
};

void solve() {
    int n; cin >> n;
    vector<ll> nums(n);
    vector<ll> pre(n + 1);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        pre[i + 1] = pre[i] + nums[i];
    }

    vector<ll> mm = pre;
    sort(mm.begin(), mm.end());
    mm.erase(unique(mm.begin(), mm.end()), mm.end());

    auto pos = [&](ll x) { return lower_bound(mm.begin(), mm.end(), x) - mm.begin(); };

    vector<ll> zero(n + 1, -INFLL);
    segtree inc(n + 1);

    zero[pos(0)] = 0;
    inc.upd(pos(0), n + 1);

    ll prev_ans = 0;
    for (int i = 1; i <= n; i++) {
        int idx = pos(pre[i]);

        // if the range is decreasing, equal
        ll best = max(prev_ans - 1, zero[idx]);

        // if range is increasing
        ll ok = inc.qry(0, idx);
        best = max(best, ok - (n + 1 - i));

        zero[idx] = max(zero[idx], best);
        inc.upd(idx, best + (n + 1 - i));
        prev_ans = best;

    }
    
    cout << prev_ans << '\n';;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

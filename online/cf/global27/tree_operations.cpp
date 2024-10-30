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

void solve() {
    int n, x;
    cin >> n >> x;
    x--;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto check = [&](ll ops, bool skip) {
        // returns how much extra is needed
        auto dfs = [&](auto &&self, int v, int p) -> ll {
            ll needed = a[v];
            for (auto e : adj[v]) {
                if (e != p) {
                    needed += self(self, e, v);
                }
            }

            ll ops_here = ops / n;
            if (v < ops % n) {
                ops_here++;
            }

            if (ops_here >= needed) {
                if (skip) {
                    return 0;
                } else {
                    return (ops_here - needed) % 2;
                }
            } else {
                return needed - ops_here;
            }
        };

        return dfs(dfs, x, x) == 0;
    };

    auto find_with_skips = [&] {
        ll lo = 0;
        ll hi = 1000000000LL * n;
        ll ans = -1;
        while (lo <= hi) {
            auto m = lo + (hi - lo) / 2;
            if (check(m, true)) {
                ans = m;
                hi = m - 1;
            } else {
                lo = m + 1;
            }
        }
        return ans;
    };

    auto base = find_with_skips();

    auto find_no_skips = [&] {
        auto check2 = [&](ll moves) {
            for (ll i = moves; i <= moves + 2 * n; i++) {
                if (check(i, false)) {
                    return i;
                }
            }
            return -1LL;
        };

        ll lo = base;
        ll hi = 1000000000000LL * n;
        ll ans = -1;
        while (lo <= hi) {
            auto m = lo + (hi - lo) / 2;
            auto pos = check2(m);
            if (pos == -1) {
                lo = m + 1;
            } else {
                ans = pos;
                hi = m - 1;
            }
        }
        return ans;
    };

    auto moves = find_no_skips();
    cout << moves << '\n';
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

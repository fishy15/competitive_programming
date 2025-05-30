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
    int n, m;
    cin >> n >> m;

    vector<int> b(n);
    rep(i, 0, n) {
        cin >> b[i];
    }

    vector<vector<pair<int, int>>> adj(n);
    rep(i, 0, m) {
        int s, t, w;
        cin >> s >> t >> w;
        s--;
        t--;
        adj[s].push_back({t, w});
    }

    auto check = [&](ll max_b) {
        vector<ll> max_reach(n, -1);
        max_reach[0] = 0;
        rep(u, 0, n) {
            if (max_reach[u] != -1) {
                max_reach[u] = min(max_reach[u] + b[u], max_b);
                for (auto [v, w] : adj[u]) {
                    if (w <= max_reach[u]) {
                        max_reach[v] = max(max_reach[v], max_reach[u]);
                    }
                }
            }
        }
        return max_reach[n-1] != -1;
    };

    ll lo = 0;
    ll hi = (ll) m * 1e9 + 10;
    ll ans = -1;
    while (lo <= hi) {
        ll m = lo + (hi - lo) / 2;
        if (check(m)) {
            ans = m;
            hi = m-1;
        } else {
            lo = m+1;
        }
    }

    cout << ans << '\n';
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

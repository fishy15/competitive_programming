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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<vector<pair<int, ll>>> adj(n);
    ll max_w = 0;
    ll tot_w = 0;
    rep(i, 0, n-1) {
        int u, v, l;
        cin >> u >> v >> l;
        u--;
        v--;
        adj[u].push_back({v, l});
        adj[v].push_back({u, l});
        max_w = max<ll>(max_w, l);
        tot_w += l;
    }

    auto check = [&](ll gap) {
        int used = 0;
        auto dfs = [&](auto &&self, int v, int p) -> ll {
            pair<ll, ll> top_ds;
            for (auto [e, w] : adj[v]) {
                if (e != p) {
                    auto len = self(self, e, v);
                    if (len + w > gap) {
                        len = 0;
                        used++;
                    }
                    len += w;

                    if (len >= top_ds.first) {
                        top_ds.second = top_ds.first;
                        top_ds.first = len;
                    } else if (len >= top_ds.second) {
                        top_ds.second = len;
                    }
                }
            }

            if (top_ds.first + top_ds.second > gap) {
                used++;
                return 0;
            } else {
                return top_ds.first;
            }
        };
        dfs(dfs, 0, 0);

        return used <= k;
    };

    ll l = max_w;
    ll r = tot_w;
    ll ans = -1;
    while (l <= r) {
        auto m = l + (r - l) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}

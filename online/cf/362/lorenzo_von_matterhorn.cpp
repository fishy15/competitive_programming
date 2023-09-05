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

ll lca(ll u, ll v) {
    while (u != v) {
        if (u > v) u /= 2;
        else v /= 2;
    }
    return u;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q;
    cin >> q;

    map<ll, ll> cost_up;

    while (q--) {
        int t;
        cin >> t;

        if (t == 1) {
            ll v, u, w;
            cin >> v >> u >> w;

            ll l = lca(u, v);

            while (u != l) {
                cost_up[u] += w;
                u /= 2;
            }

            while (v != l) {
                cost_up[v] += w;
                v /= 2;
            }
        } else {
            ll v, u;
            cin >> v >> u;

            ll l = lca(u, v);
            ll ans = 0;
            while (u != l) {
                ans += cost_up[u];
                u /= 2;
            }

            while (v != l) {
                ans += cost_up[v];
                v /= 2;
            }

            cout << ans << '\n';
        }
    }

    return 0;
}

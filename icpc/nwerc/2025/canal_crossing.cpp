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

    int n;
    cin >> n;

    vector<vector<pair<int, ll>>> adj(n);
    rep(i, 0, n-1) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    int m;
    cin >> m;
    vector<int> par(n);
    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        par[a] ^= 1;
        par[b] ^= 1;
    }

    ll ans = 0;
    auto dfs = [&](auto &&self, int v, int p) -> void {
        for (auto [e, w] : adj[v]) {
            if (e != p) {
                self(self, e, v);
                if (par[e]) {
                    par[v] ^= 1;
                    ans += w;
                }
            }
        }
    };
    dfs(dfs, 0, 0);

    cout << ans << '\n';

    return 0;
}

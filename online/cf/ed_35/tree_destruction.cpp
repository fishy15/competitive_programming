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

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // dist from the root last queries
    auto dfs = [&](auto &&self, int v, int p, vector<int> &d) -> void {
        for (auto e : adj[v]) {
            if (e != p) {
                d[e] = d[v] + 1;
                self(self, e, v, d);
            }
        }
    };

    vector<int> dist1(n);
    dfs(dfs, 0, 0, dist1);

    auto d1 = (int) (max_element(all(dist1)) - begin(dist1));
    dist1[d1] = 0;
    dfs(dfs, d1, d1, dist1);

    auto d2 = (int) (max_element(all(dist1)) - begin(dist1));
    vector<int> dist2(n);
    dfs(dfs, d2, d2, dist2);

    auto diam = dist1[d2];

    vector<pair<int, int>> ord;
    ll ans = 0;
    rep(i, 0, n) {
        if (dist1[i] + dist2[i] != diam) {
            ord.push_back({dist1[i] + dist2[i], i});
        }
    }
    sort(all(ord), greater<>{});

    vector<array<int, 3>> ops;
    for (auto [_, v] : ord) {
        if (dist1[v] > dist2[v]) {
            ops.push_back({d1, v, v});
        } else {
            ops.push_back({d2, v, v});
        }
        ans += max(dist1[v], dist2[v]);
    }

    // now get everything on the path
    vector<pair<int, int>> on_path;
    rep(i, 0, n) {
        if (dist1[i] + dist2[i] == diam && i != d1) {
            on_path.push_back({dist1[i], i});
        }
    }
    sort(all(on_path), greater<>{});
    for (auto [_, v] : on_path) {
        ans += dist1[v];
        ops.push_back({d1, v, v});
    }

    cout << ans << '\n';
    for (auto [a, b, c] : ops) {
        cout << a+1 << ' ' << b+1 << ' ' << c+1 << '\n';
    }

    return 0;
}

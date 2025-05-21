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

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, char>>> adj(n), rev(n);
    rep(i, 0, m) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        u--;
        v--;
        adj[u].push_back({v, c});
        rev[v].push_back({u, c});
    }

    vector vis(n, vector<bool>(n));
    queue<pair<int, int>> q;

    set<pair<int, int>> starts;

    rep(u, 0, n) {
        vis[u][u] = true;
        starts.insert({u, u});

        for (auto [v, _] : adj[u]) {
            vis[u][v] = true;
            starts.insert({u, v});
        }
    }

    for (auto p : starts) {
        q.push(p);
    }

    while (!q.empty()) {
        auto [u1, v1] = q.front();
        q.pop();

        for (auto [u2, c1] : rev[u1]) {
            for (auto [v2, c2] : adj[v1]) {
                if (c1 == c2 && !vis[u2][v2]) {
                    vis[u2][v2] = true;
                    q.push({u2, v2});
                }
            }
        }
    }

    int ans = 0;
    rep(i, 0, n) {
        rep(j, 0, n) {
            if (i != j && vis[i][j]) {
                ans++;
            }
        }
    }
    
    cout << ans << '\n';

    return 0;
}

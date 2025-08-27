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
#include <cassert>

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
    int n;
    cin >> n;

    vector adj(n, vector<int>{});
    vector<int> deg(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<pair<int, int>> ops;
    vector<bool> vis(n);
    // 0 = doesn't exist
    // 1 = exists and contributes single path
    // 2 = we need to delete parent
    auto dfs = [&](auto &&self, int v, int p) -> int {
        int child_count = 0;
        bool need_delete = false;
        for (auto e : adj[v]) {
            if (e != p) {
                auto c_exists = self(self, e, v);
                if (c_exists == 2) {
                    need_delete = true;
                } else {
                    child_count += c_exists;
                }
            }
        }

        if (need_delete || child_count >= 3) {
            ops.push_back({2, v});
            ops.push_back({1, v});
            vis[v] = true;
            for (auto e : adj[v]) {
                deg[e]--;
            }
            return 0;
        } else if (child_count == 2) {
            return 2;
        } else {
            return 1;
        }
    };

    dfs(dfs, 0, 0);

    auto dfs2 = [&](auto &&self, int v, int p) -> void {
        ops.push_back({1, v});
        vis[v] = true;
        for (auto e : adj[v]) {
            if (!vis[e]) {
                self(self, e, v);
            }
        }
    };
 
    rep(i, 0, n) {
        if (deg[i] <= 1 && !vis[i]) {
            dfs2(dfs2, i, i);
        }
    }

    cout << sz(ops) << '\n';
    for (auto [a, b] : ops) {
        cout << a << ' ' << b+1 << '\n';
    }
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

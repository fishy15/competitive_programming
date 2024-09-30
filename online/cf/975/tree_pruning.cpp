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
    int n;
    cin >> n;

    vector adj(n, vector<int>());
    rep(i, 0, n-1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> depth(n);
    vector<int> par(n);
    vector<vector<int>> leaf_at(n);
    vector<int> count_at(n);

    auto dfs = [&](auto &&self, int u, int p, int d) -> void {
        int lc = 0;
        for (auto v : adj[u]) {
            if (v != p) {
                self(self, v, u, d+1);
                lc++;
            }
        }

        if (lc == 0) {
            leaf_at[d].push_back(u);
        }
        par[u] = p;
        depth[u] = d;
        count_at[d]++;
    };

    int kept_edges = 0;
    int below_height = 0;

    // edges identified by the lower node
    vector<bool> vis(n);
    auto mark = [&](int u) -> void {
        while (u != 0 && !vis[u]) {
            vis[u] = true;
            u = par[u];
            kept_edges++;
        }
    };

    dfs(dfs, 0, 0, 0);

    int max_keep = 0;
    for (int cur_d = n-1; cur_d >= 0; cur_d--) {
        for (auto v : leaf_at[cur_d]) {
            mark(v);
        }

        max_keep = max(max_keep, kept_edges - below_height);
        below_height += count_at[cur_d];
    }

    cout << (n-1) - max_keep << '\n';
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

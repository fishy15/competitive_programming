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
    int n, k, root;
    cin >> n >> k >> root;
    root--;

    vector adj(n, vector<int>{});
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (sz(adj[root]) == 1) {
        cout << "YES\n";
        return;
    }

    auto dfs = [&](auto &&self, int v, int p) -> int {
        if (sz(adj[v]) == 1) {
            // we are a leaf, we cut the edge above us
            return 0;
        } else {
            vector<int> below;
            for (auto e : adj[v]) {
                if (e != p) {
                    below.push_back(self(self, e, v) + 1);
                }
            }

            sort(all(below));
            if (sz(below) > 1 && below[0] + below[1] - 1 < k + 1) {
                // we have to cut the edge above us
                return 0;
            } else {
                return below[0];
            }
        }
    };

    auto res = dfs(dfs, root, root);
    if (res > 0) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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

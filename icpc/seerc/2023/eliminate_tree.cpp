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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector adj(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // dp[v][0] = cost to remove subtree completely
    // dp[v][1] = cost to remove subtree, root unpaired still
    vector dp(n, array<int, 2>{INF, INF});

    auto dfs = [&](auto dfs, int v, int p) -> void {
        int cost_complete_below = 0;
        int max_benefit = -INF;
        for (auto e : adj[v]) {
            if (e != p) {
                dfs(dfs, e, v);
                cost_complete_below += dp[e][0];
                max_benefit = max(max_benefit, dp[e][0] - dp[e][1]);
            }
        }

        dp[v][0] = min(cost_complete_below + 2, cost_complete_below - max_benefit + 1);
        dp[v][1] = cost_complete_below;
    };

    dfs(dfs, 0, 0);

    cout << dp[0][0] << '\n';

    return 0;
}

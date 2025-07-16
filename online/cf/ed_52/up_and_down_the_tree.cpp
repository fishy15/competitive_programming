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

    vector<int> par(n);
    vector<vector<int>> child(n);
    rep(i, 1, n) {
        cin >> par[i];
        par[i]--;
        child[par[i]].push_back(i);
    }

    // dp[v][0] = max leaves if we don't have to return
    // dp[v][1] = max leaves if we have to return
    // dp[v][2] = min depth if trying to climb back up
    vector<array<int, 3>> dp(n);
    auto dfs = [&](auto &&self, int v, int d) -> void {
        for (auto e : child[v]) {
            self(self, e, d+1);
        }

        if (child[v].empty()) {
            dp[v][1] = 1;
            dp[v][2] = d;
        } else {
            dp[v][2] = INF;
        }

        int max_improve = 0;
        for (auto e : child[v]) {
            int return_visit = 0;
            if (dp[e][2] - d <= k) {
                return_visit = dp[e][1];
            }

            dp[v][1] += return_visit;
            max_improve = max(max_improve, dp[e][0] - return_visit);

            dp[v][2] = min(dp[v][2], dp[e][2]);
        }

        dp[v][0] = dp[v][1] + max_improve;
    };

    dfs(dfs, 0, 0);
    cout << dp[0][0] << '\n';

    return 0;
}

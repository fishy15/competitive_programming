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

template<typename T>
T ckmax(T &a, T b) {
    return a = max(a, b);
}

void solve() {
    int n;
    cin >> n;
    n++;

    vector<int> nums(n-1);
    for (int i = 0; i < n-1; i++) {
        cin >> nums[i];
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector dist(n, vector<int>(n));

    auto count_garbage = [&](int u, int v, bool lock1, bool lock2) {
        vector<int> par(n, -1);
        auto dfs = [&](auto &&self, int v, int p) -> void {
            for (auto e : adj[v]) {
                if (e != p) {
                    par[e] = v;
                    self(self, e, v);
                }
            }
        };
        dfs(dfs, u, -1);

        vector<bool> garbage(n, true);
        int len = 0;
        auto mark_on_path = [&] {
            int cur = v;
            while (cur != -1) {
                garbage[cur] = false;
                cur = par[cur];
                len++;
            }
        };
        mark_on_path();

        dist[u][v] = len;
        if (u == v) {
            return -1;
        }

        auto count_garbage = [&](auto &&self, int v, int p) -> int {
            int ans = garbage[v] ? 1 : 0;
            for (auto e : adj[v]) {
                if (e != p && garbage[e]) {
                    ans += self(self, e, v);
                }
            }
            return ans;
        };

        auto comp = [&] {
            int cur = v;
            int ans = 0;
            while (cur != -1) {
                if (cur == u) {
                    if (lock1) {
                        ans += count_garbage(count_garbage, u, -1);
                    }
                } else if (cur == v) {
                    if (lock2) {
                        ans += count_garbage(count_garbage, v, -1);
                    }
                } else {
                    ans += count_garbage(count_garbage, cur, -1);
                }
                cur = par[cur];
            }
            return ans;
        };

        return comp();
    };

    // 0 = intend to go there
    // 1 = locked in
    vector garbage(n, vector(n, array<array<int, 2>, 2>{}));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int a = 0; a < 2; a++) {
                for (int b = 0; b < 2; b++) {
                    garbage[i][j][a][b] = count_garbage(i, j, a, b);
                }
            }
        }
    }

    array<array<ll, 2>, 2> init{};
    init[0][0] = -1;
    init[0][1] = -1;
    init[1][0] = -1;
    init[1][1] = -1;

    ll ans = 0;
    vector dp(n+1, vector(n, vector(n, init)));
    for (int v = 0; v < n; v++) {
        if ((int) adj[v].size() == 1) {
            int e = adj[v][0];
            dp[0][v][e][1][0] = 0;
            dp[0][e][v][0][1] = 0;
        } else {
            for (int x : adj[v]) {
                for (int y : adj[v]) {
                    if (x != y) {
                        dp[0][x][y][0][0] = 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                for (int a = 0; a < 2; a++) {
                    for (int b = 0; b < 2; b++) {
                        if (dp[i][u][v][a][b] == -1) continue;

                        if (a == 1 && b == 1) {
                            ckmax(ans, dp[i][u][v][a][b]);
                        }

                        if (i == n-1) continue;

                        int slots = garbage[u][v][a][b];
                        int filled = (i+1) - (dist[u][v] - (1-a) - (1-b));

                        // extend u
                        if (a == 0) {
                            for (auto e : adj[u]) {
                                if (dist[e][v] > dist[u][v]) {
                                    ckmax(dp[i+1][e][v][a][b], dp[i][u][v][a][b] + nums[i]);
                                }
                            }

                            // fill in
                            ckmax(dp[i+1][u][v][1][b], dp[i][u][v][a][b] + nums[i]);
                        }

                        // extend v
                        if (b == 0) {
                            for (auto e : adj[v]) {
                                if (dist[u][e] > dist[u][v]) {
                                    ckmax(dp[i+1][u][e][a][b], dp[i][u][v][a][b] + nums[i]);
                                }
                            }

                            // fill in
                            ckmax(dp[i+1][u][v][a][1], dp[i][u][v][a][b] + nums[i]);
                        }

                        if (filled + 1 <= slots) {
                            ckmax(dp[i+1][u][v][a][b], dp[i][u][v][a][b]);
                        }
                    }
                }
            }
        }
    }

    cout << ans << '\n';
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

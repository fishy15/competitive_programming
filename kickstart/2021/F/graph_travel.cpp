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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<array<int, 3>> rooms(n);
    vector<vector<int>> adj(n);

    for (int i = 0; i < n; i++) {
        cin >> rooms[i][0] >> rooms[i][1] >> rooms[i][2];
    }

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<ll> dp(1 << n);
    vector<ll> sum(1 << n);
    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                int m2 = i ^ (1 << j);
                sum[i] = rooms[j][2] + sum[m2];
                if (m2 == 0) {
                    dp[i] = 1;
                } else {
                    if (sum[m2] < rooms[j][0] || sum[m2] > rooms[j][1]) continue;
                    bool ok = false;
                    for (int k = 0; k < n; k++) {
                        if (m2 & (1 << k)) {
                            if (count(adj[j].begin(), adj[j].end(), k)) {
                                ok = true;
                                break;
                            }
                        }
                    }
                    if (ok) {
                        dp[i] += dp[m2];
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i < (1 << n); i++) {
        if (sum[i] == k) {
            ans += dp[i];
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

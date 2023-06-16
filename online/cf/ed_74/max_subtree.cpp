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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 300000

using namespace std;

vector<int> adj[MAXN + 1];
int dp[MAXN + 1];
int ans;

void dfs(int v, int p) {
    int m1 = 0;
    int m2 = 0;
    dp[v] = 1;
    int cc = 0;

    for (int e : adj[v]) {
        if (e != p) {
            cc++;
            dfs(e, v);

            if (dp[e] >= m1) {
                m2 = m1;
                m1 = dp[e];
            } else if (dp[e] > m2) {
                m2 = dp[e];
            }
        }
    }

    if (cc == 1) {
        dp[v] += m1;
    } else if (cc >= 2) {
        dp[v] += m1 + m2;
        dp[v] += cc - 2;
    }

    ans = max(ans, dp[v]);
}

void solve() {
    int n; cin >> n;
    ans = 0;
    // reset
    for (int i = 1; i <= n; i++) {
        adj[i] = {};
        dp[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 1);

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

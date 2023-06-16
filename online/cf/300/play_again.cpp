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
#define MAXN 200000

using namespace std;

// 0 = min, 1 = max
int n;
vector<int> adj[MAXN + 1];
int dp[MAXN + 1][2];
int child[MAXN + 1];

void dfs(int v, int p, bool mm) {
    if (adj[v].size() == 1 && v != 1) {
        child[v] = 1;
        dp[v][0] = 1;
        dp[v][1] = 1;
    } else if (mm) {
        int m = 0;
        dp[v][0] = INF;
        for (int e : adj[v]) {
            if (e != p) {
                dfs(e, v, !mm);
                child[v] += child[e];
                m = max(m, dp[e][0] - child[e]);
                dp[v][0] = min(dp[e][0]
            }
        }
        /* int m = 0; */
        /* for (int e : adj[v]) { */
        /*     if (e != p) { */
        /*         dfs(e, v); */
        /*         child[v] += child[e]; */
        /*         m = max(m, dp[e][0] - child[e]); */
        /*         dp[v][0] += dp[e][1] - 1; */
        /*     } */
        /* } */

        /* dp[v][0]++; */
        /* dp[v][1] = child[v] + m; */
    }
}

int main() {
   cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if (n == 1) {
        cout << "1 1\n";
        return 0;
    }

    dfs(1, 1);

    int mm = INF;
    for (auto e : adj[1]) {
        mm = min(mm, child[1] - child[e] + dp[e][0]);
    }

    cout << dp[1][1] << ' ' << mm << '\n';

    return 0;
}

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

int n;
vector<int> adj[MAXN];
int dp[MAXN];
int ans;

void dfs(int v, int p)  {
    vector<int> vals;
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
            vals.push_back(dp[e]);
        }
    }
    sort(vals.rbegin(), vals.rend());
    if (vals.size() >= 2) {
        ans = max(ans, vals[0] + vals[1] + 2);
    }
    if (!vals.empty()) {
        dp[v] = vals[0] + 1;
    }
    ans = max(ans, dp[v]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);
    cout << ans << '\n';

    return 0;
}

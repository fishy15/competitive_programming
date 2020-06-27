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
#define MAXN 200010

using namespace std;

int n;
vector<int> adj[MAXN];
int dp[MAXN][2];

void dfs(int v, int p) {
    int cnt = 0;
    int nopick = 0;
    int mm = 0;
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
            cnt++;
            nopick += dp[e][0];
            mm = max(mm, dp[e][1] - dp[e][0]);
        }
    }

    if (cnt == 0) {
        dp[v][0] = 0;
        dp[v][1] = 1;
    } else {
        dp[v][0] = nopick + mm;
        dp[v][1] = nopick + 1;
    }
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
    cout << dp[0][0] << '\n';

    return 0;
}

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
int dp[MAXN];

void dfs(int v) {
    for (int e : adj[v]) {
        dfs(e);
        dp[v] += dp[e] + 1;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int x; cin >> x;
        x--;
        adj[x].push_back(i);
    }

    dfs(0);

    for (int i = 0; i < n; i++) {
        cout << dp[i] << ' ';
    }
    cout << '\n';

    return 0;
}

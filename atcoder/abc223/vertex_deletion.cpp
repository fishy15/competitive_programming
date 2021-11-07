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
#define MAXN 200010

using namespace std;

int n;
vector<int> adj[MAXN];
// 0 = don't include edge where this is bottom, 1 = include
array<int, 2> dp[MAXN];
multiset<int, greater<int>> max_d[MAXN];
int max_match, ans;

void calc(int v, int p) {
    dp[v] = {0, 0};
    max_d[v].insert(0);

    for (int e : adj[v]) {
        if (e != p) {
            max_d[v].insert(dp[e][1] - dp[e][0]);
            dp[v][1] += dp[e][0];
        }
    }

    dp[v][0] = dp[v][1] + *max_d[v].begin();
    dp[v][1]++;
}

void conv(int v, int p, int e) {
    dp[v][0] -= *max_d[v].begin();

    if (e != -1) {
        dp[v][0] -= dp[e][0];
        dp[v][1] -= dp[e][0];
        max_d[v].erase(max_d[v].find(dp[e][1] - dp[e][0]));
    }

    if (p != -1) {
        dp[v][0] += dp[p][0];
        dp[v][1] += dp[p][0];
        max_d[v].insert(dp[p][1] - dp[p][0]);
    }

    dp[v][0] += *max_d[v].begin();
}

void dfs(int v, int p) {
    dp[v] = {0, 0};

    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }

    calc(v, p);
}

void dfs2(int v, int p) {
    int cnt = 0;
    for (int e : adj[v]) {
        cnt += dp[e][0];
    }

    if (cnt == max_match) {
        ans++;
    }

    for (int e : adj[v]) {
        if (e != p) {
            conv(v, p, e);
            dfs2(e, v);
            conv(v, e, p);
        }
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

    dfs(0, 0);
    max_match = max(dp[0][0], dp[0][1] - 1);
    dfs2(0, -1);

    cout << ans << '\n';

    return 0;
}

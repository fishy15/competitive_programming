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
pair<int, int> dp[MAXN];
array<int, 3> ans;

int mdist[MAXN];

void dfs(int v, int p) {
    vector<pair<int, int>> vals;
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
            vals.push_back(dp[e]);
        }
    }

    sort(vals.rbegin(), vals.rend());
    if (vals.size() >= 2) {
        ans = max(ans, {vals[0].first + vals[1].first + 2, vals[0].second, vals[1].second});
    }
    if (!vals.empty()) {
        dp[v] = {vals[0].first + 1, vals[0].second};
    } else {
        dp[v] = {0, v};
    }
    ans = max(ans, {dp[v].first, dp[v].second, v});
}

void dfs2(int v, int p, int d) {
    mdist[v] = max(mdist[v], d);
    for (int e : adj[v]) {
        if (e != p) {
            dfs2(e, v, d + 1);
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

    dfs(0, -1);
    dfs2(ans[1], -1, 0);
    dfs2(ans[2], -1, 0);

    for (int i = 0; i < n; i++) {
        cout << mdist[i] << ' ';
    }
    cout << '\n';

    return 0;
}

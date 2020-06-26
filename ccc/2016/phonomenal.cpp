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
#include <cstring>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

int n, m;
vector<int> adj[MAXN];
bool ok[MAXN];
int child[MAXN];
int ans;

bool vis[MAXN];
int dp[MAXN];
int mm;

int dfs(int v, int p) {
    for (int e : adj[v]) {
        if (e != p) {
            child[v] += dfs(e, v);
        }
    }
    child[v] += ok[v];
    return child[v];
}

pair<int, int> get_root(int v, int p) {
    int pos = 0;
    for (int e : adj[v]) {
        if (e != p) {
            if (child[e]) pos++;
        }
    }

    if (!ok[v] && pos == 1) {
        for (int e : adj[v]) {
            if (e != p && child[e]) {
                return get_root(e, v);
            }
        }
    }

    return {v, p};
}

void dfs2(int v, int p) {
    ans += 2;
    for (int e : adj[v]) {
        if (e != p && child[e]) {
            dfs2(e, v);
        }
    }
}

void dfs3(int v, int p) {
    vector<int> val;
    for (int e : adj[v]) {
        if (e != p && child[e]) {
            dfs3(e, v);
            val.push_back(dp[e]);
        }
    }
    sort(val.rbegin(), val.rend());
    if (val.size() >= 2) {
        mm = max(mm, val[0] + val[1] + 2);
    }
    if (!val.empty()) {
        dp[v] = val[0] + 1;
    }
    mm = max(mm, dp[v]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a; cin >> a;
        ok[a] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);
    auto [root, par] = get_root(0, -1);
    dfs2(root, par);
    ans -= 2;
    dfs3(root, par);

    cout << ans - mm << '\n';

    return 0;
}

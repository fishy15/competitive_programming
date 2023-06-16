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
#define MAXN 100000

using namespace std;

int n, m;
vector<int> adj[MAXN];
vector<int> radj[MAXN];
int c[MAXN];

bool vis[MAXN];
vector<int> ord;

bool vis2[MAXN];
int comp[MAXN];
vector<vector<int>> scc;

ll dp[MAXN];

void dfs(int v) {
    vis[v] = true;
    for (int e : adj[v]) {
        if (!vis[e]) dfs(e);
    }
    ord.push_back(v);
}

void dfs2(int v, int pos) {
    vis2[v] = true;
    comp[v] = pos;
    scc.rbegin()->push_back(v);
    for (int e : radj[v]) {
        if (!vis2[e]) dfs2(e, pos);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i);
    }

    reverse(ord.begin(), ord.end());
    int cnt = 0;

    for (int i : ord) {
        if (!vis2[i]) {
            scc.push_back({});
            dfs2(i, cnt++);
        }
    }

    ll ans = 0;
    for (int i = 0; i < cnt; i++) {
        ll m = 0;
        for (int j : scc[i]) {
            dp[i] += c[j];
            for (int k : radj[j]) {
                if (comp[k] != i) {
                    m = max(m, dp[comp[k]]);
                }
            }
        }
        dp[i] += m;
        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';

    return 0;
}

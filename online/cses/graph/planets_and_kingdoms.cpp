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

int vis[MAXN];
vector<int> ord;

int vis2[MAXN];
int ans[MAXN];

void dfs(int v) {
    vis[v] = true;
    for (int e : adj[v]) {
        if (!vis[e]) dfs(e);
    }
    ord.push_back(v);
}

void dfs2(int v, int pos) {
    ans[v] = pos;
    vis2[v] = true;
    for (int e : radj[v]) {
        if (!vis2[e]) dfs2(e, pos);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i);
    }

    reverse(ord.begin(), ord.end());

    int cnt = 1;
    for (int i : ord) {
        if (!vis2[i]) dfs2(i, cnt++);
    }

    cout << cnt - 1 << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}

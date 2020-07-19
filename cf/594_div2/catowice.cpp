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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> radj;
vector<bool> vis;
vector<bool> vis2;
vector<vector<int>> scc;
vector<int> ord;
vector<int> comp;

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

void solve() {
    int n, m; cin >> n >> m;
    adj = vector<vector<int>>(2 * n);
    radj = vector<vector<int>>(2 * n);
    vis = vector<bool>(2 * n);
    vis2 = vector<bool>(2 * n);
    comp = vector<int>(2 * n);
    scc = {};
    ord = {};
    
    for (int i = 0; i < n; i++) {
        radj[i].push_back(i + n);
        adj[i + n].push_back(i);
    }

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        b += n;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    for (int i = 0; i < 2 * n; i++) {
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

    if (scc.size() == 1) {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";
    vector<int> ans[2];
    for (int i = 0; i < n; i++) {
        if (comp[i] != 0) {
            ans[0].push_back(i + 1);
        }
    }

    for (int i = n; i < 2 * n; i++) {
        if (comp[i] == 0) {
            ans[1].push_back(i - n + 1);
        }
    }

    cout << ans[0].size() << ' ' << ans[1].size() << '\n';
    for (int i : ans[0]) {
        cout << i << ' ';
    }
    cout << '\n';

    for (int i : ans[1]) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t; 
    while (t--) solve();

    return 0;
}

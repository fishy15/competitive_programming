/*
 * Suppose that there were only two elements. We could then increment the value on each path by 1 
 * and check if the value on each edge is >= k. Since we have multiple points, we cannot directly
 * use this because some edges will be counted twice. However, if we sort each set by the order 
 * that we DFS into it and increment the value on each pair of adjacent points (including the first
 * and last), then we will increment each path necessary for that set twice. We can now DFS to 
 * calculate which edges have a value >= 2k.
 */

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
#define MAXN 100010

using namespace std;

int n, m, k;
vector<pair<int, int>> adj[MAXN];
vector<int> plan[MAXN];
int par_e[MAXN];
int dx[MAXN];
vector<int> ans;

int in[MAXN];
int out[MAXN];
int up[MAXN][20];
int t = 1;

void dfs(int v, int p, int e) {
    in[v] = t++;
    up[v][0] = p;
    par_e[v] = e;
    for (int i = 1; i < 20; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto e : adj[v]) {
        if (e.first != p) {
            dfs(e.first, v, e.second);
        }
    }
    out[v] = t++;
}

int dfs2(int v, int p) {
    int res = dx[v];
    for (auto e : adj[v]) {
        if (e.first != p) {
            res += dfs2(e.first, v);
        }
    }
    if (res >= 2 * k && v) {
        ans.push_back(par_e[v]);
    }
    return res;
}

bool anc(int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}

int lca(int a, int b) {
    if (anc(a, b)) return a;
    if (anc(b, a)) return b;

    for (int i = 19; i >= 0; i--) {
        if (!anc(up[a][i], b)) {
            a = up[a][i];
        }
    }

    return up[a][0];
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    cin >> n >> m >> k;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    for (int i = 0; i < m; i++) {
        int sz; cin >> sz;
        for (int j = 0; j < sz; j++) {
            int x; cin >> x;
            x--;
            plan[i].push_back(x);
        }
    }

    dfs(0, 0, -1);

    for (int i = 0; i < m; i++) {
        int sz = (int)(plan[i].size());

        sort(plan[i].begin(), plan[i].end(), [](const int a, const int b) {
            return in[a] < in[b];
        });

        plan[i].push_back(plan[i][0]);

        for (int j = 0; j < sz; j++) {
            int l = lca(plan[i][j], plan[i][j + 1]);
            dx[plan[i][j]]++;
            dx[plan[i][j + 1]]++;
            dx[l] -= 2;
        }
    }

    dfs2(0, -1);

    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (int i : ans) {
        cout << i + 1 << ' ';
    }
    cout << '\n';

    return 0;
}

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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 3010

using namespace std;

int n, m;
vector<int> adj[MAXN];
vector<int> sol;
int vis[MAXN];
int par[MAXN];
int dist[MAXN];

void solve(int x) {
    memset(vis, 0, sizeof vis); 
    memset(par, -1, sizeof par);
    memset(dist, 0x3f, sizeof dist);

    queue<int> q;
    q.push(x);
    vis[x] = true;
    par[x] = -1;
    dist[x] = 0;

    while (!q.empty()) {
        auto t = q.front();
        q.pop();

        /* if (dist[t] == 3) { */
        /*    vector<int> v = {x, t, par[t], par[par[t]]}; */ 
        /*     sort(v.begin(), v.end()); */
        /*     if (sol.empty() || sol.size() > v.size()) { */
        /*         sol = v; */
        /*     } else if (sol.size() == v.size()) { */
        /*         sol = min(sol, v); */
        /*     } */
        /* } */

        for (int e : adj[t]) {
            if (vis[e] && e != par[t]) {
                if (dist[t] + dist[e] == 2) {
                    vector<int> v = {x, e, t};
                    sort(v.begin(), v.end());
                    if (sol.empty() || sol.size() > v.size()) {
                        sol = v;
                    } else if (sol.size() == v.size()) {
                        sol = min(sol, v);
                    }
                }
            } else if (!vis[e]) {
                vis[e] = true;
                par[e] = t;
                dist[e] = dist[t] + 1;
                q.push(e);
            }
        }
    }
}

void solve2(int x) {
    memset(dist, 0x3f, sizeof dist);
    memset(par, -1, sizeof par);

    dist[x] = 0;
    function<void(int, int)> dfs = [&](int v, int p) {
        if (dist[v] >= 4) return;
        if (dist[v] == 3) {
           vector<int> vv = {x, v, par[v], par[par[v]]}; 
            sort(vv.begin(), vv.end());
            if (sol.empty() || sol.size() > vv.size()) {
                sol = vv;
            } else if (sol.size() == vv.size()) {
                sol = min(sol, vv);
            }
        }
        for (int e : adj[v]) {
            if (e != p) {
                par[e] = v;
                dist[e] = dist[v] + 1;
                dfs(e, v);
            }
        }
    };

    dfs(x, x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    for (int i = 0; i < n; i++) {
        solve(i);
        solve2(i);
    }

    if (sol.empty()) {
        cout << "-1\n";
    } else {
        cout << sol.size() << '\n';
        for (int x : sol) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}

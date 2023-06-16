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

int n, m;
ll vals[MAXN];
vector<pair<int, int>> edges;
vector<int> adj[MAXN];
int ans[5 * MAXN];
int par[MAXN];
int pare[MAXN];

bool vis[MAXN];
bool cyc[MAXN];
bool cyce[5 * MAXN];
int rep = -1;

inline int o(int v, int e) {
    if (edges[e].first == v) return edges[e].second;
    return edges[e].first;
}

void dfs(int v, int p, int ee) {
    vis[v] = true;
    par[v] = p;
    par[v] = ee;
    for (int e : adj[v]) {
        int u = o(v, e);
        if (u != p) {
            if (vis[u]) {
                rep = e; 
                int cur = v;
                int cure = e;
                while (cur != u) {
                    cyc[cur] = true;
                    cyce[cure] = true;
                    cur = par[cur];
                    cure = pare[cure];
                }
                cyc[u] = true;
            } else {
                dfs(u, v, e);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(i);
        adj[b].push_back(i);
        edges.push_back({a, b});
    }

    if (n < m) {
        cout << "0\n";
        return 0;
    }

    dfs(0, -1, -1);

    return 0;
}

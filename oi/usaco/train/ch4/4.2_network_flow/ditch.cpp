/*
ID: aaryan.1
TASK: ditch
LANG: C++14
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
#define MAXN 210

using namespace std;

struct edge {
    int u, v;
    ll f, c;
    edge(int u, int v, ll c) : u(u), v(v), f(0), c(c) {}
};

int n, m;
vector<int> adj[MAXN];
vector<edge> edges;
int level[MAXN];
int nxt[MAXN];

void add_edge(int u, int v, ll c) {
    adj[u].push_back(edges.size());
    edges.push_back({u, v, c});
    adj[v].push_back(edges.size());
    edges.push_back({v, u, 0});
}

bool bfs() {
    queue<int> q;
    q.push(0);
    memset(level, -1, sizeof level);
    level[0] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int e : adj[v]) {
            if (edges[e].c - edges[e].f > 0 && level[edges[e].v] == -1) {
                level[edges[e].v] = level[v] + 1;
                q.push(edges[e].v);
            }
        }
    }
    
    return level[m - 1] != -1;
}

ll dfs(int v, ll cur) {
    if (cur == 0) return 0;
    if (v == m - 1) return cur;

    for (int &i = nxt[v]; i < (int)(adj[v].size()); i++) {
        int e = adj[v][i];
        if (level[v] + 1 == level[edges[e].v] && edges[e].c - edges[e].f > 0) {
            int w = dfs(edges[e].v, min(cur, edges[e].c - edges[e].f));
            if (w > 0) {
                edges[e].f += w;
                edges[e ^ 1].f -= w;
                return w;
            }
        }
    }

    return 0;
}

ll dinic() {
    ll flow = 0;
    while (true) {
        if (!bfs()) break;
        memset(nxt, 0, sizeof nxt);
        while (ll f = dfs(0, INF)) flow += f;
    }
    return flow;
}

int main() {
    ifstream fin("ditch.in");
    ofstream fout("ditch.out");

    fin >> n >> m;
    for (int i = 0; i < n; i++) {
        int u, v, c; fin >> u >> v >> c;
        u--; v--;
        add_edge(u, v, c);
    }

    fout << dinic() << '\n';

    return 0;
}

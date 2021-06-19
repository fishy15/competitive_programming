/*
ID: aaryan.1
TASK: stall4
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
#define MAXN 410

using namespace std;

struct edge {
    int u, v, f, c;
    edge(int u, int v, int c) : u(u), v(v), f(0), c(c) {}
    int cap() { return c - f; }
};

// node 0 = source
// node 1..n = cows
// node n+1..n+m = barn
// node n+m+1 = sink
int n, m;
vector<int> adj[MAXN];
vector<edge> edges;
int level[MAXN];
int nxt[MAXN];

void add_edge(int u, int v, int c) {
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
            if (edges[e].cap() > 0 && level[edges[e].v] == -1) {
                level[edges[e].v] = level[v] + 1;
                q.push(edges[e].v);
            }
        }
    }

    return level[n + m + 1] != -1;
}

int dfs(int v, int cur) {
    if (cur == 0) return 0;
    if (v == n + m + 1) return cur;

    for (int &i = nxt[v]; i < (int)(adj[v].size()); i++) {
        int e = adj[v][i];
        if (level[v] + 1 == level[edges[e].v] && edges[e].cap() > 0) {
            int w = dfs(edges[e].v, min(cur, edges[e].cap()));
            if (w > 0) {
                edges[e].f += w;
                edges[e ^ 1].f -= w;
                return w;
            }
        }
    }

    return 0;
}

int dinic() {
    int flow = 0;
    while (true) {
        if (!bfs()) break;
        memset(nxt, 0, sizeof nxt);
        while (int f = dfs(0, INF)) flow += f;
    }
    return flow;
}

int main() {
    ifstream fin("stall4.in");
    ofstream fout("stall4.out");

    fin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int k; fin >> k;
        for (int j = 0; j < k; j++) {
            int s; fin >> s;
            add_edge(i, n + s, 1);
        }
    }

    for (int i = 1; i <= n; i++) {
        add_edge(0, i, 1);
    }

    for (int i = n + 1; i <= n + m; i++) {
        add_edge(i, n + m + 1, 1);
    }

    fout << dinic() << '\n';

    return 0;
}

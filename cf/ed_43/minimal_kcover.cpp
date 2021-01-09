/*
 * If we connect one side of the graph to a start point, with each edge with deg(node) - k (and 
 * similarly for the other side with the end), then the edges not used in the max flow form the covering
 * needed. We can iterate k from min_deg to 0 and keep increasing the flow value with that information.
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
#define MAXN 4010

using namespace std;

struct edge {
    int u, v, f, c;
    edge(int u, int v, int c) : u(u), v(v), f(0), c(c) {}
};

int n1, n2, m;

// 0 is start, n1+n2+1 is the end
vector<int> adj[MAXN];
vector<edge> edges;
vector<int> ans[MAXN];
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
            if (edges[e].c - edges[e].f > 0 && level[edges[e].v] == -1) {
                level[edges[e].v] = level[v] + 1;
                q.push(edges[e].v);
            }
        }
    }
    return level[n1 + n2 + 1] != -1;
}

int dfs(int v, int cur) {
    if (!cur) return 0;
    if (v == n1 + n2 + 1) return cur;
    for (int& i = nxt[v]; i < (int)adj[v].size(); i++) {
        int e = adj[v][i];
        if (level[v] + 1 == level[edges[e].v] && edges[e].c - edges[e].f > 0) {
            int w = dfs(edges[e].v, min(cur, edges[e].c - edges[e].f));
            if (w) {
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
        while (int f = dfs(0, MAXN)) flow += f;
    }
    return flow;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n1 >> n2 >> m;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        b += n1;
        add_edge(a, b, 1);
    }

    int min_deg = MAXN;

    for (int i = 1; i <= n1 + n2; i++) {
        min_deg = min<int>(min_deg, adj[i].size());
    }

    // add edges from start
    for (int i = 1; i <= n1; i++) {
        add_edge(0, i, adj[i].size() - min_deg);
    }

    for (int i = n1 + 1; i <= n1 + n2; i++) {
        add_edge(i, n1 + n2 + 1, adj[i].size() - min_deg);
    }

    for (int k = min_deg; k >= 0; k--) {
        dinic();
        for (int i = 0; i < 2 * m; i += 2) {
            if (!edges[i].f) ans[k].push_back(i / 2);
        }
        
        // increase capacity
        for (int i = 2 * m; i < (int)edges.size(); i += 2) {
            edges[i].c++;
        }
    }
    
    for (int i = 0; i <= min_deg; i++) {
        cout << ans[i].size() << ' ';
        for (int x : ans[i]) cout << x + 1 << ' ';
        cout << '\n';
    }

    return 0;
}

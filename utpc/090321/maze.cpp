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

struct edge {
    int u, v, f, c;
    edge(int u, int v, int c, int d) : u(u), v(v), f(0), c(c) {}
};

vector<int> adj[MAXN];
vector<edge> edges;
int level[MAXN];
int nxt[MAXN];
int start, end;
int ind;

void add_edge(int a, int b, int c) {
        adj[a].push_back(ind++);
        edges.push_back({a, b, 1, 0});
        adj[b].push_back(ind++);
        edges.push_back({b, a, 0, 0});
        adj[b].push_back(ind++);
        edges.push_back({b, a, 1, 0});
        adj[a].push_back(ind++);
        edges.push_back({a, b, 0, 0});
}

bool bfs() {
    queue<int> q;
    q.push(start);
    memset(level, -1, sizeof level);
    level[start] = 0;
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
    return level[end] != -1;
}

int dfs(int v, int cur) {
    if (!cur) return 0;
    if (v == end) return cur;
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
        while (int f = dfs(start, INF)) flow += f;
    }
    return flow;
}

int n, m;
string grid[510];

int conv(int i, int j) {
    return 1000 * i + j; 
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (grid[i][j] != '#' && grid[i][j + 1] != '#') {
                add_edge(conv(i, j), conv(i, j + 1), 1);
            }
        }
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '#' && grid[i + 1][j] != '#') {
                add_edge(conv(i, j), conv(i + 1, j), 1);
            }
        }
    }

    array<int, 2> as, bs;
    cin >> as[0] >> as[1];
    cin >> bs[0] >> bs[1];

    start = conv(as[0], as[1]);
    ::end = conv(bs[0], bs[1]);

    cout << dinic() << '\n';

    return 0;
}

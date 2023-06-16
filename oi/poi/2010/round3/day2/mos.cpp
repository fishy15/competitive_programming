/* 
 * The question is asking us to orient each edge into a directed graph which has an euler tour and the max
 * edge cost is minimized. We can binary search on the cost. To test if we can orient a graph only using
 * edges below a certain cost (some edges will be fixed in one direction, others can be flipped), we can use
 * max flow. We will have a start node, nodes that represent each graph node, nodes that represent each edge,
 * and a final node. The capacity from the start to each node is the (degree of that node) / 2. For each 
 * edge that could possibly start at the current graph node, we can connect a capacity 1 edge in the max
 * flow graph. Finally, we can connect each edge to the final node with capacity 1. If the max flow equals 
 * m, then the edges with full capacity are the ones that we use in the orientation, and we can then find
 * the euler tour of this graph.
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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1010
#define MAXM 2010

using namespace std;

struct Dinic {
    struct edge {
        int u, v, f, c;
        edge(int u, int v, int c) : u(u), v(v), f(0), c(c) {}
    };

    int start, end;
    vector<vector<int>> adj;
    vector<edge> edges;
    vector<int> level;
    vector<int> nxt;

    Dinic(int n) {
        start = 0;
        end = n - 1;
        adj.resize(n);
        level.resize(n);
        nxt.resize(n);
    }

    void add_edge(int u, int v, int c) {
        adj[u].push_back(edges.size());
        edges.push_back({u, v, c});
        adj[v].push_back(edges.size());
        edges.push_back({v, u, 0});
    }

    bool bfs() {
        queue<int> q;
        q.push(0);
        fill(level.begin(), level.end(), -1);
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
        for (int &i = nxt[v]; i < (int)(adj[v].size()); i++) {
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
            fill(nxt.begin(), nxt.end(), 0);
            while (int f = dfs(start, INF)) flow += f;
        }
        return flow;
    }
};

struct Graph {
    vector<vector<int>> adj;
    vector<int> cur;
    deque<int> tour;

    Graph(int n) {
        adj.resize(n);
        cur.resize(n);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        cur[u]++;
    }

    void euler(int x) {
        while (cur[x]) {
            euler(adj[x][--cur[x]]);
        }
        tour.push_front(x);
    }
};

int n, m;
array<int, 4> edge[MAXM];
int deg[MAXN];

bool check(int cost) {
    Dinic g(n + m + 2);

    for (int i = 0; i < n; i++) {
        g.add_edge(0, i + 1, deg[i] / 2);
    }

    for (int i = 0; i < m; i++) {
        auto e = edge[i];
        if (cost < e[2]) return false;
        g.add_edge(e[0] + 1, n + i + 1, 1);
        if (cost >= e[3]) {
            g.add_edge(e[1] + 1, n + i + 1, 1);
        }
        g.add_edge(n + i + 1, n + m + 1, 1);
    }

    return g.dinic() == m;
}

void solve(int cost) {
    Dinic g(n + m + 2);

    for (int i = 0; i < n; i++) {
        g.add_edge(0, i + 1, deg[i] / 2);
    }

    for (int i = 0; i < m; i++) {
        auto e = edge[i];
        g.add_edge(e[0] + 1, n + i + 1, 1);
        if (cost >= e[3]) {
            g.add_edge(e[1] + 1, n + i + 1, 1);
        }
        g.add_edge(n + i + 1, n + m + 1, 1);
    }

    g.dinic();

    Graph g2(n);
    for (auto [u, v, f, c] : g.edges) {
        if (u > v) continue;
        if (u > 0 && v < n + m + 1) {
            if (f == 1) {
                auto e = edge[v - n - 1];
                if (u - 1 != e[0]) {
                    swap(e[0], e[1]);
                }
                g2.add_edge(e[0], e[1]);
            }
        }
    }

    cout << cost << '\n';
    g2.euler(0);
    deque<int> res = g2.tour;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if ((edge[j][0] == res[i] && edge[j][1] == res[i + 1]) 
                || (edge[j][1] == res[i] && edge[j][0] == res[i + 1])) {
                cout << j + 1 << ' ';
                break; 
            }
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; b--;
        if (d < c) {
            swap(a, b);
            swap(c, d);
        }
        edge[i] = {a, b, c, d};
        deg[a]++;
        deg[b]++;
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 1) {
            cout << "NIE\n";
            return 0;
        }
    }

    int l = 0;
    int r = 1000;
    int ans = -1;

    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    solve(ans);

    return 0;
}

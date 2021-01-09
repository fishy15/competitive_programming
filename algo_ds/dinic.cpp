struct edge {
    int u, v, f, c;
    edge(int u, int v, int c) : u(u), v(v), f(0), c(c) {}
};

vector<int> adj[MAXN];
vector<edge> edges;
int level[MAXN];
int nxt[MAXN];
int start, end;

void add_edge(int u, int v, int c) {
    adj[u].push_back(edges.size());
    edges.push_back({u, v, c});
    adj[v].push_back(edges.size());
    edges.push_back({v, u, 0});
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

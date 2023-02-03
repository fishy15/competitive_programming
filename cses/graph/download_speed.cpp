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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct dinic {
    struct edge {
        int u, v;
        ll f, c;
        edge(int u, int v, ll c) : u(u), v(v), f{}, c(c) {}
    };

    vector<vector<int>> adj;
    vector<edge> edges;
    vector<int> level, nxt;
    int start, end;

    dinic(int n, int start, int end) : adj(n), level(n), nxt(n), start(start), end(end) {}

    void add_edge(int u, int v, ll c) {
        adj[u].push_back(edges.size());
        edges.push_back({u, v, c});
        adj[v].push_back(edges.size());
        edges.push_back({v, u, 0});
    }

    bool bfs() {
        queue<int> q;
        q.push(start);
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

    ll dfs(int v, ll cur) {
        if (!cur) return 0;
        if (v == end) return cur;
        for (int &i = nxt[v]; i < (int) adj[v].size(); i++) {
            int e = adj[v][i];
            if (level[v] + 1 == level[edges[e].v] && edges[e].c - edges[e].f > 0) {
                ll w = dfs(edges[e].v, min(cur, edges[e].c - edges[e].f));
                if (w) {
                    edges[e].f += w;
                    edges[e ^ 1].f -= w;
                    return w;
                }
            }
        }
        return 0;
    }

    ll flow() {
        ll flow = 0;
        while (true) {
            if (!bfs()) break;
            fill(nxt.begin(), nxt.end(), 0);
            while (ll f = dfs(start, INFLL)) flow += f;
        }
        return flow;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    dinic d(n, 0, n - 1);
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        d.add_edge(a, b, c);
    }

    cout << d.flow() << '\n';

    return 0;
}

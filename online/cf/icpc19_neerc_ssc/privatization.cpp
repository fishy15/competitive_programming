/*
 * For each vertex, we need to pair up 2 * (deg - k) edges under the same company to go under the limit. This
 * can be done by matching using flows (one level is the vertices, the next are the edges), and Dinic's 
 * algorithm runs fast enough for this problem.
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
#define MAXN 1000000

using namespace std;

struct dinic {
    struct edge {
        int u, v, f, c;
        edge(int u, int v, int c) : u(u), v(v), f(0), c(c) {}
    };

    int n;
    vector<vector<int>> adj;
    vector<edge> edges;
    vector<int> level;
    vector<int> nxt;

    dinic(int n) : n(n), adj(n), level(n), nxt(n) {}

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

        return level[n - 1] != -1;
    }

    int dfs(int v, int cur) {
        if (cur == 0) return 0;
        if (v == n - 1) return cur;

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

    int flow() {
        int flow = 0;
        while (true) {
            if (!bfs()) break;
            fill(nxt.begin(), nxt.end(), 0);
            while (int f = dfs(0, INF)) {
                flow += f;
            }
        }
        return flow;
    }
};

void solve() {
    int n, m, k; cin >> n >> m >> k;
    dinic d(n + m + 2);
    vector<array<int, 2>> edges;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        d.add_edge(a, i + n + 1, 1);
        d.add_edge(b, i + n + 1, 1);
        edges.push_back({a - 1, b - 1});
    }

    int tot_needed = 0;
    for (int i = 0; i < n; i++) {
        int deg = d.adj[i + 1].size();

        int needed = max(2 * (deg - k), 0);
        if (needed > deg) {
            // impossible
            for (int i = 0; i < m; i++) {
                cout << "0 ";
            }
            cout << '\n';
            return;
        } else {
            tot_needed += needed;
            d.add_edge(0, i + 1, needed);
        }
    }

    for (int i = 0; i < m; i++) {
        d.add_edge(n + 1 + i, n + m + 1, 1);
    }

    int f = d.flow();
    if (f < tot_needed) {
        for (int i = 0; i < m; i++) {
            cout << "0 ";
        }
        cout << '\n';
        return;
    }

    vector<int> cur_double(n);
    for (int i = 0; i < n; i++) {
        cur_double[i] = 2000 * (i + 1);
    }

    vector<int> ans;
    for (int i = 0; i < m; i++) {
        if (d.edges[4 * i].f == 1) {
            ans.push_back(cur_double[edges[i][0]] / 2);
            cur_double[edges[i][0]]++;
        } else if (d.edges[4 * i + 2].f == 1) {
            ans.push_back(cur_double[edges[i][1]] / 2);
            cur_double[edges[i][1]]++;
        } else {
            ans.push_back(i + 1);
        }
    }

    vector<int> used = ans;
    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());
    
    auto get = [&](int x) { return lower_bound(used.begin(), used.end(), x) - used.begin(); };
    for (int i : ans) {
        cout << get(i) + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

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

    Dinic(int n) : start(0), end(n - 1), adj(n), level(n), nxt(n) {}

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    // 0 = source
    // 1 -- n = init pos
    // n + 1 -- 2n = final pos
    // 2n + 1 = sink
    Dinic d(2 * n + 2);
    for (int i = 0; i < n; i++) {
        d.add_edge(0, i + 1, 1);

        int left = i + p[i];
        if (left >= n) left -= n;

        d.add_edge(i + 1, left + n + 1, 1);

        d.add_edge(i + n + 1, 2 * n + 1, 1);
    }

    auto pr = [&] {
        for (int i = 0; i < n; i++) {
            if (d.edges[d.adj[i + 1][1]].f == 1) {
                cout << 'L';
            } else {
                cout << 'R';
            }
        }
        cout << '\n';
    };

    auto max_flow = d.dinic();

    if (max_flow == n) {
        pr();
    } else {
        for (int i = n - 1; i >= 0; i--) {
            int right = i - p[i];
            if (right < 0) right += n;

            d.add_edge(i + 1, right + n + 1, 1);
            max_flow += d.dinic();

            if (max_flow == n) {
                pr();
                return 0;
            }
        }

        cout << "no dance\n";
    }

    return 0;
}

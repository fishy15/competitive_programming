/*
 * This is a case of the project selection problem. To build the edges, we cannot directly connect 
 * everything since there can be up to O(n^2) edges (ex. if all the a_i values are the same), but we can 
 * form an edge from the current index i to the rightmost value of each divisor of a_i within [1..i - 1]. 
 * If i < j, d_i == d_j, and d_i | d_k, then if we connect k to j, then we already have the requirement
 * for k to i satisfied through j to i.
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
#define MAXN 3010

using namespace std;

int n;
int a[MAXN];
int b[MAXN];
int pos[110];

struct edge {
    int u, v, c, f;
    edge(int u, int v, int c) : u(u), v(v), c(c), f(0) {}
    edge() : edge(0, 0, 0) {}
};

vector<int> adj[MAXN];
vector<edge> edges;
int level[MAXN];
int nxt[MAXN];

void add_edge(int u, int v, int c) {
    adj[u].push_back(edges.size());
    edges.push_back(edge(u, v, c));
    adj[v].push_back(edges.size());
    edges.push_back(edge(v, u, 0));
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
    return level[n + 1] != -1;
}

int dfs(int v, int cur) {
    if (!cur) return 0;
    if (v == n + 1) return cur;
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

int flow() {
    int flow = 0;
    while (true) {
        if (!bfs()) break;
        memset(nxt, 0, sizeof nxt);
        while (int f = dfs(0, INF)) flow += f;
    }
    return flow;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    memset(pos, -1, sizeof pos);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= a[i]; j++) {
            if (a[i] % j == 0 && pos[j] != -1) {
                add_edge(i, pos[j], INF);
            }
        }
        pos[a[i]] = i;
    }

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (b[i] >= 0) {
            add_edge(0, i, b[i]);
            sum += b[i];
        } else {
            add_edge(i, n + 1, -b[i]);
        }
    }

    int x = flow();
    cout << max(0, sum - x) << '\n';

    return 0;
}

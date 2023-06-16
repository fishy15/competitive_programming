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
#define MAXN 100010

using namespace std;

int n, m;
// {u, w, in}
vector<array<int, 3>> adj[MAXN];
set<pair<int, int>> ex;
array<int, 3> extra[40];
ll depth[MAXN];
ll dist[40][2][MAXN];
bool vis[MAXN];
int idx;
int in[MAXN];
int out[MAXN];
int up[MAXN][20];
int t;

void dfs(int v, int p) {
    vis[v] = true;
    up[v][0] = p;
    in[v] = t++;
    for (int i = 1; i < 20; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto &e : adj[v]) {
        if (e[0] != p) {
            if (!vis[e[0]]) {
                e[2] = true;
                depth[e[0]] = depth[v] + e[1];
                dfs(e[0], v);
            } else {
                if (!ex.count({v, e[0]}) && !ex.count({e[0], v})) {
                    extra[idx++] = {v, e[0], e[1]};
                    ex.insert({v, e[0]});
                }
            }
        }
    }
    out[v] = t++;
}

bool anc(int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}

int lca(int a, int b) {
    if (anc(a, b)) return a;
    if (anc(b, a)) return b;
    for (int i = 19; i >= 0; i--) {
        if (!anc(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

ll dd(int a, int b) {
    if (anc(a, b)) return depth[b] - depth[a];
    if (anc(b, a)) return depth[a] - depth[b];
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

void dijkstra(int i) {
    // start at first point
    memset(vis, 0, sizeof vis);
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq;
    pq.push({0, extra[i][0]});
    int cnt = 0;
    while (cnt < n) {
        auto [d, cur] = pq.top();
        pq.pop();
        if (vis[cur]) continue;
        dist[i][0][cur] = d;
        vis[cur] = true;
        cnt++;
        for (auto e : adj[cur]) {
            if (!vis[e[0]]) {
                pq.push({d + e[1], e[0]});
            }
        }
    }

    // start at other point
    memset(vis, 0, sizeof vis);
    pq = {};
    pq.push({0, extra[i][1]});
    cnt = 0;
    while (cnt < n) {
        auto [d, cur] = pq.top();
        pq.pop();
        if (vis[cur]) continue;
        dist[i][1][cur] = d;
        vis[cur] = true;
        cnt++;
        for (auto e : adj[cur]) {
            if (!vis[e[0]]) {
                pq.push({d + e[1], e[0]});
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c, 0});
        adj[b].push_back({a, c, 0});
    }

    dfs(0, 0);
    for (int i = 0; i < idx; i++) {
        dijkstra(i);
    }

    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        a--; b--;
        ll ans = dd(a, b);
        for (int i = 0; i < idx; i++) {
            ans = min(ans, dist[i][0][a] + dist[i][1][b] + extra[i][2]);
            ans = min(ans, dist[i][1][a] + dist[i][0][b] + extra[i][2]);
        }
        cout << ans << '\n';
    }

    return 0;
}

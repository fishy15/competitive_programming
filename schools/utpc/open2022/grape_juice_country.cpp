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

struct Edge
{
    ll from, to, capacity, cost;
};

vector<vector<ll>> adj, cost, capacity;

void shortest_paths(ll n, ll v0, vector<ll>& d, vector<ll>& p) {
    d.assign(n, INFLL);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<ll> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        inq[u] = false;
        for (ll v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

ll min_cost_flow(ll N, vector<Edge> edges, ll s, ll t) {
    adj.assign(N, vector<ll>());
    cost.assign(N, vector<ll>(N, 0));
    capacity.assign(N, vector<ll>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    ll flow = 0;
    ll cost = 0;
    vector<ll> d, p;
    while (true) {
        shortest_paths(N, s, d, p);
        if (d[t] == INFLL)
            break;

        // find max flow on that path
        ll f = INFLL;
        ll cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        if (f * d[t] > 0) break;
        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    return cost;
}

int n, m;
vector<Edge> edges;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    // 0 = source
    // [1, m] = edges
    // [m + 1, m + 2n] = nodes
    // m + 2n + 1 = sink
    for (int i = 1; i <= n; i++) {
        int r; cin >> r;
        Edge e;
        e.from = m + 2 * i - 1;
        e.to = m + 2 * n + 1;
        e.capacity = INFLL;
        e.cost = r; 
        edges.push_back(e);
    }

    for (int i = 1; i <= n; i++) {
        int g; cin >> g;
        Edge e;
        e.from = m + 2 * i;
        e.to = m + 2 * n + 1;
        e.capacity = INFLL;
        e.cost = g; 
        edges.push_back(e);
    }

    for (int i = 1; i <= m; i++) {
        int a, b, s; cin >> a >> b >> s;
        // edge from source
        Edge src;
        src.from = 0;
        src.to = i;
        src.capacity = 1;
        src.cost = -s;
        edges.push_back(src);

        // edge to r
        Edge to_r;
        to_r.from = i;
        to_r.to = m + 2 * a - 1;
        to_r.capacity = INFLL;
        to_r.cost = 0;
        edges.push_back(to_r);

        // edge to g
        Edge to_g;
        to_g.from = i;
        to_g.to = m + 2 * b;
        to_g.capacity = INFLL;
        to_g.cost = 0;
        edges.push_back(to_g);
    }

    for (auto e : edges) {
        cout << e.from << ' ' << e.to << ' ' << e.capacity << ' ' << e.cost << '\n';
    }

    ll ans = -min_cost_flow(m + 2 * n + 2, edges, 0, m + 2 * n + 1);
    cout << ans << '\n';

    return 0;
}

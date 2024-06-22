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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define sz(x) (int)((x).size())
using vi = vector<int>;

template<class T> T edmondsKarp(vector<unordered_map<int, T>>& graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vi par(sz(graph)), q = par;

    for (;;) {
        fill(all(par), -1);
        par[source] = 0;
        int ptr = 1;
        q[0] = source;

        rep(i,0,ptr) {
            int x = q[i];
            for (auto e : graph[x]) {
                if (par[e.first] == -1 && e.second > 0) {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if (e.first == sink) goto out;
                }
            }
        }
        return flow;
out:
        T inc = numeric_limits<T>::max();
        for (int y = sink; y != source; y = par[y])
            inc = min(inc, graph[par[y]][y]);
        flow += inc;
        for (int y = sink; y != source; y = par[y]) {
            int p = par[y];
            if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
            graph[y][p] += inc;
        }
    }
}

vector<int> dijk(const vector<vector<pair<int, int>>> &adj) {
    int n = sz(adj);

    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [dd, v] = pq.top();
        pq.pop();

        if (dist[v] != dd) continue;
        for (auto [e, w] : adj[v]) {
            if (dist[e] > dist[v] + w) {
                dist[e] = dist[v] + w;
                pq.push({dist[e], e});
            }
        }
    }

    return dist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, c;
    cin >> n >> m >> c;

    vector<vector<pair<int, int>>> adj(n);
    vector<array<int, 3>> edges;
    for (int i = 0; i < m; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        x--;
        y--;

        adj[x].push_back({y, t});
        adj[y].push_back({x, t});
        edges.push_back({x, y, t});
    }

    vector<int> comm(c);
    rep(i, 0, c) {
        cin >> comm[i];
        comm[i]--;
    }

    auto dist = dijk(adj);

    map<int, vector<int>> at_d;
    for (auto cc : comm) {
        at_d[dist[cc]].push_back(cc);
    }

    int source = n;
    int sink = 0;
    vector<unordered_map<int, int>> gr(n+1);

    for (auto [x, y, t] : edges) {
        if (dist[x] + t == dist[y]) {
            gr[y][x]++;
        } else if (dist[x] == dist[y] + t) {
            gr[x][y]++;
        }
    }

    int ans = 0;
    for (auto &[_, locs] : at_d) {
        auto cur_gr = gr;
        for (auto x : locs) {
            cur_gr[source][x]++;
        }
        ans += edmondsKarp(cur_gr, source, sink);
    }

    cout << ans << '\n';

    return 0;
}

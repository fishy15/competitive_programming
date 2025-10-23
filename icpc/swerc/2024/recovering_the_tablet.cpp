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
#include <climits>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vii = vector<pii>;

struct mcmf {
    const ll inf = LLONG_MAX >> 2;
    struct edge {
        int v;
        ll cap, flow, cost;
    };
    int n;
    vector<edge> edges;
    vvi adj; vii par; vi in_q;
    vector<ll> dist, pi;
    mcmf(int n) : n(n), adj(n), dist(n), pi(n), par(n), in_q(n) {}
    void add_edge(int u, int v, ll cap, ll cost) {
        int idx = sz(edges);
        edges.push_back({v, cap, 0, cost});
        edges.push_back({u, cap, cap, -cost});
        adj[u].push_back(idx);
        adj[v].push_back(idx^1);
    }
    bool find_path(int s, int t) {
        fill(all(dist), inf);
        fill(all(in_q), 0);
        queue<int> q; q.push(s);
        dist[s] = 0, in_q[s] = 1;
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            in_q[cur] = 0;
            for(int idx : adj[cur]) {
                auto [nxt, cap, fl, wt] = edges[idx];
                ll nxtD = dist[cur] + wt;
                if(fl >= cap || nxtD >= dist[nxt]) continue;
                dist[nxt] = nxtD;
                par[nxt] = {cur, idx};
                if(in_q[nxt]) continue;
                q.push(nxt); in_q[nxt] = 1;
            }
        }
        return dist[t] < inf;
    }
    pair<ll, ll> calc(int s, int t) {
        ll flow = 0, cost = 0;
        while(find_path(s, t)) {
            rep(i, 0, n) pi[i] = min(pi[i] + dist[i], inf);
            ll f = inf;
            for(int i, u, v = t; tie(u, i) = par[v], v != s; v = u)
                f = min(f, edges[i].cap - edges[i].flow);
            flow += f;
            for(int i, u, v = t; tie(u, i) = par[v], v != s; v = u)
                edges[i].flow += f, edges[i^1].flow -= f;
        }
        rep(i, 0, sz(edges)>>1)
            cost += edges[i << 1].cost * edges[i<<1].flow;
        return {flow, cost};
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, s;
    cin >> n >> m >> s;

    vector<string> grid(n);
    rep(i, 0, n) {
        cin >> grid[i];
    }

    vector h_goals(n, vector(m, -1));
    vector v_goals(n, vector(m, -1));

    rep(i, 0, s) {
        char c;
        int x, y, s;
        cin >> c >> x >> y >> s;
        x--;
        y--;
        if (c == 'H') {
            h_goals[x][y] = s;
        } else {
            v_goals[x][y] = s;
        }
    }

    auto left = [&](int x, int y) {
        return x * m + y;
    };
    auto right = [&](int x, int y) {
        return n * m + x * m + y;
    };

    int src = 2 * n * m;
    int snk = src + 1;

    auto gr = mcmf(snk + 1);

    ll h_sum = 0;
    ll v_sum = 0;
    ll base = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (grid[i][j] == '0') {
                if (v_goals[i][j] != -1) {
                    rep(k, i+1, n) {
                        if (grid[k][j] == '0') break;
                        v_goals[i][j]--; // normalize to 0..8
                        gr.add_edge(left(i, j), left(k, j), INF, 0);
                    }
                    if (v_goals[i][j] < 0) {
                        cout << "IMPOSSIBLE\n";
                        return 0;
                    }
                    gr.add_edge(src, left(i, j), v_goals[i][j], 0);
                    v_sum += v_goals[i][j];
                }
                if (h_goals[i][j] != -1) {
                    rep(k, j+1, m) {
                        if (grid[i][k] == '0') break;
                        h_goals[i][j]--;
                        gr.add_edge(right(i, k), right(i, j), INF, 0);
                    }
                    if (h_goals[i][j] < 0) {
                        cout << "IMPOSSIBLE\n";
                        return 0;
                    }
                    gr.add_edge(right(i, j), snk, h_goals[i][j], 0);
                    h_sum += h_goals[i][j];
                }
            } else {
                int v = grid[i][j] - '1';
                gr.add_edge(left(i, j), right(i, j), v, -1);
                gr.add_edge(left(i, j), right(i, j), 8 - v, 1);
                base += v;
            }
        }
    }

    auto f = gr.calc(src, snk);
    if (h_sum != v_sum || h_sum != f.first) {
        cout << "IMPOSSIBLE\n";
    } else {
        auto ans = base + f.second;
        cout << ans << '\n';
    }

    return 0;
}

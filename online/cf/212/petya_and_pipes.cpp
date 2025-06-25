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

#include <bits/extc++.h>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

const ll INF = numeric_limits<ll>::max() / 4;

using vi = vector<int>;

struct MCMF {
    struct edge {
        int from, to, rev;
        ll cap, cost, flow;
    };
    int N;
    vector<vector<edge>> ed;
    vi seen;
    vector<ll> dist, pi;
    vector<edge*> par;

    MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

    void addEdge(int from, int to, ll cap, ll cost) {
        if (from == to) return;
        ed[from].push_back(edge{ from,to,sz(ed[to]),cap,cost,0 });
        ed[to].push_back(edge{ to,from,sz(ed[from])-1,0,-cost,0 });
    }

    void path(int s) {
        fill(all(seen), 0);
        fill(all(dist), INF);
        dist[s] = 0; ll di;

        __gnu_pbds::priority_queue<pair<ll, int>> q;
        vector<decltype(q)::point_iterator> its(N);
        q.push({ 0, s });

        while (!q.empty()) {
            s = q.top().second; q.pop();
            seen[s] = 1; di = dist[s] + pi[s];
            for (edge& e : ed[s]) if (!seen[e.to]) {
                ll val = di - pi[e.to] + e.cost;
                if (e.cap - e.flow > 0 && val < dist[e.to]) {
                    dist[e.to] = val;
                    par[e.to] = &e;
                    if (its[e.to] == q.end())
                        its[e.to] = q.push({ -dist[e.to], e.to });
                    else
                        q.modify(its[e.to], { -dist[e.to], e.to });
                }
            }
        }
        rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
    }

    pair<ll, ll> maxflow(int s, int t) {
        ll totflow = 0, totcost = 0;
        while (path(s), seen[t]) {
            ll fl = INF;
            for (edge* x = par[t]; x; x = par[x->from])
                fl = min(fl, x->cap - x->flow);

            totflow += fl;
            for (edge* x = par[t]; x; x = par[x->from]) {
                x->flow += fl;
                ed[x->to][x->rev].flow -= fl;
            }
        }
        rep(i,0,N) for(edge& e : ed[i]) totcost += e.cost * e.flow;
        return {totflow, totcost/2};
    }

    // If some costs can be negative, call this before maxflow:
    void setpi(int s) { // (otherwise, leave this out)
        fill(all(pi), INF); pi[s] = 0;
        int it = N, ch = 1; ll v;
        while (ch-- && it--)
            rep(i,0,N) if (pi[i] != INF)
              for (edge& e : ed[i]) if (e.cap)
                  if ((v = pi[i] + e.cost) < pi[e.to])
                      pi[e.to] = v, ch = 1;
        assert(it >= 0); // negative cost cycle
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    MCMF gr(n + 1);

    vector grid(n, vector<int>(n));

    rep(i, 0, n) {
        rep(j, 0, n) {
            int c;
            cin >> c;
            grid[i][j] = c;
            if (c != 0) {
                gr.addEdge(i, j, c, 0);
            }
        }
    }

    auto orig = gr;
    auto [flow, _] = orig.maxflow(0, n-1);

    gr.addEdge(n, 0, flow, 0);
    rep(i, 0, n) {
        rep(j, 0, n) {
            if (grid[i][j] != 0) {
                gr.addEdge(i, j, k, 1);
            }
        }
    }

    auto [ans, __] = orig.maxflow(n, n-1);
    while (true) {
        gr.addEdge(n, 0, 1, 0);
        auto [newflow, newcost] = gr.maxflow(n, n-1);
        if (newflow != 0 && newcost <= k) {
            ans += newflow;
        } else {
            break;
        }
    }

    cout << ans << '\n';

    return 0;
}

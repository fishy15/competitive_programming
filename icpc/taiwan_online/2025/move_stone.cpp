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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

using vi = vector<int>;
#define pb push_back

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vi> hs; vi H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

    void addEdge(int s, int t, ll cap, ll rcap=0) {
        if (s == t) return;
        g[s].pb({t, sz(g[t]), 0, cap});
        g[t].pb({s, sz(g[s])-1, 0, rcap});
    }

    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].pb(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    
    ll calc(int s, int t) {
        int v = sz(g); H[s] = v; ec[t] = 1;
        vi co(2*v); co[0] = v-1;
        rep(i,0,v) cur[i] = g[i].data();
        for (Edge& e : g[s]) addFlow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0)
                if (cur[u] == g[u].data() + sz(g[u])) {
                    H[u] = 1e9;
                    for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
                        H[u] = H[e.dest]+1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        rep(i,0,v) if (hi < H[i] && H[i] < v)
                            --co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector grid(n, vector(n, -1));
    vector<pair<int, int>> empty;
    vector<pair<int, int>> extra;

    rep(i, 0, n) {
        rep(j, 0, n) {
            cin >> grid[i][j];
            if (grid[i][j] == 0) {
                empty.push_back({i, j});
            } else if (grid[i][j] > 1) {
                extra.push_back({i, j});
            }
        }
    }

    auto comp_extra = [&](int x, int y) {
        return x * n + y;
    };

    auto row = [&](int x) {
        return n * n + x;
    };

    auto col = [&](int x) {
        return n * n + n + x;
    };

    auto comp_empty = [&](int x, int y) {
        return n * n + 2 * n + x * n + y;
    };

    int src = n*n + 2*n + n*n;
    int snk = src + 1;
    PushRelabel gr(snk + 1);

    for (auto [x, y] : extra) {
        gr.addEdge(src, comp_extra(x, y), grid[x][y] - 1);
        gr.addEdge(comp_extra(x, y), row(x), INF);
        gr.addEdge(comp_extra(x, y), col(y), INF);
    }

    for (auto [x, y] : empty) {
        gr.addEdge(row(x), comp_empty(x, y), INF);
        gr.addEdge(col(y), comp_empty(x, y), INF);
        gr.addEdge(comp_empty(x, y), snk, 1);
    }

    auto ans = 2 * sz(empty) - gr.calc(src, snk);
    cout << ans << '\n';

    return 0;
}

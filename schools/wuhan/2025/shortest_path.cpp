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

#define pb push_back
using vi = vector<int>;

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
            while (ec[u] > 0)  // discharge u
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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> ws(m);
    rep(i, 0, m) {
        cin >> ws[i];
    }

    vector<int> d(n);
    rep(i, 0, n) {
        cin >> d[i];
    }

    if (d[0] != 0) {
        cout << "NO\n";
        return;
    } else if (n == 1) {
        // no place to put singular edge
        cout << "NO\n";
        return;
    }

    sort(all(d));

    // collect weights
    map<int, int> w_cnt_m;
    for (auto w : ws) {
        w_cnt_m[w]++;
    }

    vector<pair<int, int>> w_cnt(all(w_cnt_m));

    int src = sz(w_cnt) + (n - 1);
    int sink = src + 1;

    auto get_w = [&](int w) {
        auto it = lower_bound(all(w_cnt), pair{w, 0});
        if (it != end(w_cnt) && it->first == w) {
            return (int) (it - begin(w_cnt));
        }
        return -1;
    };

    auto get_node = [&](int x) {
        return sz(w_cnt) + (x - 1);
    };

    PushRelabel g(sink + 1);
    
    // source to weight groups
    rep(w_idx, 0, sz(w_cnt)) {
        g.addEdge(src, w_idx, w_cnt[w_idx].second);
    }

    bool with_min = false;

    rep(v, 1, n) {
        g.addEdge(get_node(v), sink, 1);
        rep(p, 0, v) {
            auto dist = d[v] - d[p];
            auto w_idx = get_w(dist);
            if (w_idx != -1) {
                g.addEdge(w_idx, get_node(v), 1);
                if (w_idx == 0) {
                    with_min = true;
                }
            }
        }
    }

    // even if min weight is not used in this flow,
    // we can swap it out to get some flow that works,
    // so we simply need to check that we could assign it to something
    auto f = g.calc(src, sink);
    if (with_min && f == n-1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

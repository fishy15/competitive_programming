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

struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); }
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0) {
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
    }
    ll dfs(int v, int t, ll f) {
        if (v == t || !f) return f;
        for (int& i = ptr[v]; i < sz(adj[v]); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(int s, int t) {
        ll flow = 0; q[0] = s;
        rep(L,0,31) do {
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                for (Edge e : adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while (lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ifstream fin("colorful.in");
    ofstream fout("colorful.out");

    int n, m, k;
    fin >> n >> m >> k;

    auto left_only = [&](int x) {
        return x;
    };
    auto right_only = [&](int x) {
        return x + n;
    };
    auto left = [&](int x, int c) {
        return 2*n + k * x + c;
    };
    auto right = [&](int x, int c) {
        return 2*n + k*n + k * x + c;
    };
    int source = 2*n + 2*k*n;
    int sink = source + 1;

    Dinic g(sink + 1);
    // source to node, node to sink
    rep(i, 0, n) {
        g.addEdge(source, left_only(i), 2);
        g.addEdge(right_only(i), sink, 2);
        rep(c, 0, k) {
            g.addEdge(left_only(i), left(i, c), 1);
            g.addEdge(right(i, c), right_only(i), 1);
        }
    }

    vector<array<int, 3>> edges;
    rep(i, 0, m) {
        int a, b, c;
        fin >> a >> b >> c;
        a--;
        b = -b - 1;
        c--;
        g.addEdge(left(a, c), right(b, c), 1);
        edges.push_back({a, b, c});
    }

    auto f = g.calc(source, sink);
    if (f == 2 * n) {
        // throw out unnecesssary edges
        vector<vector<int>> small(2*n);
        for (auto [a, b, c] : edges) {
            for (auto e : g.adj[left(a, c)]) {
                if (e.to == right(b, c) && e.c == 0) {
                    small[a].push_back(b+n);
                    small[b+n].push_back(a);
                }
            }
        }
        
        // find cycles on small
        vector<bool> vis(2*n);
        vector<vector<int>> ans;
        rep(i, 0, n) {
            if (!vis[i]) {
                vector<int> cycle;
                int cur = i;
                while (true) {
                    vis[cur] = true;
                    cycle.push_back(cur);
                    bool found = false;
                    for (auto e : small[cur]) {
                        if (!vis[e]) {
                            cur = e;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        break;
                    }
                }
                ans.push_back(cycle);
            }
        }

        fout << "YES\n";
        fout << sz(ans) << '\n';
        for (const auto &v : ans) {
            fout << sz(v) << ' ';
            for (auto x : v) {
                if (x < n) {
                    fout << x + 1 << ' ';
                } else {
                    fout << -(x - n + 1) << ' ';
                }
            }
            fout << '\n';
        }
    } else {
        fout << "NO\n";
    }

    return 0;
}

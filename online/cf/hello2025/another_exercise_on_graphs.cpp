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

struct DSU {
    vector<int> dsu;
    vector<int> size;

    DSU(int n) : dsu(n), size(n, 1) {
        iota(dsu.begin(), dsu.end(), 0);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (size[x] < size[y]) swap(x, y);
            dsu[y] = x;
            size[x] += size[y];
        }
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<array<int, 3>> edges;
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        edges.push_back({w, u, v});
    }

    sort(all(edges));

    vector<array<int, 3>> qrys;
    rep(i, 0, q) {
        int a, b, k;
        cin >> a >> b >> k;
        a--;
        b--;
        qrys.push_back({a, b, k});
    }

    vector<pair<int, int>> search(q, {0, m});
    vector<int> ans(q, -1);

    vector init_dist(n, vector(n, INF));
    rep(i, 0, n) {
        init_dist[i][i] = 0;
    }
    for (auto [_, u, v] : edges) {
        init_dist[u][v] = 1;
        init_dist[v][u] = 1;
    }

    rep(k, 0, n) {
        rep(i, 0, n) {
            rep(j, 0, n) {
                init_dist[i][j] = min(init_dist[i][j], init_dist[i][k] + init_dist[k][j]);
            }
        }
    }

    while (true) {
        // if only the edges < position are 0, rest are 1
        vector<vector<int>> qry_at(m+1);
        bool cont = false;
        rep(i, 0, q) {
            auto [l, r] = search[i];
            if (l <= r) {
                qry_at[(l + r) / 2].push_back(i);
                cont = true;
            }
        }

        if (!cont) {
            break;
        }

        DSU dsu(n);
        vector dist = init_dist;

        auto update_edge = [&](int u, int v, int w) {
            if (dsu.find(u) != dsu.find(v)) {
                dsu.join(u, v);
                rep(a, 0, n) {
                    rep(b, 0, n) {
                        dist[a][b] = min(dist[a][b], dist[a][u] + w + dist[v][b]);
                        dist[a][b] = min(dist[a][b], dist[a][v] + w + dist[u][b]);
                    }
                }
            }
        };

        auto process_queries = [&](int m) {
            for (auto qidx : qry_at[m]) {
                auto [a, b, k] = qrys[qidx];
                auto [l, r] = search[qidx];
                if (dist[a][b] < k) {
                    search[qidx] = {l, m-1};
                    ans[qidx] = edges[m-1][0];
                } else {
                    search[qidx] = {m+1, r};
                }
            }
        };

        process_queries(0);
        rep(i, 0, m) {
            auto [w, u, v] = edges[i];
            update_edge(u, v, 0);
            process_queries(i+1);
        }
    }

    rep(i, 0, q) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto comp_dist = [&](vector<int> &dist, vector<int> &par, int st) {
        fill(all(dist), INF);
        auto dfs = [&](auto &&self, int v, int p, int d) -> void {
            dist[v] = d;
            par[v] = p;
            for (auto e : adj[v]) {
                if (e != p) {
                    self(self, e, v, d + 1);
                }
            }
        };
        dfs(dfs, st, st, 0);
    };

    vector<int> dist1(n);
    vector<int> par(n);

    comp_dist(dist1, par, 0);
    auto d1 = (int) (max_element(all(dist1)) - begin(dist1));

    comp_dist(dist1, par, d1);
    auto d2 = (int) (max_element(all(dist1)) - begin(dist1));

    auto diam = dist1[d2];
    auto mid = d2;
    rep(i, 0, diam / 2) {
        mid = par[mid];
    }

    vector<int> dist2(n), dist_mid(n);
    comp_dist(dist2, par, d2);
    comp_dist(dist_mid, par, mid);

    auto works = [&](int root) {
        // check if cur works as answer
        vector<int> dist(n);
        comp_dist(dist, par, root);
        vector<int> deg_at_dist(n, -1);
        rep(v, 0, n) {
            auto d = dist[v];
            if (deg_at_dist[d] == -1) {
                deg_at_dist[d] = sz(adj[v]);
            } else if (deg_at_dist[d] != sz(adj[v])) {
                return false;
            }
        }
        return true;
    };

    if (works(d1)) {
        cout << d1 + 1 << '\n';
    } else if (works(d2)) {
        cout << d2 + 1 << '\n';
    } else if (works(mid)) {
        cout << mid + 1 << '\n';
    } else {
        auto to_try = pair{INF, -1};
        rep(v, 0, n) {
            if (sz(adj[v]) == 1 && dist1[v] == dist2[v]) {
                to_try = min(to_try, pair{dist_mid[v], v});
            }
        }
        if (to_try.second != -1 && works(to_try.second)) {
            cout << to_try.second + 1 << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}

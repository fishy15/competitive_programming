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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

pair<int, int> solve_slow(int n, vector<vector<int>> &adj, int max_time) {
    // stores min time that we need to wait to get there
    vector<int> cur_dist(max_time + 1, INF);
    auto nxt_dist = cur_dist;

    cur_dist[0] = 0;
    pair<int, int> ans{INF, INF};

    rep(t, 0, 3*n) {
        rep(v, 0, n) {
            // stay at the same place
            ckmin(nxt_dist[v], cur_dist[v] + 1);

            auto nxt = adj[v][t % sz(adj[v])];
            ckmin(nxt_dist[nxt], cur_dist[v]);
        }

        if (cur_dist[n-1] != INF) {
            ckmin(ans, pair{t, cur_dist[n-1]});
        }
        swap(cur_dist, nxt_dist);
        fill(all(nxt_dist), INF); 
    }

    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        if (u != v) {
            adj[v].push_back(u);
        }
    }

    auto [t, wt] = solve_slow(n, adj, 3 * n);
    cout << t << ' ' << wt << '\n';
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

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

vector<int> toposort(const vector<vector<int>> &dag) {
    int n = sz(dag);
    vector<int> deg(n);
    rep(u, 0, n) {
        for (auto v : dag[u]) {
            deg[v]++;
        }
    }

    queue<int> zero;
    rep(u, 0, n) {
        if (deg[u] == 0) {
            zero.push(u);
        }
    }

    vector<int> ord;
    while (!zero.empty()) {
        int u = zero.front();
        zero.pop();

        ord.push_back(u);
        for (auto v : dag[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                zero.push(v);
            }
        }
    }

    return ord;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, d;
    cin >> n >> m >> d;

    vector<vector<pair<int, ll>>> adj(n);
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
    }

    set<ll> marked;
    rep(i, 0, d) {
        ll x;
        cin >> x;
        marked.insert(x);
    }

    vector<ll> dist(n, INFLL);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [cd, u] = pq.top();
        pq.pop();
        if (cd != dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (cd + w < dist[v]) {
                dist[v] = cd + w;
                pq.push({dist[v], v});
            }
        }
    }

    auto not_present = marked;
    rep(i, 0, n) {
        not_present.erase(dist[i]);
    }

    if (!not_present.empty()) {
        cout << "0\n";
        return 0;
    }

    vector<vector<int>> dag(n), rev(n);
    rep(u, 0, n) {
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w == dist[v]) {
                auto it = marked.upper_bound(dist[u]);
                if (it == end(marked) || *it >= dist[v]) {
                    // ensure we are not skipping some marked element
                    dag[u].push_back(v);
                    rev[v].push_back(u);
                }
            }
        }
    }

    auto ord = toposort(dag);
    vector<ll> dp(n);
    for (auto u : ord) {
        if (u == 0) {
            dp[u] = 1;
        }
        for (auto v : dag[u]) {
            dp[v] += dp[u];
            // compress number of paths back down
            if (dp[v] >= 2) {
                dp[v] = 2;
            }
        }
    }

    if (dp[n-1] == 1) {
        vector<int> path = {n-1};
        int cur = n-1;
        while (cur != 0) {
            for (auto x : rev[cur]) {
                if (dp[x] != 0) {
                    cur = x;
                    break;
                }
            }
            path.push_back(cur);
        }

        reverse(all(path));

        cout << sz(path) << '\n';
        for (auto x : path) cout << x + 1 << '\n';
    } else {
        if (dp[n-1] == 0) {
            cout << "0\n";
        } else {
            cout << "1\n";
        }
    }

    return 0;
}

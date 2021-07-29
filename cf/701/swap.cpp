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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<int> par(n);
    vector<int> dist(n);
    vector<vector<int>> level(n);
    vector<ll> cost(n);
    vector<ll> ans(n);
    vector<ll> max_c(n), min_c(n);

    for (int i = 1; i < n; i++) {
        int v; cin >> v; v--;
        adj[i].push_back(v);
        adj[v].push_back(i);
    }

    for (int i = 0; i < n - 1; i++) {
        cin >> cost[i + 1];
    }

    function<void(int,int,int)> dfs = [&](int v, int p, int d) {
        dist[v] = d;
        par[v] = p;
        level[d].push_back(v);
        for (int e : adj[v]) {
            if (e != p) {
                dfs(e, v, d + 1);
            }
        }
    };


    dfs(0, 0, 0);
    for (int d = n - 1; d > 0; d--) {
        if (level[d].empty()) continue;
        sort(level[d].begin(), level[d].end(), [&](int x, int y) {
            if (cost[x] == cost[y]) return x < y;
            return cost[x] < cost[y];
        });

        // calculate best child
        for (int v : level[d]) {
            for (int e : adj[v]) {
                if (e != par[v]) {
                    ans[v] = max(ans[e], ans[v]);
                }
            }
        }

        // blue has lower cost
        ll best = -INFLL;
        for (int v : level[d]) {
            min_c[v] = best;
            best = max(best, ans[v] - cost[v]);
        }

        // blue has higher cost
        best = -INF;
        for (auto it = level[d].rbegin(); it != level[d].rend(); it++) {
            int v = *it;
            max_c[v] = best;
            best = max(best, cost[v] + ans[v]);
        }

        ll min_cost = cost[level[d].front()];
        ll max_cost = cost[level[d].back()];
        // find actual best cost
        for (int v : level[d]) {
            ans[v] = max({min_c[v] + cost[v], max_c[v] - cost[v], ans[v] + cost[v] - min_cost, ans[v] + max_cost - cost[v]});
        }
    }

    ll val = 0;
    for (int v : adj[0]) {
        val = max(val, ans[v]);
    }
    cout << val << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

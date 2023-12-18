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

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<pair<ll, ll>> costs(n);
    for (int i = 0; i < n; i++) {
        cin >> costs[i].first >> costs[i].second;
    }

    vector adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // compute distances from zero
    vector dist(n, INF);
    queue<int> q;
    q.push(0);
    dist[0] = 0;

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (auto e : adj[v]) {
            if (dist[e] == INF) {
                dist[e] = dist[v] + 1;
                q.push(e);
            }
        }
    }

    // max_i (a_i - (dist_i + 1) b_i)
    multiset<ll> base_ans;
    for (int i = 0; i < n; i++) {
        auto [a, b] = costs[i];
        base_ans.insert(a - (dist[i] + 1) * b);
    }

    // construct graph
    vector dag(2 * n, vector<int>());
    for (int u = 0; u < n; u++) {
        for (auto v : adj[u]) {
            if (dist[u] + 1 == dist[v]) {
                dag[u].push_back(v);
                dag[u + n].push_back(v + n);
            } else if (dist[u] == dist[v]) {
                dag[u].push_back(v + n);
            }
        }
    }

    // ignore these for now since the max can't include itself
    vector adj_to_0(n, false);
    for (auto e : adj[0]) {
        adj_to_0[e] = true;
    }

    vector vis(2 * n, false);

    vector<ll> ans(2 * n, -INFLL);
    for (int i = 0; i < n; i++) {
        if (!adj_to_0[i]) {
            auto [a, b] = costs[i];
            ans[i] = a - (dist[i] - 1) * b;
            ans[i + n] = a - dist[i] * b;
        }
    }

    auto solve = [&](auto solve, int v) -> ll {
        if (!vis[v]) {
            vis[v] = true;
            for (auto e : dag[v]) {
                ans[v] = max(ans[v], solve(solve, e));
            }
        }
        return ans[v];
    };

    vector<ll> res;
    sort(adj[0].begin(), adj[0].end());
    for (auto e : adj[0]) {
        auto score = solve(solve, e);
        // find answer among others
        for (auto e2 : adj[e]) {
            auto [a, b] = costs[e2];
            score = max(score, a - b);
        }

        auto [a, b] = costs[e];
        auto base_cur = a - 2 * b;
        base_ans.erase(base_ans.find(base_cur));
        score = max(score, *base_ans.rbegin());

        res.push_back(score);

        base_ans.insert(base_cur);
    }

    for (auto x : res) {
        cout << x << '\n';
    }

    return 0;
}

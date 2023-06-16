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

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);

    auto get_edge = [&](int u, int idx) {
        if (edges[idx].first == u) {
            return edges[idx].second;
        }
        return edges[idx].first;
    };

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        edges[i] = {u, v};
        adj[u].push_back(i);
        adj[v].push_back(i);
    }

    vector<bool> vis(n);
    vector<bool> on_tree(m);
    vector<int> d(n);

    auto dfs_make = y_combinator([&](auto self, int u) -> void {
        vis[u] = true;
        for (auto v_idx : adj[u]) {
            auto v = get_edge(u, v_idx);
            if (!vis[v]) {
                on_tree[v_idx] = true;
                d[v] = d[u] + 1;
                self(v);
            }
        }
    });

    for (int i = 0; i < n; i++) {
        dfs_make(i);
    }

    for (int i = 0; i < m; i++) {
        if (on_tree[i]) {
            if (d[edges[i].first] > d[edges[i].second]) {
                swap(edges[i].first, edges[i].second);
            }
        } else {
            if (d[edges[i].first] < d[edges[i].second]) {
                swap(edges[i].first, edges[i].second);
            }
        }
    }

    // need to check if everything can reach one
    fill(vis.begin(), vis.end(), false);

    int t = 0;
    vector<int> in(n);
    vector<int> low(n);

    auto dfs_check = y_combinator([&](auto self, int u) -> void {
        in[u] = low[u] = t++;
        vis[u] = true;

        for (auto v_idx : adj[u]) {
            if (edges[v_idx].first == u) {
                auto v = edges[v_idx].second;

                if (vis[v]) {
                    low[u] = min(low[u], in[v]);
                } else {
                    self(v);
                    low[u] = min(low[u], low[v]);
                }
            }
        }
    });

    dfs_check(0);

    bool valid = true;
    for (int i = 1; i < n; i++) {
        if (in[i] == low[i]) {
            valid = false;
            break;
        }
    }

    if (valid) {
        for (int i = 0; i < m; i++) {
            auto [x, y] = edges[i];
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}

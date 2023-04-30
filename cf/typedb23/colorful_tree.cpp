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

struct edge {
    int to, w, c;
};

struct tree {
    map<int, vector<edge>> adj;
    ll prev_ans;

    void init();
    void toggle(int x);
    ll get_max();
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<vector<edge>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        u--;
        v--;

        adj[u].push_back({v, w, c});
        adj[v].push_back({u, w, c});
    }

    vector<int> sz(n);
    vector<int> vis(n);

    auto dfs_sz = y_combinator([&](auto self, int v, int p) -> int {
        sz[v] = 1;
        for (auto e : adj[v]) {
            if (e.to != p && vis[e.to]) {
                sz[v] += self(e.to, v);
            }
        }
        return sz[v];
    });

    auto dfs_root = y_combinator([&](auto self, int v, int p, int n) -> int {
        for (auto e : adj[v]) {
            if (e.to != p && !vis[e.to] && 2 * sz[e.to] > n) {
                return self(e.to, v, n);
            }
        }
        return v;
    });

    auto find_paths = y_combinator([&](auto self, int v, int p, int cc, tree &t, vector<int> &lst) -> void {
        lst.push_back(v);
        for (auto e : adj[v]) {
            if (e.to != p && !vis[e.to] && e.c == cc) {
                t.adj[v].push_back(e);
                self(e.to, v, cc, t, lst);
            }
        }
    });

    vector<int> c_par(n);
    vector<vector<tree>> c_trees;
    vector<map<int, pair<int, int>>> c_map_back;
    vector<map<int, multiset<int, greater<int>>>> c_best_color;
    vector<multiset<int, greater<int>>> c_best_total;
    multiset<int, greater<int>> best_overall = {0};

    auto build_centroid = y_combinator([&](auto self, int v, int p) -> void {
        dfs_sz(v, -1);
        v = dfs_root(v, -1, sz[v]);

        vis[v] = true;
        c_par[v] = p;

        auto &trees = c_trees[v];
        auto &map_back = c_map_back[v];
        auto &best_color = c_best_color[v];
        auto &best_total = c_best_total[v];

        for (auto e : adj[v]) {
            if (!vis[e.to]) {
                tree t;
                t.adj[v].push_back(e); 
                vector<int> lst;
                find_paths(e.to, v, e.c, t, lst);

                for (auto x : lst) {
                    map_back[x] = {trees.size(), e.c};
                }

                t.init();
                best_color[e.c].insert(t.get_max());
                trees.push_back(t);
            }
        }

        for (auto &[_, m] : best_color) {
            if (m.size() == 1) {
                best_total.insert(*m.begin());
            } else if (m.size() >= 2) {
                best_total.insert(*m.begin() + *next(m.begin()));
            }
        }

        if (!best_total.empty()) {
            best_overall.insert(*best_total.begin());
        }

        for (auto e : adj[v]) {
            if (!vis[e.to]) {
                self(e.to, v);
            }
        }
    });

    build_centroid(0, -1);

    auto toggle = [&](int v, int x) {
        auto &trees = c_trees[v];
        auto &map_back = c_map_back[v];
        auto &best_color = c_best_color[v];
        auto &best_total = c_best_total[v];

        if (!best_total.empty()) {
            best_overall.erase(best_overall.find(*best_total.begin()));
        }

        auto [t_idx, c] = map_back[x];
        auto &color_map = best_color[c];
        auto &t = trees[t_idx];

        if (color_map.size() == 1) {
            best_total.erase(best_total.find(*color_map.begin()));
        } else {
            best_total.erase(best_total.find(*color_map.begin() + *next(color_map.begin())));
        }

        color_map.erase(color_map.find(t.get_max()));
        t.toggle(x);
        color_map.insert(t.get_max());

        if (color_map.size() == 1) {
            best_total.insert(*color_map.begin());
        } else {
            best_total.insert(*color_map.begin() + *next(color_map.begin()));
        }

        if (!best_total.empty()) {
            best_overall.erase(best_overall.find(*best_total.begin()));
        }
    };

    while (q--) {
        int x;
        cin >> x;

        int c = x;
        while (c != -1) {
            toggle(c, x);
            c = c_par[c];
        }

        cout << *best_overall.begin() << '\n';
    }

    return 0;
}

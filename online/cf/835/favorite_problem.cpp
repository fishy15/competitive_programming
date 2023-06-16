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

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    a--;
    b--;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    auto get_dist = [&](int start, bool include_first) {
        set<int> weight;
        if (include_first) {
            weight.insert(0);
        }

        auto dfs = y_combinator([&](auto self, int u, int p, int cur_w) -> void {
            for (auto [v, w] : adj[u]) {
                if (v != p && v != b) {
                    auto new_w = cur_w ^ w;
                    weight.insert(new_w);
                    self(v, u, new_w);
                }
            }
        });

        dfs(start, start, 0);
        return weight;
    };

    auto a_dist = get_dist(a, true);
    auto b_dist = get_dist(b, false);

    for (auto x : a_dist) {
        if (b_dist.count(x)) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
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

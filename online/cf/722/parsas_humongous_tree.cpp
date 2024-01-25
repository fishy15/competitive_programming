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
    template<typename T> explicit y_combinator_result(T &&f) : f(std::forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), std::forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(std::forward<F>(f));
}

void solve() {
    int n;
    cin >> n;

    vector<array<int, 2>> value(n);
    for (auto &[l, r] : value) {
        cin >> l >> r;
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // dp[v][0] = if we pick lower value for v
    // dp[v][1] = if we pick higher value for v
    vector<array<ll, 2>> dp(n);

    auto dfs = y_combinator([&](auto self, int v, int p) -> void {
        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v);
                dp[v][0] += max(dp[e][0] + abs(value[v][0] - value[e][0]),
                                dp[e][1] + abs(value[v][0] - value[e][1]));
                dp[v][1] += max(dp[e][0] + abs(value[v][1] - value[e][0]),
                                dp[e][1] + abs(value[v][1] - value[e][1]));
            }
        }
    });

    dfs(0, 0);
    cout << max(dp[0][0], dp[0][1]) << '\n';
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

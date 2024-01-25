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
#include <bitset>

#pragma GCC target("popcnt")

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

using namespace std;

constexpr int MAXN = 50000;

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

template<int N>
void solve(int n, int m, const vector<vector<int>> &adj) {
    if (N < n) {
        solve<min(2 * N, MAXN)>(n, m, adj);
        return;
    }

    vector<int> vis(n);
    vector<bitset<N>> reachable(n);

    auto solve = y_combinator([&](auto self, int v) -> void {
        if (!vis[v]) {
            vis[v] = true;
            reachable[v].set(v);
            for (auto e : adj[v]) {
                if (!vis[e]) {
                    self(e);
                }
                reachable[v] |= reachable[e];
            }
        }
    });

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            solve(i);
        }
        cout << reachable[i].count() << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    
    vector adj(n, vector<int>{});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
    }

    solve<1>(n, m, adj);

    return 0;
}

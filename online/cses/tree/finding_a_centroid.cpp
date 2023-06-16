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

    int n;
    cin >> n;

    vector adj(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> sz(n);

    auto dfs_size = y_combinator([&](auto self, int v, int p) -> void {
        sz[v] = 1;
        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v);
                sz[v] += sz[e];
            }
        }
    });

    dfs_size(0, 0);

    auto dfs_find = y_combinator([&](auto self, int v, int p) -> int {
        sz[v] = 1;
        for (auto e : adj[v]) {
            if (e != p && 2 * sz[e] > n) {
                return self(e, v);
            }
        }

        return v;
    });

    cout << dfs_find(0, 0) + 1 << '\n';

    return 0;
}

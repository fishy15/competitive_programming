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
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> par(n);
    vector<int> leaf_cnt(n);
    vector<bool> is_leaf(n);
    vector<bool> can_remove(n);
    auto dfs = y_combinator([&](auto self, int v, int p) -> int {
        is_leaf[v] = true;
        can_remove[v] = true;

        for (int e : adj[v]) {
            if (e != p) {
                par[e] = v;
                leaf_cnt[v] += self(e, v);

                if (!can_remove[e]) {
                    is_leaf[v] = false;
                }

                if (!is_leaf[e] && !can_remove[e]) {
                    can_remove[v] = false;
                }
            }
        }

        if (leaf_cnt[v] == 0) {
            leaf_cnt[v] = 1;
        }

        if (is_leaf[v]) {
            can_remove[v] = false;
        }

        return leaf_cnt[v];
    });

    dfs(0, 0);

    int tot_remove = 0;
    int tot_leaf = 0;

    for (int i = 1; i < n; i++) {
        if (can_remove[i]) tot_remove++;
        if (is_leaf[i]) tot_leaf++;
    }

    bool join_leaf = false;
    for (int e : adj[0]) {
        if (is_leaf[e]) {
            join_leaf = true;
        }
    }

    if (join_leaf) {
        cout << max(0, tot_leaf - tot_remove) << '\n';
    } else {
        cout << max(0, tot_leaf - tot_remove + 1) << '\n';
    }

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200000

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

    vector up(n, array<int, 20>{});
    vector<vector<int>> radj(n);
    for (int i = 0; i < n; i++) {
        cin >> up[i][0];
        up[i][0]--;
        radj[up[i][0]].push_back(i);
    }

    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    vector<bool> in_cycle(n);
    for (int i = 0; i < n; i++) {
        in_cycle[up[i][19]] = true;
    }

    vector<int> d(n), exit(n);

    auto dfs = y_combinator([&](auto self, int v, int ee) -> void {
        exit[v] = ee;
        for (auto e : radj[v]) {
            d[e] = d[v] + 1;
            self(e, ee);
        }
    });

    for (int i = 0; i < n; i++) {
        // if this is just before entering a cycle
        if (!in_cycle[i] && in_cycle[up[i][0]]) {
            d[i] = 1;
            dfs(i, up[i][0]); 
        }
    }

    vector<int> cycle_sz(n);
    vector<bool> vis(n);
    auto calc_cycle = y_combinator([&](auto self, int v, int idx) -> void  {
        vis[v] = true;
        if (vis[up[v][0]]) {
            cycle_sz[v] = idx + 1;
        } else {
            self(up[v][0], idx + 1);
            cycle_sz[v] = cycle_sz[up[v][0]];
        }
    });

    for (int i = 0; i < n; i++) {
        if (in_cycle[i] && !vis[i]) {
            calc_cycle(i, 0);
        }
    }

    for (int i = 0; i < n; i++) {
        if (in_cycle[i]) {
            cout << cycle_sz[i] << ' ';
        } else {
            cout << d[i] + cycle_sz[exit[i]] << ' ';
        }
    }
    cout << '\n';

    return 0;
}

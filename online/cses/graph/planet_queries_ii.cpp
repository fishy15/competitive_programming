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

    int n, q;
    cin >> n >> q;

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

    int t = 0;
    vector<int> in(n), out(n), d(n), exit(n);

    auto dfs = y_combinator([&](auto self, int v, int ee) -> void {
        in[v] = t++;
        exit[v] = ee;
        for (auto e : radj[v]) {
            d[e] = d[v] + 1;
            self(e, ee);
        }
        out[v] = t++;
    });

    for (int i = 0; i < n; i++) {
        // if this is just before entering a cycle
        if (!in_cycle[i] && in_cycle[up[i][0]]) {
            d[i] = 1;
            dfs(i, up[i][0]); 
        }
    }

    vector<int> cycle_pos(n), cycle_id(n, -1), cycle_sz(n);
    auto calc_cycle = y_combinator([&](auto self, int v, int id, int idx) -> void  {
        cycle_id[v] = id;
        if (cycle_id[up[v][0]] != -1) {
            cycle_pos[v] = idx;
            cycle_sz[v] = idx + 1;
        } else {
            cycle_pos[v] = idx;
            self(up[v][0], id, idx + 1);
            cycle_sz[v] = cycle_sz[up[v][0]];
        }
    });

    int cur_id = 0;
    for (int i = 0; i < n; i++) {
        if (in_cycle[i] && cycle_id[i] == -1) {
            calc_cycle(i, cur_id, 0);
            cur_id++;
        }
    }

    auto cycle_dist = [&](int a, int b) {
        if (cycle_id[a] != cycle_id[b]) {
            return -1;
        }

        int res = cycle_pos[b] - cycle_pos[a];
        if (res < 0) res += cycle_sz[a];
        return res;
    };

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        if (!in_cycle[a] && !in_cycle[b]) {
            if (in[b] <= in[a] && out[a] <= out[b]) {
                cout << d[a] - d[b] << '\n';
            } else {
                cout << "-1\n";
            }
        } else if (!in_cycle[a] && in_cycle[b]) {
            int init_steps = d[a];
            a = exit[a];
            int nxt_steps = cycle_dist(a, b);

            if (nxt_steps == -1) {
                cout << "-1\n";
            } else {
                cout << init_steps + nxt_steps << '\n';
            }
        } else if (in_cycle[a] && in_cycle[b]) {
            cout << cycle_dist(a, b) << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}

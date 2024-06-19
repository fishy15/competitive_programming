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

ll max_set(ll x) {
    return 1LL << (63 - __builtin_clzll(x));
}

void add_to_basis(vector<ll> &basis, ll a) {
    for (auto x : basis) {
        if (a != 0 && max_set(x) == max_set(a)) {
            a ^= x;
        }
    }

    if (a != 0) {
        basis.push_back(a);
        sort(basis.begin(), basis.end(), greater<>());
    }
}

bool can_add_to_basis(const vector<ll> &basis, ll a) {
    for (auto x : basis) {
        if (a != 0 && max_set(x) == max_set(a)) {
            a ^= x;
        }
    }

    return a != 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
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

    int q;
    cin >> q;

    vector<array<int, 4>> qry(q);
    for (int i = 0; i < q; i++) {
        auto &[x, y, k, idx] = qry[i];
        cin >> x >> y >> k;
        x--;
        y--;
        idx = i;
    }

    vector<int> sz(n);
    vector<bool> vis(n);
    vector<int> branch(n);
    vector<int> ans(q);
    vector<vector<ll>> basis(n);

    auto dfs_sz = y_combinator([&](auto &&self, int v, int p) -> int {
        sz[v] = 1;
        for (auto e : adj[v]) {
            if (e != p && !vis[e]) {
                sz[v] += self(e, v);
            }
        }
        return sz[v];
    });

    auto dfs_root = y_combinator([&](auto &&self, int v, int p, int tot) -> int {
        for (auto e : adj[v]) {
            if (e != p && !vis[e] && 2 * sz[e] > tot) {
                return self(e, v, tot);
            }
        }
        return v;
    });

    auto dfs_anc = y_combinator([&](auto &&self, int v, int p, int anc) -> void {
        basis[v] = basis[p];
        add_to_basis(basis[v], a[v]);
        branch[v] = anc;

        for (auto e : adj[v]) {
            if (e != p && !vis[e]) {
                self(e, v, anc);
            }
        }
    });

    auto centroid = y_combinator([&](auto &&self, int v, const vector<array<int, 4>> &cur_qry) -> void {
        dfs_sz(v, -1);
        v = dfs_root(v, -1, sz[v]);
        vis[v] = true;

        branch[v] = -1;
        int idx = 0;
        basis[v] = {a[v]};

        for (auto e : adj[v]) {
            if (!vis[e]) {
                dfs_anc(e, v, idx);
                idx++;
            }
        }

        vector<vector<array<int, 4>>> nxt_qry(idx);

        for (auto [x, y, k, i] : cur_qry) {
            if (x == v && y == v) {
                ans[i] = (k == a[v] || k == 0);
            } else if (branch[x] == branch[y]) {
                nxt_qry[branch[x]].push_back({x, y, k, i});
            } else {
                vector<ll> cur_basis = basis[x];
                for (auto elem : basis[y]) {
                    add_to_basis(cur_basis, elem);
                }

                if (!can_add_to_basis(cur_basis, k)) {
                    ans[i] = true;
                }
            }
        }

        idx = 0;
        for (auto e : adj[v]) {
            if (!vis[e]) {
                self(e, nxt_qry[idx]);
                idx++;
            }
        }
    });

    centroid(0, qry);

    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}

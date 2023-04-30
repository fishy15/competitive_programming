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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

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

const mi HALF = mi(1) / 2;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<mi> p_butterfly(n, 0);
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        a--;

        p_butterfly[a] = 1;
    }

    vector<pair<int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; 
        v--;

        edges.push_back({u, v});
    }

    for (auto [u, v] : edges) {
        mi new_u, new_v;

        // u -> v
        {
            mi both = p_butterfly[u] * p_butterfly[v];
            mi moved = p_butterfly[u] * (mi(1) - p_butterfly[v]);
            new_u += HALF * both;
            new_v += HALF * (p_butterfly[v] + moved);
        }

        // v -> u
        {
            mi both = p_butterfly[u] * p_butterfly[v];
            mi moved = p_butterfly[v] * (mi(1) - p_butterfly[u]);
            new_u += HALF * (p_butterfly[u] + moved);
            new_v += HALF * both;
        }

        p_butterfly[u] = new_u;
        p_butterfly[v] = new_v;
    }

    // tree work

    vector adj(n, vector<int>());
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> d(n);
    vector<mi> p_anc(n);
    vector<mi> p_lca(n);
    auto dfs = y_combinator([&](auto self, int v, int p) -> void {
        p_anc[v] += p_butterfly[v] / k;
        for (auto e : adj[v]) {
            if (e != p) {
                d[e] = d[v] + 1;
                self(e, v);

                p_anc[v] += p_anc[e];
            }
        }

        p_lca[v] = p_anc[v] * p_anc[v];
        for (auto e : adj[v]) {
            if (e != p) {
                p_lca[v] -= p_anc[e] * p_anc[e];
            }
        }
    });

    dfs(0, 0);

    mi ans;
    for (int i = 0; i < n; i++) {
        ans += p_butterfly[i] * d[i] * 2 / k;
        ans -= mi(2) * p_lca[i] * d[i];

        cout << p_anc[i].v << ' ' << p_lca[i].v << '\n';
    }

    cout << ans.v << '\n';

    ans *= k - 1;

    cout << ans.v << '\n';

    return 0;
}

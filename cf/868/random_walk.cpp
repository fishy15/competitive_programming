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
    template<typename T> explicit y_combinator_result(T &&f) : f(std::forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), std::forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(std::forward<F>(f));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, s, t;
    cin >> n >> s >> t;
    s--;
    t--;

    vector<vector<int>> adj(n);
    vector<int> outdeg(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<mi> ans(n);
    vector<mi> up_ratio(n);

    auto dfs1 = y_combinator([&](auto self, int v, int p) -> void {
        mi coeff = 1;
        for (auto e : adj[v]) {
            if (e != p && e != t) {
                self(e, v);
                // e_v = sum_e e_e / deg(e)
                // e_e = up_ratio[e] * e_v
                coeff -= up_ratio[e] / (int) adj[e].size();
            }
        }
        if (v != s) {
            // coeff * e_v = e_p / deg(p)
            // e_v = e_p / (coeff * deg(p))
            up_ratio[v] = (coeff * (int) adj[p].size()).inv();
        } else {
            up_ratio[v] = coeff.inv();
        }
    });

    auto dfs2 = y_combinator([&](auto self, int v, int p) -> void {
        for (auto e : adj[v]) {
            if (e != p && e != t) {
                ans[e] = ans[v] * up_ratio[e];
                self(e, v);
            }
        }
    });

    dfs1(s, s);

    ans[s] = up_ratio[s];
    ans[t] = 1;

    dfs2(s, s);

    for (auto x : ans) cout << x.v << ' ';
    cout << '\n';

    return 0;
}

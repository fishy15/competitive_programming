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

mi count_graph(int n, const vector<pair<int, int>> &edges, const set<int> &done) {
    vector<set<int>> adj(n);

    for (int i = 0; i < (int) edges.size(); i++) {
        auto [u, v] = edges[i];
        adj[u].insert(i);
        adj[v].insert(i);
    }

    queue<int> one;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1 && !done.count(i)) {
            one.push(i);
        }
    }

    while (!one.empty()) {
        auto v = one.front();
        one.pop();

        if (adj[v].empty()) {
            return 0;
        }

        int e = *adj[v].begin();
        auto [u1, v1] = edges[e];
        adj[u1].erase(e);
        adj[v1].erase(e);

        if (adj[u1].size() == 1 && !done.count(u1)) {
            one.push(u1);
        }

        if (adj[v1].size() == 1 && !done.count(v1)) {
            one.push(v1);
        }
    }

    vector vis(n, false);
    mi ans = 1;

    auto dfs = y_combinator([&](auto self, int v) -> void {
        if (!vis[v]) {
            vis[v] = true;
            for (auto e : adj[v]) {
                auto [u1, v1] = edges[e];
                self(u1);
                self(v1);
            }
        }
    });

    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 2) {
            if (!vis[i]) {
                ans *= 2;
                dfs(i);
            }
        } else if (!adj[i].empty()) {
            return 0;
        }
    }

    return ans;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    set<int> not_covered;
    for (int i = 1; i <= n; i++) {
        not_covered.insert(i);
    }

    mi any = 1;
    vector<pair<int, int>> edges;
    set<int> self_refl;

    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            any *= n;
            self_refl.insert(a[i] - 1);
        } else {
            edges.push_back({a[i] - 1, b[i] - 1});
        }

        not_covered.erase(a[i]);
        not_covered.erase(b[i]);
    }

    if (not_covered.empty()) {
        mi ans = any * count_graph(n, edges, self_refl);
        cout << ans.v << '\n';
    } else {
        cout << 0 << '\n';
    }
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

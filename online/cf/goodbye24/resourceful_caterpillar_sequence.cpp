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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

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

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // winning if adj to a leaf
    vector<bool> winning(n);
    vector<bool> leaf(n);
    int nonleaf = 0;
    rep(i, 0, n) {
        leaf[i] = sz(adj[i]) == 1;
        if (!leaf[i]) {
            nonleaf++;
        }
        for (auto x : adj[i]) {
            if (sz(adj[x]) == 1) {
                winning[i] = true;
                break;
            }
        }
    }

    vector<int> par(n, -1);
    vector<int> ssz(n, 0);
    auto dfs = y_combinator([&](auto &&self, int v, int p) -> void {
        ssz[v] = (!leaf[v] && !winning[v]) ? 1 : 0;
        par[v] = p;
        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v);
                ssz[v] += ssz[e];
            }
        }
    });

    dfs(0, -1);

    ll ans = 0;
    rep(q, 0, n) {
        if (leaf[q]) {
            ans += nonleaf;
        } else {
            for (auto e : adj[q]) {
                if (winning[e]) {
                    // how many start locations that are not leaves
                    ll works = 0;
                    if (e == par[q]) {
                        works = ssz[0] - ssz[q];
                    } else {
                        works = ssz[e];
                    }
                    ans += works;
                }
            }
        }
    }

    cout << ans << '\n';
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

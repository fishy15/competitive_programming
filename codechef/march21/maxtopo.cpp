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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}
    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }
    mi &operator/=(const mi &m2) {
        *this *= m2.modpow(MOD - 2);
        return *this;
    }
    mi modpow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
};

struct frac {
    int n, d;
    frac(int n, int d) : n(n), d(d) {}
    bool operator<(const frac &f2) const {
        return (ll) n * f2.d < (ll) f2.n * d;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    vector<int> sz(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    function<int(int, int)> dfs_sz = [&](int v, int p) {
        sz[v] = 1;
        for (int e : adj[v]) {
            if (e != p) {
                sz[v] += dfs_sz(e, v);
            }
        }
        return sz[v];
    };

    function<int(int, int)> dfs_root = [&](int v, int p) {
        for (int e : adj[v]) {
            if (e != p && sz[e] > n - sz[e]) {
                return dfs_root(e, v);
            }
        }
        return v;
    };

    dfs_sz(0, 0);
    int v = dfs_root(0, 0);
    dfs_sz(v, v);
    mi res = 1;
    for (int i = 1; i < n; i++) {
        res *= i;
    }
    for (int i = 0; i < n; i++) {
        if (i != v) {
            res /= sz[i];
        }
    }

    vector<pair<frac, int>> opt = {{{1, 1}, v}};
    for (int e : adj[v]) {
        opt.push_back({{sz[e], n - sz[e]}, e});
    }

    sort(opt.rbegin(), opt.rend());
    res *= opt[k - 1].first.n;
    res /= opt[k - 1].first.d;
    cout << opt[k - 1].second + 1 << ' ' << res.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

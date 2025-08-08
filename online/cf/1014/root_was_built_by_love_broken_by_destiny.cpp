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

constexpr int MAXN = 200'000;
mi f[MAXN+1];

void precomp() {
    f[0] = 1;
    rep(i, 1, MAXN+1) {
        f[i] = f[i-1] * i;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector adj(n, vector<int>{});
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (m != n-1) {
        cout << "0\n";
        return;
    }

    // computes cost of current cc
    mi ans = 1;
    int not_endpoint = 0;
    rep(v, 0, n) {
        if (sz(adj[v]) > 1) {
            not_endpoint++;
        }
        int one_adj = 0;
        int cont = 0;
        for (auto e : adj[v]) {
            if (sz(adj[e]) == 1) {
                one_adj++;
            } else {
                cont++;
            }
        }

        // must be at endpoints
        if (cont > 2) {
            ans = 0;
        }
        ans *= f[one_adj];
    }

    if (not_endpoint > 1) {
        ans *= 2;
    }

    ans *= 2;

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

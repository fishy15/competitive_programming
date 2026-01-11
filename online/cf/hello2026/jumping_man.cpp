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

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> ord;
    vector<int> par(n);
    auto dfs = [&](auto &&self, int v, int p) -> void {
        ord.push_back(v);
        par[v] = p;
        for (auto e : adj[v]) {
            if (e != p) {
                self(self, e, v);
            }
        }
    };
    dfs(dfs, 0, -1);

    // dp[v1][v2][0] = paths that are ongoing
    // dp[v1][v2][1] = paths that have terminated
    // dp[v1][v2][2] = paths that just got an element, so both need to be skipped
    vector dp(n, vector(n, array{mi(0), mi(0), mi(0)}));

    for (int i1 = n-1; i1 >= 0; i1--) {
        for (int i2 = n-1; i2 >= 0; i2--) {
            int v1 = ord[i1];
            int v2 = ord[i2];

            for (auto e1 : adj[v1]) {
                if (e1 != par[v1]) {
                    rep(i, 0, 2) {
                        dp[v1][v2][i] += dp[e1][v2][i];
                    }
                }
            }

            for (auto e2 : adj[v2]) {
                if (e2 != par[v2]) {
                    rep(i, 0, 2) {
                        dp[v1][v2][i] += dp[v1][e2][i];
                    }
                }
            }

            for (auto e1 : adj[v1]) {
                for (auto e2 : adj[v2]) {
                    if (e1 != par[v1] && e2 != par[v2]) {
                        rep(i, 0, 2) {
                            dp[v1][v2][i] -= dp[e1][e2][i];
                        }
                        dp[v1][v2][0] += dp[e1][e2][2];
                    }
                }
            }

            if (s[v1] == s[v2]) {
                dp[v1][v2][2] += dp[v1][v2][0] + 1;
                dp[v1][v2][1] += dp[v1][v2][2];
            }
        }
    }

    rep(i, 0, n) {
        cout << dp[i][i][1].v << ' ';
    }
    cout << '\n';
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

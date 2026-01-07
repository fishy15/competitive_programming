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

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int MOD;

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
    string s;
    cin >> s;

    cin >> MOD;

    int n = sz(s);

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        adj[i].push_back(i+1);
        adj[i+1].push_back(i);
    }

    vector dp(n, vector(n, mi(0)));

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

    mi ans = 0;
    rep(i1, 0, n) {
        rep(i2, 0, n) {
            int v1 = ord[i1];
            int v2 = ord[i2];
            int p1 = par[v1];
            int p2 = par[v2];

            // pull continuations from parents
            if (p1 != -1) {
                dp[v1][v2] += dp[p1][v2];
            }
            if (p2 != -1) {
                dp[v1][v2] += dp[v1][p2];
            }
            if (p1 != -1 && p2 != -1) {
                dp[v1][v2] -= dp[p1][p2];
            }
            
            if (s[v1] == s[v2]) {
                ans += dp[v1][v2] + 1;
                // push down the skips
                for (auto e1 : adj[v1]) {
                    for (auto e2 : adj[v2]) {
                        if (e1 != p1 && e2 != p2) {
                            dp[e1][e2] += dp[v1][v2] + 1;
                        }
                    }
                }
            }
        }
    }

    ans += 1;
    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;

    while (t--) {
        solve();
    }

    return 0;
}

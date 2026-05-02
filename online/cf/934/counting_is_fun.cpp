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
    int n, k;
    cin >> n >> k >> MOD;

    vector dp(k+1, vector(k+1, mi(0)));
    auto nxt = dp;

    // must start with 0
    rep(i, 0, k+1) {
        dp[0][i] = 1;
    }

    // repeat for n-1 more places
    rep(_, 0, n-1) {
        rep(i, 0, k+1) {
            rep(j, 0, k+1) {
                auto lim = max(0, j - i);
                if (lim <= k) {
                    nxt[j][lim] += dp[i][j];
                }
            }
        }

        rep(i, 0, k+1) {
            rep(j, 1, k+1) {
                nxt[i][j] += nxt[i][j-1];
            }
        }

        dp.swap(nxt);
        for (auto &v : nxt) {
            for (auto &x : v) {
                x = 0;
            }
        }
    }

    mi ans = 0;
    rep(i, 0, k+1) {
        // j <= i
        rep(j, 0, i+1) {
            ans += dp[i][j];
        }
    }

    cout << ans.v << '\n';
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

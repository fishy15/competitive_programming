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

mi no_rep_count(const string &s) {
    int len_until_repeat = 0;
    mi ans = 0;
    rep(i, 0, sz(s)) {
        if (i > 0 && s[i] == s[i - 1]) {
            len_until_repeat = 1;
        } else {
            len_until_repeat++;
        }
        ans += len_until_repeat;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t;
    cin >> s >> t;

    int n = sz(s);
    int m = sz(t);

    // dp[reached i][reached j][last dir]
    vector dp(n+1, vector(m+1, array<mi, 2>{}));
    mi ans = 0;
    rep(i, 0, n+1) {
        rep(j, 0, m+1) {
            ans += dp[i][j][0];
            ans += dp[i][j][1];
            if (i < n) {
                dp[i+1][j][0] += 1;
                if (i > 0 && s[i] != s[i-1]) {
                    dp[i+1][j][0] += dp[i][j][0];
                }
                if (j > 0 && s[i] != t[j-1]) {
                    dp[i+1][j][0] += dp[i][j][1];
                }
            }
            if (j < m) {
                dp[i][j+1][1] += 1;
                if (i > 0 && t[j] != s[i-1]) {
                    dp[i][j+1][1] += dp[i][j][0];
                }
                if (j > 0 && t[j] != t[j-1]) {
                    dp[i][j+1][1] += dp[i][j][1];
                }
            }
        }
    }

    // sequences that only use 1 of the two strings are counted extra
    ans -= mi(m + 1) * no_rep_count(s);
    ans -= mi(n + 1) * no_rep_count(t);

    cout << ans.v << '\n';

    return 0;
}

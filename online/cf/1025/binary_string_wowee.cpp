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
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    // combo[x][y][0/1] = if we have x flips, how many ways to fill y of them with current, starting with 0 or 1
    vector combo(k+1, vector(k+1, array<mi, 2>{}));
    combo[0][0][0] = 1;
    combo[0][0][1] = 1;
    for (int len = 1; len <= k; len++) {
        for (int cur = 0; cur <= len; cur++) {
            if (cur > 0) {
                combo[len][cur][0] += combo[len - 1][cur - 1][1];
            }
            combo[len][cur][0] += combo[len - 1][cur][1];
            combo[len][cur][1] += combo[len - 1][cur][0];
        }
    }

    // dp[x][y] = using s[:x], if there are k gaps left, how many ways to fill
    vector dp(n+1, vector(k+1, mi(0)));
    dp[0][k] = 1;
    rep(i, 1, n+1) {
        auto c = s[i-1] == '0' ? 0 : 1;
        rep(gap, 0, k+1) {
            rep(used, 0, gap+1) {
                dp[i][gap - used] += dp[i-1][gap] * combo[gap][used][c];
            }
        }
    }

    cout << dp[n][0].v << '\n';
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

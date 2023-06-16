/*
 * Let dp[x][k] = C(0 + k, x) + C(3 + k, x) + ... + C(n + k, x), where 0 <= k < 3. We get that dp[x][0] + 
 * dp[x][1] + dp[x][2] = C(0, x) + ... + C(3 * n + 2, x) = C(3 * n + 3, x + 1) by the Hockey Stick Identity,
 * We also have dp[x][k] = dp[x][k - 1] + dp[x - 1][k] due to Pascal's Identity. Using this, we start with
 * the base case dp[0][0] = dp[0][1] = dp[0][2] = n + 1 and then use the previous facts to solve for the 
 * three dp values for a given value x. The answer for some query x is then dp[x][0].
 */
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
#define MAXN 1000010

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

mi f[3 * MAXN];
mi inv_f[3 * MAXN];
mi dp[3 * MAXN][3];

void precomp() {
    f[0] = 1;
    for (int i = 1; i < 3 * MAXN; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[3 * MAXN - 1] = f[3 * MAXN - 1].inv();

    for (int i = 3 * MAXN - 2; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

mi c(int n, int k) {
    return f[n] * inv_f[k] * inv_f[n - k];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int n; cin >> n;

    dp[0][0] = n + 1;
    dp[0][1] = n + 1;
    dp[0][2] = n + 1;

    mi three_inv = mi(3).inv();
    for (int i = 1; i <= 3 * n; i++) {
        dp[i][0] = (c(3 * n + 3, i + 1) - dp[i - 1][0] * 2 - dp[i - 1][1]) * three_inv;
        dp[i][1] = dp[i][0] + dp[i - 1][0];
        dp[i][2] = dp[i][1] + dp[i - 1][1];
    }

    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        cout << dp[x][0].v << '\n';
    }

    return 0;
}

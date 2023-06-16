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
#define MOD 10567201

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

mi pow_mul[1010][1010];
mi f[1010];
mi inv_f[1010];

void precalc() {
    f[0] = 1;
    for (int i = 1; i <= 1000; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[1000] = f[1000].inv();
    for (int i = 999; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }

    mi pow2 = 1;
    for (int n = 0; n <= 1000; n++) {
        int max_m = min(1 << min(n, 20), 1000);
        mi cur = pow2;
        pow_mul[n][0] = 1;

        for (int m = 1; m <= max_m; m++) {
            pow_mul[n][m] = pow_mul[n][m - 1] * cur;
            cur -= 1;
        }

        pow2 *= 2;
    }
}

mi c(int n, int m) {
    return pow_mul[n][m] * inv_f[m];
}

void solve(int n, int m, int v) {
    vector<mi> dp(m + 1);
    if (m % 2 == 0) {
        if (v == 0) {
            dp[0] = 1;
        } else {
            dp[0] = 0;
        }
    } else {
        dp[1] = 1;
    }

    for (int i = m % 2 + 2; i <= m; i += 2) {
        dp[i] = f[i - 1] * c(n, i - 1) - mi(i - 1) * (pow_mul[n][1] - i + 2) * dp[i - 2];
    }

    cout << (dp[m] * inv_f[m]).v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    while (true) {
        int n, m, v; cin >> n >> m >> v;
        if (n == 0) break;
        solve(n, m, v);
    }

    return 0;
}

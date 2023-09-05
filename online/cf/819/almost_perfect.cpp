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

// change if necessary
#define MAXN 300000

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

mi single[MAXN + 1];
mi inv_pow_two[MAXN + 1];
mi f[MAXN + 1];
mi inv_f[MAXN + 1];

mi g(mi *c, int idx) {
    if (idx < 0) return 0;
    return c[idx];
}

void precalc() {
    single[0] = 1;
    inv_pow_two[0] = 1;
    f[0] = 1;

    auto inv2 = mi(2).inv();
    for (int i = 1; i <= MAXN; i++) {
        single[i] = g(single, i - 2) * (i - 1) + g(single, i - 1);
        inv_pow_two[i] = inv_pow_two[i - 1] * inv2;
        f[i] = f[i - 1] * i;
    }

    inv_f[MAXN] = f[MAXN].inv();
    for (int i = MAXN - 1; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

mi c(int n, int k) {
    return g(f, n) * g(inv_f, k) * g(inv_f, n - k);
}

void solve() {
    int n;
    cin >> n;

    mi ans;
    for (int k = 0; 4 * k <= n; k++) {
        int s = n - 4 * k;
        auto total = c(2 * k + s, s);
        auto pair_combo = f[2 * k] * inv_f[k];
        auto single_combo = single[s];
        ans += total * pair_combo * single_combo;
    }

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

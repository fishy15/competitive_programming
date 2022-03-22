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
#define MAXN 1000000
#define MAXF 2510

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

mi f[MAXF];
mi inv_f[MAXF];

void precalc() {
    f[0] = 1;
    for (int i = 1; i < MAXF; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[MAXF - 1] = f[MAXF - 1].inv();

    for (int i = MAXF - 2; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

mi c(int n, int k) {
    if (k > n) return 0;
    return f[n] * inv_f[k] * inv_f[n - k];
}

int n, m, b, w;
mi cnt[60][60]; // cnt[x][y] = # of ways to pick B spots with x rows, y columns

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    cin >> n >> m >> b >> w;

    mi ans;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // PIE
            for (int a = 1; a <= i; a++) {
                for (int b = 1; b <= j; b++) {
                    if (a == i && b == j) break;
                    cnt[i][j] -= cnt[a][b] * c(i, a) * c(j, b);
                }
            }

            cnt[i][j] += c(i * j, b);
            ans += cnt[i][j] * c(n, i) * c(m, j) * c((n - i) * (m - j), w);
        }
    }

    cout << ans.v << '\n';

    return 0;
}

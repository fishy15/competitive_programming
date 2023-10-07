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

// change if necessary
#define MAXN 4000

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

mi f[MAXN + 1];
mi inv_f[MAXN + 1];

bool aset[MAXN][MAXN];
mi ans[MAXN][MAXN];

mi c(int n, int k) {
    if (k < 0 || k > n) return 0;
    return f[n] * inv_f[k] * inv_f[n - k];
}

mi solve(int t, int m) {
    if (m < 0) return 0;
    if (aset[t][m]) return ans[t][m];

    aset[t][m] = true;
    if (t == 0) {
        if (m >= 0) {
            return ans[t][m] = 1;
        } else {
            return ans[t][m] = 0;
        }
    } else {
        mi tot = solve(t - 1, m + 1) + solve(t - 1, m - 1);
        return ans[t][m] = tot;
    }
}

void precalc() {
    f[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[MAXN] = f[MAXN].inv();
    for (int i = MAXN - 1; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

void solve() {
    int t, m;
    cin >> t >> m;

    mi ans = solve(t, m);
    ans -= solve(t, m - 1);

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

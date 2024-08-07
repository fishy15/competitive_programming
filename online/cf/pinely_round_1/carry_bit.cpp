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

mi f[MAXN + 1];
mi inv_f[MAXN + 1];

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

mi c(int n, int k) {
    if (k > n) return 0;
    return f[n] * inv_f[k] * inv_f[n - k];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int n, k;
    cin >> n >> k;

    if (k == 0) {
        cout << mi(3).pow(n).v << '\n';
        return 0;
    }

    int left = n - k;
    int up = k;

    mi ans;
    for (int turns = 1; turns <= n; turns++) {
        int left_groups = turns / 2 + 1;
        int up_groups = (turns + 1) / 2;
        ans += c(left, left_groups - 1) * c(up - 1, up_groups - 1) * mi(3).pow(n - turns);
    }

    cout << ans.v << '\n';

    return 0;
}

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

int n, k;
map<ll, mi> cnt[60][60]; // cnt[n][# of loops]

mi f[60];
mi invf[60];
mi inv_num[60];

void precalc() {
    f[0] = 1;
    invf[0] = 1;
    for (int i = 1; i <= 50; i++) {
        f[i] = f[i - 1] * i;
        invf[i] = f[i].inv();
        inv_num[i] = mi(i).inv();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    precalc();

    cin >> n >> k;

    cnt[0][0][1] = 1;

    // i = old part, j = how much added, k = prev how many loops
    for (int i = 0; i < n; i++) {
        mi pick = 1;
        for (int j = 1; i + j <= n; j++) {
            pick *= n - i - j + 1;

            for (int k = 0; k < n; k++) {
                for (auto [len, count] : cnt[i][k]) {
                    ll l = lcm(len, j);
                    cnt[i + j][k + 1][l] += count * (pick * inv_num[j]);
                }
            }
        }
    }

    mi ans = 0;
    for (int i = 1; i <= n; i++) {
        for (auto [len, count] : cnt[n][i]) {
            count *= invf[i];
            ans += mi(len).pow(k) * count;
        }
    }

    cout << ans.v << '\n';

    return 0;
}

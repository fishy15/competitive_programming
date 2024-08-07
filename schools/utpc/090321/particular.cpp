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

ll x, y, n;
mi ans;
mi f[MAXN];
mi f_inv[MAXN];

mi c(int n, int k) {
    return f[n] * f_inv[k] * f_inv[n - k];
}

bool ok(const string &s) {
    for (char c : s) {
        int a = c - '0';
        if (a != x && a != y) {
            return false;
        }
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> x >> y >> n;

    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * i;
    }

    f_inv[n] = f[n].inv();

    for (int i = n - 1; i >= 0; i--) {
        f_inv[i] = f_inv[i + 1] * (i + 1);
    }

    for (int i = 0; i <= n; i++) {
        ll sum = i * x + (n - i) * y;
        string ssum = to_string(sum);

        if (ok(ssum)) {
            ans += c(n, i);
        }
    }

    cout << ans.v << '\n';

    return 0;
}

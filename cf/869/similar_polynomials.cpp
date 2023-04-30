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
#define MAXN 2500010

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

mi f[MAXN];
mi inv_f[MAXN];

void precalc() {
    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[MAXN - 1] = f[MAXN - 1].inv();
    for (int i = MAXN - 2; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

mi c(int n, int k) {
    return f[n] * inv_f[k] * inv_f[n - k];
}

mi comp(const vector<mi> &v) {
    int n = v.size();
    mi res;
    for (int i = 0; i < n; i++) {
        mi val = v[n - i - 1];
        int sgn = (i % 2 == 0 ? 1 : -1);
        mi coeff = c(n - 1, i) * sgn;
        res += val * coeff;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int d;
    cin >> d;

    vector<mi> a(d + 1), b(d + 1);

    for (int i = 0; i <= d; i++) {
        int x;
        cin >> x;
        a[i] = x;
    }

    for (int i = 0; i <= d; i++) {
        int x;
        cin >> x;
        b[i] = x;
    }

    vector<mi> c(d);
    for (int i = 0; i < d; i++) {
        c[i] = b[i] - a[i];
    }

    mi inv_df = f[d].inv();
    mi a_d = comp(a) / inv_df;
    mi ans = comp(c) / inv_df / a_d;
    cout << ans.v << '\n';

    return 0;
}

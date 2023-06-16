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

constexpr int sz = 1000;

int n, k;
mi dp[sz][sz]; // dp[num_transposition][num_cycle]
mi ans[sz];
mi fact[sz];
mi inv_f[sz];
mi nfact[sz];
mi inv_nf[sz];

mi choose(int m, int k) {
    m = n - m;
    mi num = nfact[m + k] * inv_nf[m];
    return num * inv_f[k];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    dp[0][0] = 1;
    ans[0] = 1;

    fact[0] = 1;
    inv_f[0] = 1;
    nfact[0] = 1;
    inv_nf[0] = 1;
    for (int i = 1; i < sz; i++) {
        fact[i] = fact[i - 1] * i;
        inv_f[i] = fact[i].inv();
        nfact[i] = nfact[i - 1] * (n - i + 1);
        inv_nf[i] = nfact[i].inv();
    }

    ll cnt = 0;
    for (int t = 1; t <= min(n - 1, k); t++) {
        for (int c = 1; c <= 2 * k; c++) {
            for (int nt = 1; nt <= t; nt++) {
                int prev_t = t - nt;
                int prev_c = c - 1;
                int tot_in_c = prev_t + prev_c;
                dp[t][c] += choose(n - tot_in_c, nt + 1) * dp[t - nt][c - 1] * fact[nt];
                cnt++;
            }

            dp[t][c] /= c; // counts all of these multiple times
            ans[t] += dp[t][c];
        }
    }

    for (int i = 1; i <= k; i++) {
        if (i > 1) ans[i] += ans[i - 2];
        cout << ans[i].v << ' ';
    }
    cout << '\n';

    return 0;
}

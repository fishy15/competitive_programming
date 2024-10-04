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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

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

constexpr int MAX_K = 2000;

mi stirling[MAX_K+1][MAX_K+1];

void precomp() {
    for (int n = 1; n <= MAX_K; n++) {
        for (int k = 1; k <= n; k++) {
            if (k == 1 || k == n) {
                stirling[n][k] = 1;
            } else {
                stirling[n][k] = stirling[n-1][k-1] + stirling[n-1][k] * k;
            }
        }
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    // n * (n - 1) * ...
    mi cur_fact = n;
    mi ans;

    mi m_inv = mi(m).inv();
    mi half = (m + 1) / 2;
    mi cur_half = half;
    mi cur_all = mi(m).pow(n - 1);

    for (int grp = 1; grp <= k; grp++) {
        mi num_tuples = stirling[k][grp] * cur_fact;
        ans += num_tuples * cur_half * cur_all;
        cur_fact *= n - grp;
        cur_half *= half;
        cur_all *= m_inv;
    }

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

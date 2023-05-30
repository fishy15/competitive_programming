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
#include <random>
#include <chrono>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 300010

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mi f[MAXN];
mi inv_f[MAXN];

ll rand_hash() {
    return uniform_int_distribution(numeric_limits<ll>::min(), numeric_limits<ll>::max())(rng);
}

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

mi catalan(int n) {
    return c(2 * n, n) / (n + 1);
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<ll> psum_hash(n);
    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;
        l--;

        auto hash = rand_hash();
        psum_hash[l] ^= hash;

        if (r < n) {
            psum_hash[r] ^= hash;
        }
    }

    for (int i = 1; i < n; i++) {
        psum_hash[i] ^= psum_hash[i - 1];
    }

    map<ll, int> cnts;
    for (auto h : psum_hash) {
        cnts[h]++;
    }

    mi ans = 1;
    for (auto [_, cnt] : cnts) {
        if (cnt % 2 == 0) {
            ans *= catalan(cnt / 2);
        } else {
            ans = 0;
            break;
        }
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

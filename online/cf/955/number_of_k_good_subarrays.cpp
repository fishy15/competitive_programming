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
#define MAXB 100

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

mi div2 = mi(2).inv();

mi f[MAXB];
mi inv_f[MAXB];
map<ll, int> pow2;

void precomp() {
    f[0] = 1;
    inv_f[0] = 1;
    for (int i = 1; i < MAXB; i++) {
        f[i] = f[i - 1] * i;
        inv_f[i] = f[i].inv();
    }

    ll cur_p = 1;
    for (int i = 0; i <= 60; i++) {
        pow2[cur_p] = i;
        cur_p *= 2;
    }
}

mi c(int n, int k) {
    return f[n] * inv_f[k] * inv_f[n - k];
}

vector<mi> comp_distrib(ll n) {
    if (n == 0) return {};
    if ((n & (n - 1)) == 0) {
        // we are a power of 2
        int bits = pow2[n];
        vector<mi> res(bits + 1);
        for (int i = 0; i <= bits; i++) {
            res[i] = c(bits, i);
        }
        return res;
    } else {
        auto biggest_pow = prev(pow2.upper_bound(n))->first;
        auto distrib1 = comp_distrib(biggest_pow);
        auto distrib2 = comp_distrib(n - biggest_pow);

        if (distrib1.size() < distrib2.size() + 1) {
            distrib1.resize(distrib2.size() + 1);
        }

        for (int i = 0; i < (int) distrib2.size(); i++) {
            distrib1[i + 1] += distrib2[i];
        }

        return distrib1;
    }
}

mi solve(ll n, int k) {
    static map<pair<ll, int>, mi> cache;
    if (n == 0) return 0;
    if (cache.count({n, k})) {
        return cache[{n, k}];
    }

    mi ret;
    auto int_size = 1LL << (k + 1);
    if (k < 0) {
        ret = 0;
    } else if (k == 0) {
        ret = 1;
    } else if (n <= int_size) {
        // every single combo works, except including the last one
        if (n < int_size) {
            ret = mi(n) * mi(n + 1) * div2;
        } else {
            ret = mi(n - 1) * mi(n) * div2;
        }
    } else {
        ll complete_ints = n / int_size;
        auto distrib = comp_distrib(complete_ints);
        for (int i = 0; i < (int) distrib.size(); i++) {
            ret += distrib[i] * solve(int_size, k - i);
        }

        // final interval
        auto rem_size = n - complete_ints * int_size;
        if (rem_size > 0) {
            int bits_set = __builtin_popcountll(complete_ints);
            ret += solve(rem_size, k - bits_set);
        }
    }

    return cache[{n, k}] = ret;
}

void solve() {
    ll n;
    int k;
    cin >> n >> k;
    cout << solve(n, k).v << '\n';
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

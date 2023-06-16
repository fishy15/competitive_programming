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

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

template<int MOD>
struct modint {
    int v;
    modint() : modint(0) {}
    modint(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    modint(ll _v) : modint((int)(_v % MOD)) {}
    modint operator+(const modint &m2) const { return modint(v + m2.v); }
    modint operator-(const modint &m2) const { return modint(v - m2.v); }
    modint operator*(const modint &m2) const { return modint((ll) v * m2.v); }
    modint operator/(const modint &m2) const { return modint((ll) v * m2.inv().v); }
    modint &operator+=(const modint &m2) { return *this = *this + m2; }
    modint &operator-=(const modint &m2) { return *this = *this - m2; }
    modint &operator*=(const modint &m2) { return *this = *this * m2; }
    modint &operator/=(const modint &m2) { return *this = *this / m2; }
    modint pow(ll e) const {
        modint res = 1;
        modint n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    modint inv() const {
        return pow(MOD - 2);
    }
};

constexpr int MOD = 1e9 + 7;
using mi = modint<MOD>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<ll, ll>> primes(n);
    for (int i = 0; i < n; i++) {
        cin >> primes[i].first >> primes[i].second;
    }

    mi num_divisors = 1;
    mi sum_divisors = 1;
    mi prod_divisors = 1;

    vector<modint<MOD - 1>> prefix_divisors(n + 1);
    vector<modint<MOD - 1>> suffix_divisors(n + 1);

    prefix_divisors[0] = 1;
    for (int i = 0; i < n; i++) {
        auto [p, e] = primes[i];
        prefix_divisors[i + 1] = prefix_divisors[i] * (e + 1);
    }

    suffix_divisors[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        auto [p, e] = primes[i];
        suffix_divisors[i] = suffix_divisors[i + 1] * (e + 1);
    }

    for (auto [p, e] : primes) {
        num_divisors *= e + 1;
        sum_divisors *= (mi(p).pow(e + 1) - 1) / (p - 1);
    }

    for (int i = 0; i < n; i++) {
        auto [p, e] = primes[i];

        auto mul_powers = mi(p).pow(e * (e + 1) / 2);
        auto num_appears = prefix_divisors[i] * suffix_divisors[i + 1];
        prod_divisors *= mul_powers.pow(num_appears.v);
    }

    cout << num_divisors.v << ' ' << sum_divisors.v << ' ' << prod_divisors.v << '\n';

    return 0;
}

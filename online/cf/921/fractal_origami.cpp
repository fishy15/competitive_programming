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
#define MOD 999999893

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

// a + b sqrt(2)
struct mi2 {
    mi a, b;

    mi2() : a{}, b{} {}
    mi2(mi a, mi b) : a{a}, b{b} {}

    mi2 operator+(const mi2 &other) const {
        return {a + other.a, b + other.b};
    }

    mi2 operator*(const mi2 &other) const {
        return {a * other.a + b * other.b * 2, a * other.b + b * other.a};
    }

    mi2 &operator+=(const mi2 &m2) { return *this = *this + m2; }
    mi2 &operator*=(const mi2 &m2) { return *this = *this * m2; }

    mi2 operator/(const mi2 &m2) const {
        mi2 mul = {m2.a * -1, m2.b};
        auto div = (m2 * mul).a;
        auto num = *this * mul;
        return {num.a / div, num.b / div};
    }
};

struct M {
    const static int n = 3;
    mi2 m[n][n]; 
    M operator*(const M &m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    res[i][j] += m[i][a] * m2[a][j];
                }
            }
        }
        return res;
    }
    mi2 *operator[](const int x) { return m[x]; }
    const mi2 *operator[](const int x) const { return m[x]; }
    static M pow(M m, ll e) {
        M res = I();
        while (e > 0) {
            if (e & 1) res = res * m;
            m = m * m;
            e >>= 1;
        }
        return res;
    }
    static M I() {
        M m;
        for (int i = 0; i < n; i++) m[i][i] = {1, 0};
        return m;
    }
};

void solve() {
    int n;
    cin >> n;

    // {P, V, M}
    M transition;

    // P <- P sqrt(2)
    transition[0][0] = {0, 1};

    // V <- P + V + M
    transition[1][0] = {1, 0};
    transition[1][1] = {1, 0};
    transition[1][2] = {1, 0};

    // M <- V + M
    transition[2][1] = {1, 0};
    transition[2][2] = {1, 0};

    M start; // [2 sqrt{2}, 0, 0]
    start[0][0] = {0, 2}; 

    transition = M::pow(transition, n);
    auto res = transition * start;
    auto ans = res[2][0] / res[1][0];

    cout << ans.b.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

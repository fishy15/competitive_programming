/*
 * We can use a matrix to represent how many paths there are and another matrix represents the current 
 * transitions possible. For each query, we can apply the transition matrix some number of times using
 * matrix exponentiation and then print the appropriate value/modify the transition matrix appropriately.
 */
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
#include <cassert>

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

struct M {
    const static int n = 20;
    mi m[n][n]; 
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
    mi *operator[](const int x) { return m[x]; }
    const mi *operator[](const int x) const { return m[x]; }
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
        for (int i = 0; i < n; i++) m[i][i] = 1;
        return m;
    }
};

int n, m, q;
int pt = 1;
M cur, to_mul;

int g(int x, int y) {
    return m * x + y;
}

bool ok(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

void modify(int x, int y, int chg) {
    to_mul[g(x, y)][g(x, y)] += chg;
    if (ok(x - 1, y)) to_mul[g(x - 1, y)][g(x, y)] += chg;
    if (ok(x + 1, y)) to_mul[g(x + 1, y)][g(x, y)] += chg;
    if (ok(x, y - 1)) to_mul[g(x, y - 1)][g(x, y)] += chg;
    if (ok(x, y + 1)) to_mul[g(x, y + 1)][g(x, y)] += chg;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            modify(i, j, 1);
        }
    }

    cur[g(0, 0)][g(0, 0)] = 1; 

    while (q--) {
        int tp, x, y, t; cin >> tp >> x >> y >> t;
        x--; y--;

        cur = cur * M::pow(to_mul, t - pt);
        pt = t;

        if (tp == 1) {
            cout << cur[g(0, 0)][g(x, y)].v << '\n';
        } else if (tp == 2) {
            cur[g(0, 0)][g(x, y)] = 0;
            modify(x, y, -1);
        } else {
            modify(x, y, 1);
        }
    }

    return 0;
}

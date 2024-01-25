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

int p[MAXN + 1];

void precomp() {
    for (int i = 2; i <= MAXN; i++) {
        if (p[i] == 0) {
            p[i] = i;
            for (ll j = (ll) i * i; j <= MAXN; j += i) {
                p[j] = i;
            }
        }
    }
}

mi get_num_divs(int x) {
    map<int, int> fact;
    while (x > 1) {
        fact[p[x]]++;
        x /= p[x];
    }

    mi ans = 1;
    for (auto [_, c] : fact) {
        ans *= c + 1;
    }

    return ans - 1; // proper
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int n;
    cin >> n;

    // solution for 2i
    vector<mi> sol(n + 1);

    sol[0] = 1;
    mi psum;
    for (int i = 1; i <= n; i++) {
        psum += sol[i - 1];

        // matching 1 w/ something past half
        sol[i] += psum;

        if (i > 1) {
            // matching w/ a divisor
            // each proper divisor contributes 2 except for 1
            auto num_divs = get_num_divs(i);
            sol[i] += num_divs;
        }
    }

    cout << sol[n].v << '\n';

    return 0;
}

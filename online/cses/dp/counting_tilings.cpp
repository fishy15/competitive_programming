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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<mi> dp(1 << n);
    dp[0] = 1;

    for (int i = 0; i < m; i++) {
        // distribute down
        for (int k = 0; k < n - 1; k++) {
            for (int a = 0; a < (1 << k); a++) {
                for (int b = 0; b < (1 << (n - k - 2)); b++) {
                    int cur_m = (b << (k + 2)) + a;

                    int nxt_m = cur_m;
                    nxt_m ^= (1 << k);
                    nxt_m ^= (1 << (k + 1));

                    dp[nxt_m] += dp[cur_m];
                }
            }
        }

        // flip
        int ones = (1 << n) - 1;
        for (int j = 0; j < (1 << (n - 1)); j++) {
            swap(dp[j], dp[ones ^ j]);
        }
    }

    cout << dp[0].v << '\n';

    return 0;
}

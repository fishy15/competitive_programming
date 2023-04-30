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

int n, m;
mi dp[1001][1 << 10];
mi cnt[1 << 10];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    cnt[0] = 1;
    for (int i = 1; i < (1 << m); i++) {
        cnt[i] = cnt[i / 2];
        if (i & 1) cnt[i] *= 2;
    }

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << m); j++) {
            dp[i][j] = dp[i - 1][j] * cnt[j];
        }

        for (int j = 0; j < m; j++) {
            for (int ma = 0; ma < (1 << m); ma++) {
                if (ma & (1 << j)) {
                    dp[i][ma] += dp[i][ma ^ (1 << j)];
                }
            }
        }

        // now need to remove 0 and all masks
        for (int j = 0; j < (1 << m); j++) {
            dp[i][j] -= dp[i - 1][j];
            dp[i][(1 << m) - 1] -= dp[i - 1][j];
        }
    }

    cout << dp[n][(1 << m) - 1].v << '\n';

    return 0;
}

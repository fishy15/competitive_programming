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
#define MAXN 510

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

int n, d;
int a[MAXN];
mi dp[MAXN][1 << 11];

int get_p(int diff) {
    return 1 << (diff + d);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] != -1) a[i]--;
    }

    // for the first index, init
    if (a[0] == -1) {
        for (int i = 0; i <= d; i++) {
            dp[0][get_p(i)] = 1;
        }
    } else {
        dp[0][get_p(a[0])] = 1;
    }

    // push forward dp
    for (int i = 0; i < n - 1; i++) {
        for (int m = 0; m < (1 << (2 * d + 1)); m++) {
            if (i > d && (m & 1) == 0) continue; 
            if (a[i + 1] == -1) {
                for (int diff = -d; diff <= d; diff++) {
                    if ((i + 1) + diff < 0 || (i + 1) + diff >= n) continue;
                    int p = get_p(diff);
                    int nm = m >> 1;
                    if (nm & p) continue;
                    nm ^= p;

                    dp[i + 1][nm] += dp[i][m];
                }
            } else {
                int diff = a[i + 1] - (i + 1);
                int p = get_p(diff);
                int nm = m >> 1;
                if (nm & p) continue;
                nm ^= p;

                dp[i + 1][nm] += dp[i][m];
            }
        }
    }

    mi ans = 0;
    for (int m = 0; m < (1 << (2 * d + 1)); m++) {
        ans += dp[n - 1][m];
    }

    cout << ans.v << '\n';

    return 0;
}

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

template<typename T>
struct mid_vector {
    int n;
    vector<T> vec;

    mid_vector(int n) : n(n), vec(2 * n + 1) {}

    T &operator[](int idx) {
        return vec[idx + n];
    }

    const T &operator[](int idx) const {
        return vec[idx + n];
    }
};

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

    int n;
    cin >> n;

    string t;
    cin >> t;

    vector dp(2 * n + 1, mid_vector<pair<mi, mi>>(n));
    dp[0][0] = {0, 1};

    for (int i = 0; i < 2 * n + 1; i++) {
        auto c = t[i];
        for (int j = -n; j <= n; j++) {
            // transition +
            if (c == '+' || c == '?') {
                if (j + 1 <= n) {
                    dp[i + 1][j + 1].first += dp[i][j].first;
                    dp[i + 1][j + 1].second += dp[i][j].second;
                    if (j >= 0) {
                        dp[i + 1][j + 1].first += dp[i][j].second * (mi(2) * j + 1);
                    }
                }
            }

            // transition -
            if (c == '-' || c == '?') {
                if (j - 1 >= -n) {
                    dp[i + 1][j - 1].first += dp[i][j].first;
                    dp[i + 1][j - 1].second += dp[i][j].second;
                    if (j <= 0) {
                        dp[i + 1][j - 1].first += dp[i][j].second * (mi(2) * -j + 1);
                    }
                }
            }
        }
        cout << '\n';
    }

    cout << dp[2*n][0].first.v << '\n';

    return 0;
}

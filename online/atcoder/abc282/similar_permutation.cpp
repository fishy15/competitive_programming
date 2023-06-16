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

int MOD;

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

    int n, k;
    cin >> n >> k >> MOD;

    // dp[prefix added][similarity][end first][end second]
    vector dp(n, vector(n, vector(n, vector<mi>(n))));

    dp[0][0][0][0] = 1;
    for (int i = 1; i < n; i++) {
        for (int s = 0; s < i; s++) {
            // make psum for the previous level
            vector psum(i + 1, vector<mi>(i + 1));
            for (int a = 0; a < i; a++) {
                for (int b = 0; b < i; b++) {
                    psum[a + 1][b + 1] = dp[i - 1][s][a][b];
                }
            }

            for (int a = 0; a <= i; a++) {
                for (int b = 0; b <= i; b++) {
                    if (a > 0) psum[a][b] += psum[a - 1][b];
                    if (b > 0) psum[a][b] += psum[a][b - 1];
                    if (a > 0 && b > 0) psum[a][b] -= psum[a - 1][b - 1];
                }
            }

            auto get = [psum = move(psum), i](int x1, int x2, int y1, int y2) { 
                x1 = max(x1, 0);
                y1 = max(y1, 0);
                x2 = min(x2, i);
                y2 = min(y2, i);

                return psum[x2][y2] - psum[x1][y2] - psum[x2][y1] + psum[x1][y1];
            };

            for (int e1 = 0; e1 <= i; e1++) {
                for (int e2 = 0; e2 <= i; e2++) {
                    // similar
                    dp[i][s + 1][e1][e2] += get(0, e1, 0, e2);
                    dp[i][s + 1][e1][e2] += get(e1, i, e2, i);

                    // not similar
                    dp[i][s][e1][e2] += get(0, e1, e2, i);
                    dp[i][s][e1][e2] += get(e1, i, 0, e2);
                }
            }
        }
    }

    mi ans = 0;
    for (int e1 = 0; e1 < n; e1++) {
        for (int e2 = 0; e2 < n; e2++) {
            ans += dp[n - 1][k][e1][e2];
        }
    }

    cout << ans.v << '\n';

    return 0;
}

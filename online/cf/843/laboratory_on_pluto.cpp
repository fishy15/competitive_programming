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
#define MAXN 631

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

constexpr int DIST = 26;

mi ways[MAXN+1];
mi arrange[MAXN+1]; // arrange i spaces to the 4 corners

void precomp() {
    ways[0] = 1;
    for (int len = 1; len <= MAXN; len++) {
        for (int j = 0; j+len <= MAXN; j++) {
            ways[j+len] += ways[j];
        }
    }

    array c = {
        array{1, 1, 1, 1, 1},
        array{0, 1, 2, 3, 4},
        array{0, 0, 1, 3, 6},
        array{0, 0, 0, 1, 4},
        array{0, 0, 0, 0, 1},
    };

    auto sq = [](mi x) { return x * x; };
    auto tr = [](mi x) { return x * x * x; };
    auto qd = [](mi x) { return x * x * x * x; };

    // dp[corners used][len so far]
    vector dp(5, vector<mi>(MAXN+1));
    dp[0][0] = 1;
    arrange[0] = 1;
    for (int len = 1; len <= MAXN; len++) {
        for (int i = 3; i >= 0; i--) {
            for (int j = MAXN; j >= 0; j--) {
                if (i < 4 && j + len <= MAXN) {
                    dp[i+1][j+len] += dp[i][j] * ways[len] * c[1][4-i];
                }

                if (i < 3 && j + 2*len <= MAXN) {
                    dp[i+2][j+2*len] += dp[i][j] * sq(ways[len]) * c[2][4-i];
                }

                if (i < 2 && j + 3*len <= MAXN) {
                    dp[i+3][j+3*len] += dp[i][j] * tr(ways[len]) * c[3][4-i];
                }

                if (i < 1 && j + 4*len <= MAXN) {
                    dp[i+4][j+4*len] += dp[i][j] * qd(ways[len]) * c[4][4-i];
                }
            }
        }

        for (int i = 0; i <= 4; i++) {
            arrange[len] += dp[i][len];
        }
    }
}

void solve(int n, int typ) {
    vector<pair<int, int>> boundings;
    int cur_p = INF;

    int rt = (int) sqrt(n);

    for (int h = max(rt - DIST, 1); h <= min(rt + DIST, n); h++) {
        int w = (n + h - 1) / h;
        int p = 2 * (h + w);
        if (p < cur_p) {
            boundings = {{h, w}};
            cur_p = p;
        } else if (p == cur_p) {
            boundings.push_back({h, w});
        }
    }

    if (typ == 1) {
        auto [h, w] = boundings[0];

        vector<string> grid(h);
        int done = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (done < n) {
                    done++;
                    grid[i] += '#';
                } else {
                    grid[i] += '.';
                }
            }
        }

        cout << h << ' ' << w << '\n';
        for (const auto &row : grid) {
            cout << row << '\n';
        }
    } else {
        mi ans = 0;
        for (auto [h, w] : boundings) {
            if (h == 1 || w == 1) {
                ans += 1;
            } else {
                int spaces = h*w - n;
                ans += arrange[spaces];
            }
        }

        cout << cur_p << ' ' << ans.v << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t, u;
    cin >> t >> u;

    if (u == 2){
        cin >> MOD;
        precomp();
    }

    while (t--) {
        int n;
        cin >> n;
        solve(n, u);
    }

    return 0;
}

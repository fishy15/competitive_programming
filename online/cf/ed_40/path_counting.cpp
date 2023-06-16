/*
 * We can solve using dynamic programming. Let dp[n][k][2] be the number of paths of length k within the first
 * n + 1 levels of the the tree with either 1 or 2 endpoints at a vertex of depth n (depending on the final 
 * state). We can calculate how many new paths we can start at the bottom of the current tree and also
 * extend the dp[n] values to dp[n + 1] values (by increasing the path length by 1 or 2). Summing this dp
 * given a constant k value gives us the value of f_k.
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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 5010

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}
    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mi operator+(const mi &m2) const {
        mi m = *this;
        return m += m2;
    }
    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }
    mi operator*(const mi &m2) const {
        mi m = *this;
        return m *= m2;
    }
};

int n;
mi c[MAXN];
mi dp[2][2 * MAXN][2]; // dp[depth][length][# open (1 or 2)]
mi ans[2 * MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        c[i] = x;
    }

    mi root_cnt = 1;
    for (int i = 1; i < n; i++) {
        dp[0][1][0] += root_cnt * c[i - 1];
        dp[0][2][1] += root_cnt * c[i - 1] * mi(c[i - 1].v - 1) * mi(500000004); // div by 2
        root_cnt *= c[i - 1];
        for (int k = 1; k <= 2 * n - 2; k++) {
            dp[1][k + 1][0] += dp[0][k][0] * c[i];
            dp[1][k + 1][0] += dp[0][k][1] * 2 * c[i];
            dp[1][k + 2][1] += dp[0][k][1] * c[i] * c[i];
        }
        for (int k = 1; k <= 2 * n - 2; k++) {
            ans[k] += dp[0][k][0];
            ans[k] += dp[0][k][1];
            dp[0][k][0] = dp[1][k][0];
            dp[0][k][1] = dp[1][k][1];
            dp[1][k][0] = 0;
            dp[1][k][1] = 0;
        }
    }

    for (int k = 1; k <= 2 * n - 2; k++) {
        ans[k] += dp[0][k][0];
        ans[k] += dp[0][k][1];
    }

    for (int k = 1; k <= 2 * n - 2; k++) {
        cout << ans[k].v << ' ';
    }
    cout << '\n';

    return 0;
}

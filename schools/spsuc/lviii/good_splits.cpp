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

int mod;

void add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n >> mod;

    vector dp(2*n+1, vector(n+1, vector(n+1, 0)));
    dp[0][0][0] = 1;

    for (int i = 1; i <= 2*n; i++) {
        auto &cur = dp[i];
        auto &prev = dp[i - 1];
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                if (j > 0) add(cur[j][k], prev[j-1][k]);
                if (j < n) add(cur[j][k], prev[j+1][k]);
                if (k > 0) add(cur[j][k], prev[j][k-1]);
                if (k < n) add(cur[j][k], prev[j][k+1]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dp[2*i][0][0] << '\n';
    }

    return 0;
}

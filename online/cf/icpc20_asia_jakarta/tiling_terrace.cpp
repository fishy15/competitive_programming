/*
 * Let dp[i][j] be the max number of type-2 tiles that can be placed within the first i locations and 
 * using j type-3 tiles. Since there are at max 50 rocks, there are at max 50 tiles of type-3, so calculating
 * this dp runs within the time limit. If it is optimal and we don't go over the limit of type-1 tiles, we
 * can replace some of the type-2 tiles with type-1 tiles. The max of all thse values for all the different 
 * number of type-3 tiles gives the answer.
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
#define MAXN 100010

using namespace std;

int n, k, g[3];
string s;
int dp[MAXN][55];
int rock;
int ans;

int ckmax(int &a, int b, int c) {
    if (b == -1) return a;
    return a = max(a, b + c);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k >> g[0] >> g[1] >> g[2];
    cin >> s;

    for (int i = 0; i < n; i++) {
        if (s[i] == '.') {
            rock++;
        }
    }

    memset(dp, -1, sizeof dp);
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 50; j++) {
            ckmax(dp[i][j], dp[i - 1][j], 0);
            if (i >= 2 && s[i - 2] == '.' && s[i - 1] == '.') {
                ckmax(dp[i][j], dp[i - 2][j], 1);
            }
            if (j >= 1 && i >= 3 && s[i - 3] == '.' && s[i - 2] == '#' && s[i - 1] == '.') {
                ckmax(dp[i][j], dp[i - 3][j - 1], 0);
            }
        }
    }

    for (int i = 0; i <= 50; i++) {
        if (dp[n][i] == -1) continue;
        int left = rock - 2 * i - 2 * dp[n][i];
        if (left < k && 2 * g[0] > g[1]) {
            int spot = min((k - left) / 2, dp[n][i]);
            dp[n][i] -= spot;
            left += spot * 2;
        }
        if (left < k && g[0] > g[1] && dp[n][i]) {
            dp[n][i]--;
            left++;
        }
        left = min(left, k);
        ckmax(ans, g[0] * left + g[1] * dp[n][i] + g[2] * i, 0);
    }

    cout << ans << '\n';

    return 0;
}

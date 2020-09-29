// explanation of solution at below link
// https://codeforces.com/blog/entry/47764#comment-704139

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
#define MAXN 2010 

using namespace std;

int n, cs, cf;
ll dp[MAXN][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> cs >> cf;

    dp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == cs || i == cf) {
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
                if (dp[i][j] >= MOD) dp[i][j] -= MOD;
            } else {
                dp[i][j] += (dp[i - 1][j + 1]) * j % MOD;
                dp[i][j] += (dp[i - 1][j - 1]) * (j - (i > cs) - (i > cf)) % MOD;
                if (dp[i][j] >= MOD) dp[i][j] -= MOD;
            }
        }
    }

    cout << dp[n][1] << '\n';

    return 0;
}

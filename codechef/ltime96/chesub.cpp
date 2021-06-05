/*
 * We can do dynamic programming, where dp[i][j] represents the maximum score we can get with the first i
 * numbers and j subarrays. We can then transition dp[i - 1][j] -> dp[i][j] to represent adding the ith
 * number to the end of the subarray and max(dp[0][j - 1], dp[1][j - 1], ..., dp[i - 1][j - 1]) -> dp[i][j]
 * to represent starting a new subarray. To get the max quickly, we can maintain the prefix max.
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

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    // dp[i][j][0] = best that ends at i, uses j arrays
    // dp[i][j][1] = best that ends <= i, uses j arrays
    vector<vector<array<ll, 2>>> dp(n, vector<array<ll, 2>>(k + 1));
    dp[0][1][0] = nums[0];
    dp[0][1][1] = nums[0];
    for (int j = 2; j <= k; j++) {
        dp[0][j] = {-INFLL, -INFLL};
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j][0] = max(dp[i - 1][j - 1][1], dp[i - 1][j][0]) + j * nums[i];
            dp[i][j][1] = max(dp[i - 1][j][1], dp[i][j][0]);
        }
    }

    cout << dp[n - 1][k][1] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 55

using namespace std;

int n;
int nums[MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];

int qry(int l, int r, int lo, int hi) {
    if (dp[l][r][lo][hi] != -1) {
        return dp[l][r][lo][hi];
    }

    if (l > r || lo > hi) {
        return dp[l][r][lo][hi] = 0;
    }

    if (l == r) {
        if (lo <= nums[l] && nums[l] <= hi) {
            return dp[l][r][lo][hi] = 1;
        }
        return dp[l][r][lo][hi] = 0;
    }

    dp[l][r][lo][hi] = max(qry(l + 1, r, lo, hi), qry(l, r - 1, lo, hi));
    dp[l][r][lo][hi] = max(dp[l][r][lo][hi], qry(l + 1, r - 1, lo, hi));
    dp[l][r][lo][hi] = max(dp[l][r][lo][hi], qry(l, r, lo + 1, hi));
    dp[l][r][lo][hi] = max(dp[l][r][lo][hi], qry(l, r, lo, hi - 1));
    dp[l][r][lo][hi] = max(dp[l][r][lo][hi], qry(l, r, lo + 1, hi - 1));

    int a = min(nums[l], nums[r]);
    int b = max(nums[l], nums[r]);

    if (nums[l] == lo) {
        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], qry(l + 1, r, lo, hi) + 1);
    }

    if (nums[r] == hi) {
        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], qry(l, r - 1, lo, hi) + 1);
    }

    if (a == lo && b == hi) {
        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], qry(l + 1, r - 1, lo, hi) + 2);
    }

    if (a == lo) {
        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], qry(l + 1, r - 1, lo, hi) + 1);
    }

    if (b == hi) {
        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], qry(l + 1, r - 1, lo, hi) + 1);
    }

    if (dp[l][r][lo][hi] > r - l + 1) {
        dp[l][r][lo][hi] = -INF;
    }

    return dp[l][r][lo][hi];
}

int main() {
    /* ifstream fin("subrev.in"); */
    /* ofstream fout("subrev.out"); */

    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            for (int c = 0; c <= 50; c++) {
                for (int d = 0; d <= 50; d++) {
                    dp[a][b][c][d] = -1;
                }
            }
        }
    }

    cout << qry(0, n - 1, 1, 50) << '\n';

    return 0;
}

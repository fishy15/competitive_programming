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
#define MAXN 300

using namespace std;

// 3 2 1 
int n;
double dp[MAXN + 1][MAXN + 1][MAXN + 1];

double solve(int i, int j, int k) {
    if (k == 0 && j == 0 && i == 0) {
        return 0.0;
    }

    if (dp[i][j][k]) {
        return dp[i][j][k];
    }

    if (i > 0) {
        dp[i][j][k] += 1.0 * i / n * (solve(i - 1, j + 1, k));
    }

    if (j > 0) {
        dp[i][j][k] += 1.0 * j / n * (solve(i, j - 1, k + 1));
    }

    if (k > 0) {
        dp[i][j][k] += 1.0 * k / n * (solve(i, j, k - 1));
    }

    dp[i][j][k]++;
    dp[i][j][k] /= i + j + k;
    dp[i][j][k] *= n;

    return dp[i][j][k];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    int cnt[4] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    cout << fixed << setprecision(15) << solve(cnt[3], cnt[2], cnt[1]) << '\n';

    return 0;
}
/*
 * For the interval [l, r], the expected value of beating the region is equal to sum over l <= i <= j <= r 
 * of t_j / t_i. Using a combination of various sums, we can find the cost of any interval in O(1). We can
 * then use the divide and conquer DP optimization to solve the problem in O(nk log n). To prove why this
 * works, suppose the optimal interval that ends at index i begins at m. This means that the case where
 * the regions are grouped like ..., m - 1], [m, i] has a lower cost than when it is grouped like 
 * ..., m - 2], [m - 1, i]. In comparison to the optimal scenario, the first interval has a smaller 
 * expected value and the second interval has a larger expected value, so this means that the decrease
 * in the first interval is less than the increase in the second interval. When we add index i + 1 to the 
 * second interval, this only increases the second interval, so moving the splitting point backwards only
 * enlargens the difference and means that it is not optimal. Therefore, the optimal splitting point 
 * monotonically increases, so we can use divide and conquer DP.
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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, k;
int nums[MAXN];
ld dp[2][MAXN];

// prefix sums stuff
ld triangle_sum[MAXN];
ll num_sum[MAXN];
ld denom_sum[MAXN];

ld cost(int l, int r) {
    return triangle_sum[r] - triangle_sum[l] - num_sum[l] * (denom_sum[r] - denom_sum[l]);
}

void solve(int cur, int l, int r, int x, int y) {
    if (l > r) return;

    int m = (l + r) / 2;
    int pre = cur ^ 1;

    pair<ld, int> best = {INFLL, x};
    for (int i = x; i <= min(m, y); i++) {
        ld p = i > 0 ? dp[pre][i - 1] : 0;
        best = min(best, {p + cost(i, m + 1), i});
    }

    dp[cur][m] = best.first;
    solve(cur, l, m - 1, x, best.second);
    solve(cur, m + 1, r, best.second, y);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];

        num_sum[i + 1] = num_sum[i];
        num_sum[i + 1] += nums[i];

        denom_sum[i + 1] = denom_sum[i];
        denom_sum[i + 1] += 1.0 / nums[i];

        triangle_sum[i + 1] = triangle_sum[i];
        triangle_sum[i + 1] += 1.0 * num_sum[i + 1] / nums[i];
    }

    for (int i = 0; i < n; i++) {
        dp[0][i] = cost(0, i + 1);
    }

    for (int i = 1; i < k; i++) {
        for (int j = 0; j < n; j++) {
            dp[i & 1][j] = INFLL;
        }

        solve(i & 1, 0, n - 1, 0, n - 1);
    }

    cout << fixed << setprecision(12) << dp[(k & 1) ^ 1][n - 1] << '\n';

    return 0;
}

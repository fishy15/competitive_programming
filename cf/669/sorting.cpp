/*
 * We can solve for the maximum number of indices that don't have to move using dynamic programming. Let
 * dp[i] represent the number of indices that can stay in the suffix [i..n]. If i is the leftmost value of 
 * the color, then one possibility is that everything of that color stays, which would mean that everything
 * in the middle would have to move. Therefore, the amount that could stay in this case is the count of that
 * color + dp[r + 1], where r is the rightmost index of that color. If i is not the leftmost value of that
 * color, then we consider the case where we let every index of that color stay in the current suffix, and
 * the colors outside of the current suffix will be moved. In order for this to be possible, all of the 
 * colors besides the current one must be moved in the suffix in order to make room to move the indices
 * of the color outside of the suffix. There is finally the case that we mark the current index to be moved.
 * The answer will be n - dp[0].
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
#define MAXN 500010

using namespace std;

int n;
int nums[MAXN];
int l[MAXN];
int r[MAXN];
int dp[MAXN];
int cnt[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    memset(l, -1, sizeof l);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (l[nums[i]] == -1) {
            l[nums[i]] = i;
        }
        r[nums[i]] = i;
    }

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = dp[i + 1];
        cnt[nums[i]]++;
        if (l[nums[i]] == i) {
            int stay = cnt[nums[i]];
            stay += dp[r[nums[i]] + 1];
            dp[i] = max(dp[i], stay);
        } else {
            dp[i] = max(dp[i], cnt[nums[i]]);
        }
    }

    cout << n - dp[0] << '\n';

    return 0;
}

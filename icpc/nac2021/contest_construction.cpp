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
#define MAXN 1000000

using namespace std;

int n, k;
int nums[51];

ll dp[51][51][51][20]; // dp[i][first][second][cur_len]

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    sort(nums, nums + n);

    dp[0][0][0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int f = 0; f <= n; f++) {
            for (int s = f; s <= n; s++) {
                if (f == 0 || s == 0 || nums[f] + nums[s] <= nums[i]) {
                    for (int l = 1; l <= k; l++) {
                        dp[i][
                        if (k > 0) {
                            dp[i][s][i][k] += dp[i - 1][f][s][k - 1];
                        }
                    }
                }
            }
        }
    }

    return 0;
}

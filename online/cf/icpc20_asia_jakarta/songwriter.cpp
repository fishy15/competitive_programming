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
#define MAXN 100000

using namespace std;

int n, l, r, k;
int nums[MAXN];
int dp[MAXN][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> l >> r >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    dp[n - 1][0] = l;
    dp[n - 1][1] = r;

    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            dp[i][0] = max(dp[i + 1][0] - k, l);
            dp[i][1] = dp[i + 1][1] - 1;
        } else if (nums[i] == nums[i + 1]) {
            dp[i][0] = dp[i + 1][0];
            dp[i][1] = dp[i + 1][1];
        } else {
            dp[i][0] = dp[i + 1][0] + 1;
            dp[i][1] = min(dp[i + 1][1] + k, r);
        }

        if (dp[i][0] > r || dp[i][1] < l) {
            cout << "-1\n";
            return 0;
        }
    }

    int cur = dp[0][0];
    cout << dp[0][0] << ' ';
    
    for (int i = 1; i < n; i++) {
        if (nums[i - 1] < nums[i]) {
            cur = max(cur + 1, dp[i][0]);
        } else if (nums[i - 1] > nums[i]) {
            cur = max(cur - k, dp[i][0]);
        }

        cout << cur << ' ';
    }

    cout << '\n';

    return 0;
}

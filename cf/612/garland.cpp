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
#define MAXN 100

using namespace std;

int n;
vector<int> nums;
int dp[MAXN][MAXN][MAXN][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                dp[i][j][k][0] = INF;
                dp[i][j][k][1] = INF;
            }
        }
    }

    dp[0][1][0][0] = 0;
    dp[0][0][1][1] = 0;

    if (nums[0] > 0) {
        if (nums[0] % 2) {
            dp[0][1][0][0] = INF;
        } else { 
            dp[0][0][1][1] = INF;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if ((nums[i] == 0 || nums[i] % 2 == 0) && j > 0) {
                    dp[i][j][k][0] = min(dp[i - 1][j - 1][k][0], dp[i - 1][j - 1][k][1] + 1);
                    /* if (dp[i][j][k][0] < INF) { */
                    /*     cout << i << ' ' << j << ' ' << k << ' ' << 0 << ' ' << dp[i][j][k][0] << '\n'; */
                    /* } */
                }

                if ((nums[i] == 0 || nums[i] % 2 == 1) && k > 0) {
                    dp[i][j][k][1] = min(dp[i - 1][j][k - 1][0] + 1, dp[i - 1][j][k - 1][1]);
                    /* if (dp[i][j][k][1] < INF) { */
                    /*     cout << i << ' ' << j << ' ' << k << ' ' << 1 << ' ' << dp[i][j][k][1] << '\n'; */
                    /* } */
                }
            }
        } 
    }

    int m = n / 2;
    cout << min(dp[n - 1][m][n - m][0], dp[n - 1][m][n - m][1]) << '\n';

    return 0;
}

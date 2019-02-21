#include <iostream>
#include <vector>

#define MOD 1000000007

using namespace std;

// 0 if you have not included d before
// 1 if you have

int n, k, d;
int dp[101][2];

int main() {
    cin >> n >> k >> d;
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                if (j >= d) {
                    dp[i][1] += dp[i - j][0];
                    dp[i][1] %= MOD;
                    dp[i][1] += dp[i - j][1];
                    dp[i][1] %= MOD;
                } else {
                    dp[i][0] += dp[i - j][0];
                    dp[i][0] %= MOD;
                    dp[i][1] += dp[i - j][1];
                    dp[i][1] %= MOD;
                }
            }
        }
    }

    cout << (dp[n][1] % MOD) << '\n';

    return 0;
}
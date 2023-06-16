// :pray: :fishy:

#include <iostream>
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
#define MAXN 500 

using namespace std;

int n;
string s;
int dp[MAXN][MAXN];


int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (int sz = 2; sz <= n; sz++) {
        for (int l = 0; l < n - sz + 1; l++) {
            int r = l + sz - 1;
            dp[l][r] = dp[l + 1][r] + 1;

            for (int i = l + 1; i <= r; i++) {
                if (s[l] == s[i]) {
                    dp[l][r] = min(dp[l][r], dp[l + 1][i - 1] + dp[i][r]);
                }
            }
        }
    }

    cout << dp[0][n - 1] << '\n';

    return 0;
}

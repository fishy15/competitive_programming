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

int n;
ll k;
ll nums[30];
ll dp[1 << 20][30]; // how much remaining, mask, used

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    memset(dp, -1, sizeof dp);
    dp[0][0] = 0;

    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                int m = i ^ (1 << j);
                for (int a = 0; a <= n; a++) {
                    if (dp[m][a] < nums[j] && dp[m][a] != -1) {
                        ckmax(dp[i][a + 1], k - nums[j]);
                    } else {
                        ckmax(dp[i][a], dp[m][a] - nums[j]);
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dp[(1 << n) - 1][i] != -1) {
            cout << i << '\n';
            break;
        }
    }

    return 0;
}

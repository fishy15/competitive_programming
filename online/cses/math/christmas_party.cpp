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
#define MAXN 1000010

using namespace std;

int n;
ll dp[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    dp[1] = 0;
    dp[2] = 1;

    for (int i = 3; i <= n; i++) {
        dp[i] = (i - 1) * (dp[i - 2] + dp[i - 1]) % MOD;
    }

    cout << dp[n] << '\n';

    return 0;
}

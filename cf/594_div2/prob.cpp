// :pray: :steph:
// :pray: :bakekaga:

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
#define MAXN 100000

using namespace std;

ll dp[MAXN + 1];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    ll n, m; cin >> n >> m;

    dp[0] = 2;

    for (int i = 1; i <= max(m, n); i++) {
        dp[i] += dp[i - 1];
        if (i > 1) dp[i] += dp[i - 2];
        if (dp[i] > MOD) dp[i] -= MOD;
    }

    cout << (dp[n] - 2 + dp[m]) % MOD << '\n';

    return 0;
}

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
#define MAXN 1000000

using namespace std;

int n;
ll dp[130000];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    dp[1] = 1;
    ll mm = n * (n + 1) / 2;

    if (mm % 2 != 0) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = mm; j >= i; j--) {
            dp[j] += dp[j - i];
            if (dp[j] >= MOD) dp[j] -= MOD;
        }
    }

    cout << dp[mm / 2] << '\n';

    return 0;
}

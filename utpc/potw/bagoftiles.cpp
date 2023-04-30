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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

ll c(int n, int k) {
    if (n - k < k) {
        k = n - k;
    }

    ll denom = 1;
    for (int i = 1; i <= k; i++) {
        denom *= i;
    }

    ll ans = 1;
    for (int i = 0; i < k; i++) {
        ans *= n - i;

        ll g = gcd(ans, denom);
        ans /= g;
        denom /= g;
    }

    return ans;
}

void solve() {
    int m;
    cin >> m;

    vector<int> tiles(m);
    for (int i = 0; i < m; i++) {
        cin >> tiles[i];
    }

    int n, t;
    cin >> n >> t;

    vector<vector<ll>> dp(n + 1, vector<ll>(t + 1, 0));
    dp[0][0] = 1;

    for (auto x : tiles) {
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j + x <= t; j++) {
                dp[i + 1][j + x] += dp[i][j];
            }
        }
    }

    ll total = c(m, n);

    cout << dp[n][t] << " : " << total - dp[n][t] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int g;
    cin >> g;

    for (int i = 1; i <= g; i++) {
        cout << "Game " << i << " -- ";
        solve();
    }

    return 0;
}

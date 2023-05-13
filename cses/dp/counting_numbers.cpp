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

ll solve(ll x) {
    if (x < 0) return 0;
    if (x == 0) return 1;

    string s = to_string(x);
    int n = s.size();

    // dp[idx][dig]
    // assumed to be less than the number
    vector dp(n, array<ll, 10>{});

    // skipping leading zero, that will be implicitly counted
    for (int d = 1; d < s[0] - '0'; d++) {
        dp[0][d] = 1;
    }

    // keeps track if prefix has no repeats
    bool prefix_works = true;

    // transitions
    for (int i = 1; i < n; i++) {
        // from less
        for (int d = 0; d <= 9; d++) {
            for (int p = 0; p <= 9; p++) {
                if (d != p) {
                    dp[i][d] += dp[i - 1][p];
                }
            }

            // from leading zeros only
            if (d != 0) {
                dp[i][d]++;
            }
        }

        // from equal
        int p = s[i - 1] - '0';
        for (int d = 0; d < s[i] - '0'; d++) {
            if (d != p && prefix_works) {
                dp[i][d]++;
            }
        }

        int c = s[i] - '0';
        prefix_works &= (c != p);
    }

    ll ans = 1;
    for (int i = 0; i <= 9; i++) {
        ans += dp[n - 1][i];
    }

    if (prefix_works) {
        ans++;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll a, b;
    cin >> a >> b;

    cout << solve(b) - solve(a - 1) << '\n';

    return 0;
}

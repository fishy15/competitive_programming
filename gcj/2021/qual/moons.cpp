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

ll ckmin(ll &a, ll b) {
    return a = min(a, b);
}

void solve() {
    int x, y; cin >> x >> y;
    string s; cin >> s;
    int n = s.size();

    vector<array<ll, 2>> dp(n, {INFLL, INFLL});
    dp[0] = {0, 0};

    for (int i = 1; i < n; i++) {
        if (s[i - 1] != 'J') {
            if (s[i] != 'J') {
                ckmin(dp[i][0], dp[i - 1][0]);
            }

            if (s[i] != 'C') {
                ckmin(dp[i][1], dp[i - 1][0] + x);
            }
        }

        if (s[i - 1] != 'C') {
            if (s[i] != 'J') {
                ckmin(dp[i][0], dp[i - 1][1] + y);
            }

            if (s[i] != 'C') {
                ckmin(dp[i][1], dp[i - 1][1]);
            }
        }
    }

    cout << min(dp[n - 1][0], dp[n - 1][1]) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

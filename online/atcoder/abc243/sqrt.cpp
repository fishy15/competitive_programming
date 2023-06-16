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
#define MAXN 60000

using namespace std;

ll dp[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    dp[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        for (int j = 0; j * j * j * j <= i; j++) {
            ll cnt = (ll) sqrtl(i) - j * j + 1;
            dp[i] += cnt * dp[j];
        }
    }

    int t; cin >> t;
    while (t--) {
        ll x; cin >> x;
        ll ans = 0;

        for (ll j = 0; j * j * j * j <= x; j++) {
            ll cnt = (ll) sqrtl(x) - j * j + 1;
            ans += cnt * dp[j];
        }

        cout << ans << '\n';
    }

    return 0;
}

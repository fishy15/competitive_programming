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

ll n, sq, ans;

ll s(ll x, ll y) {
    x--;
    x %= MOD;
    y %= MOD;
    ll v1 = x * (x + 1) / 2 % MOD;
    ll v2 = y * (y + 1) / 2 % MOD;
    ll ans = v2 - v1;
    if (ans < 0) ans += MOD;
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    sq = (ll)(sqrt(n));

    for (ll i = 1; n / i >= sq; i++) {
        ans += n / i * i % MOD;
        if (ans >= MOD) ans -= MOD;
    }

    for (ll i = sq - 1; i >= 1; i--) {
        ll top = n / i;
        ll bot = n / (i + 1) + 1;
        ans += i * s(bot, top) % MOD;
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans << '\n';

    return 0;
}

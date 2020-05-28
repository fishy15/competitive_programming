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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 500000

using namespace std;

ll ans;
int n, k;

ll f[MAXN + 1];
ll invf[MAXN + 1];

ll modpow(ll n, ll e) {
    if (e == 0) return 1;
    if (e == 1) return n % MOD;
    ll res = modpow(n, e / 2);
    if (e % 2 == 0) {
        return res * res % MOD;
    }
    return (res * res % MOD * n) % MOD;
}

ll choose(ll n, ll k) {
    return f[n] * invf[k] % MOD * invf[n - k] % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    f[0] = 1;
    invf[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        f[i] = f[i - 1] * i % MOD;
        invf[i] = modpow(f[i], MOD - 2);
    }

    for (int i = 1; i <= n; i++) {
        if (n / i < k) break;
        ans += choose(n / i - 1, k - 1);
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans << '\n';

    return 0;
}

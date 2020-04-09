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
#define MAXN 200000

using namespace std;

int n, k;
map<int, int> pos;
ll f[MAXN + 1];
ll f_inv[MAXN + 1];

ll modpow(ll n, ll e) {
    if (e == 0) return 1;
    if (e == 1) return n % MOD;
    ll val = modpow(n, e / 2);
    val = val * val % MOD;
    if (e % 2) val = val * n % MOD;
    return val;
}

ll c(int n, int k) {
    return f[n] * f_inv[k] % MOD * f_inv[n - k] % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        pos[l]++;
        pos[r + 1]--;
    }

    f[0] = 1;
    f_inv[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * i % MOD;
        f_inv[i] = modpow(f[i], MOD - 2);
    }

    int cur = pos.begin()->first;
    int val = 0;
    ll ans = 0;
    for (auto x : pos) {
        int d = x.first - cur;
        if (d > 0 && val >= k) {
            ans += d * c(val, k) % MOD;
            if (ans >= MOD) ans -= MOD;
        }
        val += x.second;
        cur = x.first;
    }

    cout << ans << '\n';

    return 0;
}

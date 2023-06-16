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
#define MAXN 1000010

using namespace std;

ll f[MAXN];
ll finv[MAXN];

ll c(int n, int k) {
    return f[n] * finv[k] % MOD * finv[n - k] % MOD;
}

ll modpow(ll n, int e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = n * res % MOD;
        n = n * n % MOD;
        e >>= 1;
    }
    return res;
}

void solve() {
    int n; cin >> n;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }
    int sz = cnt.rbegin()->second;
    ll tot = modpow(2, n);
    if (sz % 2 == 0) {
        tot -= c(sz, sz / 2) * modpow(2, n - sz) % MOD;
        if (tot < 0) tot += MOD;
    }
    cout << tot << '\n';
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    f[0] = 1;
    finv[0] = 1;

    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i % MOD;
        finv[i] = modpow(f[i], MOD - 2);
    }

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

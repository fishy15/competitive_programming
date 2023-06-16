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
#define MOD 998244353 

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, k;
int nums[MAXN];
ll f[MAXN];
ll finv[MAXN];
ll ans = 0;

ll modpow(ll n, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * n % MOD;
        n = n * n % MOD;
        e >>= 1;
    }
    return res;
}

inline ll c(ll n, ll k) {
    return f[n] * finv[k] % MOD * finv[n - k] % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    f[0] = 1;
    finv[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i % MOD;
        finv[i] = modpow(f[i], MOD - 2);
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] != nums[(i + 1) % n]) {
            cnt++;
        }
    }

    for (int i = 0; i < cnt; i++) {
        ll ways;
        if ((cnt - i) % 2 == 0) {
            ways = modpow(2, cnt - i) - c(cnt - i, (cnt - i) / 2);
            ways %= MOD;
            if (ways < 0) ways += MOD;
            ways = ways * modpow(2, MOD - 2) % MOD;
        } else {
            ways = modpow(2, cnt - i - 1);
        }

        ans += modpow(k - 2, i) * c(cnt, i) % MOD * ways % MOD;
        ans %= MOD;
    }

    cout << modpow(k, n - cnt) * ans % MOD << '\n';

    return 0;
}

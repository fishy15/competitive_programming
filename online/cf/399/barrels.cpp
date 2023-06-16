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
#define MAXN 100000

using namespace std;

ll f, w, h;

ll ok;
ll tot;
ll fact[MAXN + 10];
ll inv[MAXN + 10];

long long modpow(long long a, long long b, ll m) {
    long long res = 1;
    while (b > 0) {
        res %= m;
        a %= m;
        if (b & 1) {
            res = res * a;
            res %= m;
        }
        a = a * a;
        a %= m;
        b >>= 1;
    }
    return res;
}

ll c(ll n, ll k) {
    if (n < 0 || k < 0 || n - k < 0) return 0;
    return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
}

void calc(ll ff, ll ww) {
    ll fl = f - ff;
    ll wln = w - ww;
    ll wl = w - (h + 1) * ww;
    if (fl < 0 || wln < 0) return;

    ll tot2 = c(fl + ff - 1, ff - 1) * c(wln + ww - 1, ww - 1) % MOD;
    if (tot2 >= MOD) tot2 -= MOD;
    ll ok2 = c(fl + ff - 1, ff - 1) * c(wl + ww - 1, ww - 1) % MOD;
    if (ok2 >= MOD) ok2 -= MOD;

    if (ff == ww) {
        tot2 *= 2;
        if (tot2 >= MOD) tot2 -= MOD;
        ok2 *= 2;
        if (ok2 >= MOD) ok2 -= MOD;
    }

    tot += tot2;
    ok += ok2;
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    cin >> f >> w >> h;

    if (f == 0) {
        cout << (w > h) << '\n';
        return 0;
    } else if (w == 0) {
        cout << 1 << '\n';
        return 0;
    }

    fact[0] = 1;
    inv[0] = 1;
    for (ll i = 1; i <= MAXN + 5; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        inv[i] = modpow(fact[i], MOD - 2, MOD);
    }

    for (ll i = 1; i <= f; i++) {
        for (ll d = -1; d <= 1; d++) {
            if (i + d > 0 && i + d <= w) {
                calc(i, i + d);
            }
        }
    }

    ok %= MOD;
    cout << ok * modpow(tot, MOD - 2, MOD) % MOD << '\n';

    return 0;
}

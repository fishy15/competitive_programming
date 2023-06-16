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
#define MAXN 1000010

using namespace std;

int n;
ll f[MAXN];
ll finv[MAXN];

ll modpow(ll n, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * n % MOD;
        n = n * n % MOD;
        e >>= 1;
    }
    return res;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    f[0] = 1;
    finv[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i % MOD;
        finv[i] = modpow(f[i], MOD - 2);
    }

    cin >> n;
    while (n--) {
        ll a, b; cin >> a >> b;
        cout << f[a] * finv[b] % MOD * finv[a - b] % MOD << '\n';
    }

    return 0;
}

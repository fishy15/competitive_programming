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

ll modpow(ll n, ll e) {
    ll ans = 1;
    while (e) {
        if (e & 1) ans = ans * n % MOD;
        n = n * n % MOD;
        e >>= 1;
    }
    return ans;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<ll> dc(n);
    bool ok = true;
    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
       dc[x]++;
    }

    dc[0] = 1;
    for (int i = 1; i < n; i++) {
        if (dc[i] && !dc[i - 1]) ok = false;
    }

    if (!ok) {
        cout << "0\n";
        return;
    }

    ll ans = 1;
    ll tot = 0;
    for (int i = 1; i < n; i++) {
        ans *= modpow(dc[i - 1], dc[i]);
        ans %= MOD;
        tot += dc[i] * (dc[i] - 1) / 2 % MOD;
        if (tot >= MOD) tot -= MOD;
    }

    m -= n - 1;
    ll num = 1;
    ll denom = 1;
    for (int i = 0; i < m; i++) {
        num *= (tot - i + MOD) % MOD;
        num %= MOD;
        denom *= i + 1;
        denom %= MOD;
    }
    
    cout << (ans * num % MOD * modpow(denom, MOD - 2) % MOD) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();
    
    return 0;
}
 

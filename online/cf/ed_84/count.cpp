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
#define MAXN 998244353

using namespace std;

ll modpow(ll num, ll exp, ll mod) {
    if (exp == 0) {
        return 1;
    }

    if (exp == 1) {
        return num;
    }

    ll val = 0;
    if (exp % 2 == 0) {
        val = modpow(num, exp / 2, mod);
        val *= val;
    } else {
        val = modpow(num, exp - 1, mod) * num;
    }

    val %= mod;
    return val;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            cout << "10\n";
            return 0;
        }

        ll ans = 0;
        // ends
        int rem = n - i - 1;
        ans += 2 * 10 * 9 * modpow(10, rem, MOD) % MOD;
        if (ans >= MOD) ans -= MOD;
        
        // mid
        if (i < n - 1) {
            int rem = n - i - 2;
            int spots = n - i - 1;
            ans += spots * 10 % MOD * 9 * 9 % MOD * modpow(10, rem, MOD) % MOD;
            if (ans >= MOD) ans -= MOD;
        }

        cout << ans << ' ';
    }

    return 0;
}

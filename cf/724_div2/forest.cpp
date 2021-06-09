/*
 * If we fix the locations that have zeroes, the rest of the locations must be fixed as well due to the 
 * conditions. Therefore, the answer is 2^(number of #s).
 */

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
    ll res = 1;
    while (e) {
        if (e & 1) res = res * n % MOD;
        n = n * n % MOD;
        e >>= 1;
    }
    return res;
}

void solve() {
    int n, m; cin >> n >> m;
    int cnt = 0;
    
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (char c : s) {
            if (c == '#') {
                cnt++;
            }
        }
    }

    ll ans = modpow(2, cnt);
    if (cnt == n * m) {
        ans--;
        if (ans == 0) ans += MOD;
    }

    cout << ans << '\n'; 
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

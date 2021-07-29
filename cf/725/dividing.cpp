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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

ll fact(ll x) {
    ll ans = 0;

    while (x % 2 == 0) {
        x /= 2;
        ans++;
    }

    for (ll i = 3; i <= sqrt(x) + 1; i += 2) {
        while (x % i == 0) {
            x /= i;
            ans++;
        }
    }

    if (x != 1) {
        ans++;
    }
    
    return ans;
}

void solve() {
    ll a, b, k; cin >> a >> b >> k;
    ll g = gcd(a, b);

    int max_mv = 0;
    max_mv += fact(a);
    max_mv += fact(b);

    a /= g;
    b /= g;

    int min_mv = 0;
    if (a > 1) min_mv++;
    if (b > 1) min_mv++;
    if (a == b) min_mv = 2;

    if (min_mv <= k && k <= max_mv) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

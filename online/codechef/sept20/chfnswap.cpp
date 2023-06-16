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

void solve() {
    ll n; cin >> n;
    
    ll sum = n * (n + 1) / 2;
    if (sum % 2 == 1) {
        cout << "0\n";
        return;
    }

    ll l = 1;
    ll r = n;
    ll ans = 0;
    while (l <= r) {
        ll m = (l + r) / 2;
        ll s = m * (m + 1) / 2;
        if (s <= sum / 2) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    ll cnt = 0;
    for (ll i = max(1LL, ans - 10); i <= min(n, ans + 10); i++) {
        ll s1 = i * (i + 1) / 2;
        ll d = sum / 2 - s1;
        ll low = max(1 + d, i + 1);
        ll high = min(i + d, n); 
        if (low <= high) cnt += high - low + 1;
        if (d == 0) {
            cnt += i * (i - 1) / 2;
            cnt += (n - i) * (n - i - 1) / 2;
        }
    }
    cout << cnt << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

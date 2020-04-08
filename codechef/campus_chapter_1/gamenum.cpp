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
#define MAXN 1000000

using namespace std;

int len(ll x) {
    int l = 0;
    while ((1LL << l) <= x) l++;
    return l - 1;
}

void solve() {
    ll a, b; cin >> a >> b;
    ll ans = 0;
    int s = 0;
    int l = len(max(a, b));

    for (int i = 0; i < 3600; i++) {
        if ((a ^ b) > ans) {
            ans = a ^ b;
            s = i;
        }
        b = (b >> 1) + ((b & 1) << l);
    }

    cout << s << ' ' << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

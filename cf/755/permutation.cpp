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
#include <functional>
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

ll ask(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    ll a; cin >> a;
    if (a == -1) exit(0);
    return a;
}

ll tri(ll n) {
    return n * (n + 1) / 2;
}

ll find(ll x) {
    ll l = 0;
    ll r = 1000000000;
    ll ans = -1;

    while (l <= r) {
        ll m = (l + r) / 2;
        if (tri(m) <= x) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return ans;
}

void solve() {
    int n; cin >> n;

    // find i
    int ans = -1;
    int l = 1;
    int r = n;
    while (l <= r) {
        int m = (l + r) / 2;
        ll a = ask(1, m);
        if (a == 0) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    ll tot = ask(1, n);
    ll first = ask(ans + 1, n);

    ll part1 = tot - first;
    ll part2 = find(tot - tri(part1));

    cout << "! " << ans << ' ' << ans + part1 + 1 << ' ' << ans + part1 + 1 + part2 << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

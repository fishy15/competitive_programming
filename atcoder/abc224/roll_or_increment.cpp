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

ll n, s, t, a, b;
ld ans = INFLL;

ld calc(ll x) {
    x = t - x + 1;
    return (ld) (x - 1) / 2 * a + (ld) n / x * b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> s >> t >> a >> b;

    ll l, r;
    if (s <= t) {
        ans = a * (t - s);
        l = s + 1;
        r = t;
    } else {
        l = 1;
        r = t;
    }

    while (l <= r) {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        
        ld v1 = calc(m1);
        ld v2 = calc(m2);
        ans = min(ans, v1);
        ans = min(ans, v2);

        if (v1 < v2) {
            r = m2 - 1;
        } else {
            l = m1 + 1;
        }
    }

    cout << fixed << setprecision(12) << ans << '\n';

    return 0;
}

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

void solve() {
    ll h, c, t; cin >> h >> c >> t;
    if (t <= (h + c) / 2.0) {
        cout << 2 << '\n';
    } else {
        ll l = 0;
        ll r = 1e9;
        ll a = -1;
        while (l <= r) {
            ll m = l + (r - l) / 2;
            if (1.0 * (h * (m + 1) + c * m) / (2 * m + 1) >= t) {
                a = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        
        double v1 = 1.0 * (h * (a + 1) + c * a) / (2 * a + 1);
        double v2 = 1.0 * (h * (a + 2) + c * (a + 1)) / (2 * a + 3);
        if (abs(v2 - t) < abs(v1 - t)) {
            a++;
        }

        cout << 2 * a + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

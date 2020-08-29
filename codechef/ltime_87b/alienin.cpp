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
    int n, d; cin >> n >> d;
    vector<int> c;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        c.push_back(x);
    }

    sort(c.begin(), c.end());

    ld l = 0;
    ld r = 1e18;
    ld ans = 0;

    for (int i = 0; i < 200; i++) {
        ld m = (l + r) / 2;
        ld pt = 0;
        bool ok = true;
        for (int j : c) {
            pt = max((ld)j, pt);
            if (pt > j + d) {
                ok = false;
                break;
            }
            pt += m;
        }

        if (ok) {
            ans = m;
            l = m;
        } else {
            r = m;
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cout << fixed << setprecision(12);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

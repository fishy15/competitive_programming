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
    int n; cin >> n;
    vector<ll> x, y;
    for (int i = 0; i < 2 * n; i++) {
        ll a, b; cin >> a >> b;
        if (a == 0) {
            y.push_back(abs(b));
        } else {
            x.push_back(abs(a));
        }
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    ld ans = 0;
    for (int i = 0; i < n; i++) {
        ans += sqrt(x[i] * x[i] + y[i] * y[i]);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    cout << fixed << setprecision(12);
    while (t--) solve();

    return 0;
}

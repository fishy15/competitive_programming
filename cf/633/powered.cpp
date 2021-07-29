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
    int n; cin >> n;
    ll m; cin >> m;
    ll d = 0;
    for (int i = 0; i < n - 1; i++) {
        ll x; cin >> x;
        if (x < m) {
            d = max(d, m - x);
        } else {
            m = x;
        }
    }

    int cnt = 0;
    if (d == 0) {
        cout << 0 << '\n';
    } else {
        cout << (int)log2(d) + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

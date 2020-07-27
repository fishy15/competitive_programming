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

ll ckmax(ll &a, ll b) {
    return a = max(a, b);
}

void solve() {
    int n; cin >> n;
    vector<pair<ll, ll>> tree;
    map<ll, ll> best;

    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        tree.push_back({x, y});
    }

    sort(tree.begin(), tree.end());

    ll ans = 0;
    for (auto &[p, h] : tree) {
        ckmax(best[p + h], best[p] + h);
        ckmax(best[p], best[p - h] + h);
        ckmax(ans, best[p + h]);
        ckmax(ans, best[p]);
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

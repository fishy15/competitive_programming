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

void solve() {
    ll n, P, l, t;
    cin >> n >> P >> l >> t;

    auto total_tasks = (n + 6) / 7;

    ll lo = 0;
    ll hi = n;
    ll ans = -1;

    auto comp = [&](ll days) {
        auto tasks = min(total_tasks, 2 * days);
        return t * tasks + days * l;
    };

    while (lo <= hi) {
        auto m = lo + (hi - lo) / 2;
        auto v = comp(m);
        if (v < P) {
            lo = m + 1;
        } else {
            ans = m;
            hi = m - 1;
        }
    }

    cout << n - ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

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
    ll n, x, p;
    cin >> n >> x >> p;

    int needed = x == 0 ? 0 : n - x;

    ll steps = 0;
    for (ll i = 1, cur_step = 1; i <= min(2 * n, p); i++, cur_step++) {
        if (cur_step >= n) cur_step -= n;

        steps += cur_step;
        if (steps >= n) steps -= n;

        if (needed == steps) {
            cout << "Yes\n";
            return;
        }
    }

    cout << "No\n";
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

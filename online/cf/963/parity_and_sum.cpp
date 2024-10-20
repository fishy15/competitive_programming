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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> even, odd;
    rep(i, 0, n) {
        int x;
        cin >> x;
        if (x % 2 == 0) {
            even.push_back(x);
        } else {
            odd.push_back(x);
        }
    }

    if (sz(even) == 0 || sz(odd) == 0) {
        cout << "0\n";
        return;
    }

    sort(all(even));
    sort(all(odd));

    ll best_odd = odd.back();
    int ops = 0;
    for (auto e : even) {
        if (e < best_odd) {
            ops++;
            best_odd += e;
        } else {
            ops += 2;
            best_odd += 2 * e;
        }
    }

    // going top down
    ops = min(ops, sz(even) + 1);

    cout << ops << '\n';
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

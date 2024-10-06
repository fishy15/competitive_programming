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

    ld max_low = 0;
    ld min_high = INFLL;

    rep(i, 0, n) {
        int a, b;
        cin >> a >> b;
        max_low = max(max_low, (ld) (i + 1) / b);
        if (a != 0) {
            min_high = min(min_high, (ld) (i + 1) / a);
        }
    }

    if (min_high < max_low - eps) {
        cout << "-1\n";
    } else {
        cout << max_low << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    cout << fixed << setprecision(15);
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

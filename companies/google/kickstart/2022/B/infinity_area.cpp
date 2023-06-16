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

#define PI 3.14159265358979323846

using namespace std;

void solve() {
    ll r, a, b; cin >> r >> a >> b;
    ll ans = 0;

    bool do_a = true;
    while (r > 0) {
        ans += r * r;
        if (do_a) {
            r *= a;
        } else {
            r /= b;
        }

        do_a = !do_a;
    }

    cout << PI * ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;

    cout << fixed << setprecision(12);

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

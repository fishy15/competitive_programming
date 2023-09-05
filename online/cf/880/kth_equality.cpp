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

int pow10(int p) {
    int res = 1;
    for (int i = 0; i < p; i++) {
        res *= 10;
    }
    return res;
}

void solve() {
    int a, b, c;
    ll k;
    cin >> a >> b >> c >> k;

    k--;

    int min_b = pow10(b - 1);
    int max_b = pow10(b) - 1;
    int min_c = pow10(c - 1);
    int max_c = pow10(c) - 1;
    ll so_far = 0;
    for (int i = pow10(a - 1); i < pow10(a); i++) {
        int low_b = max(min_c - i, min_b);
        int high_b = min(max_c - i, max_b);
        if (low_b <= high_b) {
            ll total = high_b - low_b + 1;
            if (so_far + total > k) {
                ll pos = k - so_far;
                cout << i << " + " << low_b + pos << " = " << (i + low_b + pos) << '\n';
                return;
            }
            so_far += total;
        }
    }

    cout << "-1\n";
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

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
#include <cassert>

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

int get_bit(int x, int i) {
    return x & (1 << i);
}

void solve() {
    int l, r;
    cin >> l >> r;

    // find first split point
    int prefix = 0;
    int a = -1, b = -1, c = -1;
    for (int i = 30; i >= 0; i--) {
        if (get_bit(l, i) == get_bit(r, i)) {
            prefix += get_bit(l, i);
        } else {
            b = prefix + (1 << i);
            a = b - 1;
            break;
        }
    }

    assert(a != -1);
    assert(b != -1);

    for (int i = l; i <= r; i++) {
        if (i != a && i != b) {
            c = i;
            break;
        }
    }

    assert(c != -1);

    cout << a << ' ' << b << ' ' << c << '\n';
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

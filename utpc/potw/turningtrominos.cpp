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
    ll x, y;
    cin >> x >> y;

    ll cur = 1;
    while (min(x, y) >= cur || max(x, y) >= 2 * cur) {
        cur *= 2;
    }

    int ans_x = 1;
    int ans_y = 1;
    while (cur > 1) {
        cur /= 2;
        // middle portion
        if (cur <= min(x, y) && max(x, y) < 3 * cur) {
            x -= cur;
            y -= cur;
            cur *= 2; // just for next iter
        } else {
            if (x >= 2 * cur) {
                ans_x *= -1;
                x = 4 * cur - x - 1;
            } else if (y >= 2 * cur) {
                ans_y *= -1;
                y = 4 * cur - y - 1;
            }
        }

        /* cout << x << ' ' << y << '\n'; */
    }

    if (ans_x == 1) {
        if (ans_y == 1) {
            cout << 0 << '\n';
        } else {
            cout << 1 << '\n';
        }
    } else {
        if (ans_y == 1) {
            cout << 3 << '\n';
        } else {
            cout << 2 << '\n';
        }
    }
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

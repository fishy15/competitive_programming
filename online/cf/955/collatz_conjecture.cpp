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
    int x, y, k;
    cin >> x >> y >> k;

    while (k > 0) {
        int nxt_mult = (x + y) / y * y;
        int ops_until = nxt_mult - x;
        if (k < ops_until) {
            x += k;
            k = 0;
        } else {
            k -= ops_until;
            int nxt_x = nxt_mult;
            while (nxt_x % y == 0) {
                nxt_x /= y;
            }

            // we have entered a cycle
            // mod k by the cycle length
            if (nxt_x == x) {
                k %= ops_until; 
            } else {
                x = nxt_x;
            }
        }
    }

    cout << x << '\n';
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

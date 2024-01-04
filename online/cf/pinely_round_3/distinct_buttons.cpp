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
    int n;
    cin >> n;

    bool x_pos = false;
    bool x_neg = false;
    bool y_pos = false;
    bool y_neg = false;

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        if (x < 0) {
            x_neg = true;
        } else if (x > 0) {
            x_pos = true;
        }
        if (y < 0) {
            y_neg = true;
        } else if (y > 0) {
            y_pos = true;
        }
    }

    if (x_pos && x_neg && y_pos && y_neg) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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

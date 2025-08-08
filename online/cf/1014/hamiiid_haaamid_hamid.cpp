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
    int n, x;
    cin >> n >> x;
    x--;

    string grid;
    cin >> grid;

    set<int> walls;
    rep(i, 0, n) {
        if (grid[i] == '#') {
            walls.insert(i);
        }
    }

    int ans = 0;
    rep(i, 0, n) {
        if (grid[i] == '.' && i != x) {
            walls.insert(i);

            // if we initially go to the right
            auto it = walls.upper_bound(x);
            int right;
            if (it == end(walls)) {
                right = 0;
            } else {
                right = min(*it + 1, n - *it);
            }

            // if we initially go to the left
            int left;
            if (it == begin(walls)) {
                left = 0;
            } else {
                left = min(*prev(it) + 1, n - *prev(it));
            }


            ans = max(ans, min(left, right));

            walls.erase(i);
        }
    }

    cout << ans + 1 << '\n';
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

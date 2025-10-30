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

    vector<string> grid(n);
    int cnt = 0;
    rep(i, 0, n) {
        cin >> grid[i];
        cnt += count(all(grid[i]), '#');
    }

    if (cnt == 4) {
        // check for 2x2 case
        rep(i, 0, n-1) {
            rep(j, 0, n-1) {
                if (grid[i][j] == '#' && grid[i+1][j] == '#' && grid[i][j+1] == '#' && grid[i+1][j+1] == '#') {
                    cout << "YES\n";
                    return;
                }
            }
        }
    }

    set<int> sums, diffs;
    rep(i, 0, n) {
        rep(j, 0, n) {
            if (grid[i][j] == '#') {
                sums.insert(i + j);
                diffs.insert(i - j);
            }
        }
    }

    if (cnt == 0) {
        cout << "YES\n";
    } else if (sz(sums) == 1) {
        cout << "YES\n";
    } else if (sz(sums) == 2 && *sums.begin() + 1 == *sums.rbegin()) {
        cout << "YES\n";
    } else if (sz(diffs) == 1) {
        cout << "YES\n";
    } else if (sz(diffs) == 2 && *diffs.begin() + 1 == *diffs.rbegin()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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

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
    int r, c, k; cin >> r >> c >> k;
    k--;
    vector<string> grid(r);
    for (int i = 0; i < r; i++) {
        cin >> grid[i];
    }

    // no up or down
    int ans = 0;
    for (int i = 0; i < c; i++) {
        if (grid[k][i] == 'X') {
            ans++;
        }
    }

    // solve moving up and down
    for (int a = 0; a < 2; a++) {
        vector<int> below(c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] == 'X') {
                    below[j]++;
                }
            }

            if (i >= k) {
                int ans2 = i - k;
                for (int j = 0; j < c; j++) {
                    if (grid[i][j] == 'X' || below[j] >= k + 1) {
                        ans2++;
                    }
                }
                ans = min(ans, ans2);
            }
        }

        int ans2 = r - k;
        for (int j = 0; j < c; j++) {
            if (below[j] >= k + 1) {
                ans2++;
            }
        }
        ans = min(ans, ans2);

        // flip to reuse same code
        reverse(grid.begin(), grid.end()); 
        k = r - k - 1;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n, m, x, y; cin >> n >> m >> x >> y;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    if (2 * x <= y) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (char c : grid[i]) {
                if (c == '.') cnt++;
            }
        }
        cout << x * cnt << '\n';
    } else {
        int cnt1 = 0;
        int cnt2 = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j < m - 1 && grid[i][j] == '.' && grid[i][j + 1] == '.') {
                    cnt2++;
                    j++;
                } else if (grid[i][j] == '.') {
                    cnt1++;
                }
            }
        }
        cout << x * cnt1 + y * cnt2 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

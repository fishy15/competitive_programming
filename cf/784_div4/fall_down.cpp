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
    int n, m; cin >> n >> m;
    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    for (int c = 0; c < m; c++) {
        for (int r = n - 1; r >= 0; r--) {
            if (grid[r][c] == '*') {
                int r2 = r + 1;
                while (r2 < n && grid[r2][c] == '.') {
                    swap(grid[r2 - 1][c], grid[r2][c]);
                    r2++;
                }
            }
        }
    }

    for (string s : grid) {
        cout << s << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

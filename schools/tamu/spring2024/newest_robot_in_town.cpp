#pragma GCC target("popcnt")

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
#include <bitset>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

bitset<400> grid[400];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < m; j++) {
            if (row[j] == 'X') {
                grid[i][j] = 1;
            }
        }
    }

    ld ans = 0;
    for (int dx = 0; dx <= n; dx++) {
        for (int dy = -m; dy <= m; dy++) {
            if (dx == 0 && dy <= 0) continue;
            ld dist = hypot(dx, dy);
            for (int row = 0; row < n; row++) {
                int other_row = row + dx;
                if (other_row < n) {
                    int cnt;
                    if (dy < 0) {
                        cnt = ((grid[row] >> (-dy)) & grid[other_row]).count();
                    } else {
                        cnt = ((grid[row] << dy) & grid[other_row]).count();
                    }
                    ans += cnt * dist;
                }
            }
        }
    }

    cout << fixed << setprecision(15);
    cout << ans << '\n';

    return 0;
}

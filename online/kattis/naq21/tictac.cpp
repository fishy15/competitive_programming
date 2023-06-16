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

int conv(int x) {
    int cur = 1;
    int ans = 0;
    while (x > 0) {
        ans += (x % 10) * cur;
        cur *= 8;
        x /= 10;
    }
    return ans;
}

void solve() {
    int x; cin >> x;
    x = conv(x);

    vector<vector<char>> grid(3, vector<char>(3));

    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        int r = i % 3;
        int c = i / 3;
        if (x & (1 << i)) {
            cnt++;
            if (x & (1 << (i + 9))) {
                grid[r][c] = 'X';
            } else {
                grid[r][c] = 'O';
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (grid[i][0] && grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]) {
            cout << grid[i][0] << " wins\n";
            return;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (grid[0][i] && grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i]) {
            cout << grid[0][i] << " wins\n";
            return;
        }
    }

    if (grid[0][0] && grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) {
        cout << grid[0][0] << " wins\n";
        return;
    }

    if (grid[0][2] && grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]) {
        cout << grid[0][2] << " wins\n";
        return;
    }

    if (cnt == 9) {
        cout << "Cat's\n";
    } else {
        cout << "In progress\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

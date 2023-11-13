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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    auto flip = [&](int i, int j) {
        if (grid[i][j] == 'o') {
            grid[i][j] = 'X';
        } else {
            grid[i][j] = 'o';
        }
    };

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (grid[i][j] == 'X') {
                flip(i, j);
                flip(i, j + 1);
                flip(i + 1, j);
                flip(i + 1, j + 1);
            }
        }
    }

    int last_col = 0;
    for (int i = 0; i < n - 1; i++) {
        if (grid[i][m - 1] == 'X') {
            last_col++;
        }
    }

    int last_row = 0;
    for (int i = 0; i < m - 1; i++) {
        if (grid[n - 1][i] == 'X') {
            last_row++;
        }
    }

    int ans = max(last_col, last_row);
    int last = min(last_row, last_col) % 2;
    if (grid[n - 1][m - 1] == 'X') {
        last = 1 - last;
    }
    ans += last;

    cout << ans << '\n';

    return 0;
}

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

    int r, c;
    cin >> r >> c;

    vector<string> grid(r);
    for (int i = 0; i < r; i++) {
        cin >> grid[i];
    }

    auto is_bomb = [&](int x, int y) { return grid[x][y] != '.' && grid[x][y] != '#'; };

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (is_bomb(i, j)) {
                int p = grid[i][j] - '0';
                grid[i][j] = '.';
                for (int x = 0; x < r; x++) {
                    for (int y = 0; y < c; y++) {
                        if (abs(i - x) + abs(j - y) <= p && grid[x][y] == '#') {
                            grid[x][y] = '.';
                        }
                    }
                }
            }
        }
    }

    for (auto &row : grid) {
        cout << row << '\n';
    }

    return 0;
}

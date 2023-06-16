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

struct node {
    vector<array<int, 3>> par;
    bool reach;
    bool ans_p;

    node() : par{}, reach(false), ans_p(false) {}
};

int r, c;
string grid[310];
node dp[310][310][310]; // row, col, height

bool ok(int x, int y, int h) {
    return x >= 0 && y >= 0 && x < r && y < c && h >= 0 && h <= 300 && dp[x][y][h].reach;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> r >> c;
    for (int i = 0; i < c; i++) {
        cin >> grid[i];
    }

    for (int i = 0; i < c; i++) {
        if (grid[r - 1][c] == 'M') {
            dp[r - 1][c][0].reach = true;
            break;
        }
    }

    for (int i = r - 2; r >= 0; r--) {
        for (int h = 0; h <= 300; h++) {

        }
    }

    return 0;
}

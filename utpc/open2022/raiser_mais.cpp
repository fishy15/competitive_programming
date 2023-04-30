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

int n, m;
string grid[310];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

enum Dir {
    L, D, R, U
};

int forw[4] = {D, L, U, R};
int back[4] = {U, R, D, L};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    int sx, sy;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];

        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'O') {
                sx = i;
                sy = j;
            }
        }
    }

    int d;
    if (sx == 0) {
        d = D;
    } else if (sy == 0) {
        d = R;
    } else if (sx == n - 1) {
        d = U;
    } else {
        d = L;
    }

    sx += dx[d];
    sy += dy[d];

    while (grid[sx][sy] != '#') {
        if (grid[sx][sy] == '.') {
            grid[sx][sy] = '@';
        } else if (grid[sx][sy] == '/') {
            d = forw[d];
        } else if (grid[sx][sy] == '\\') {
            d = back[d];
        }

        sx += dx[d];
        sy += dy[d];
    }

    for (int i = 0; i < n; i++) {
        cout << grid[i] << '\n';
    }

    return 0;
}

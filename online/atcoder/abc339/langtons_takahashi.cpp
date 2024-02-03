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

array dx{-1, 0, 1, 0};
array dy{0, 1, 0, -1};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int h, w, n;
    cin >> h >> w >> n;

    vector<string> grid(h, string(w, '.'));

    int x = 0;
    int y = 0;
    int d = 0;

    for (int i = 0; i < n; i++) {
        if (grid[x][y] == '.') {
            grid[x][y] = '#';
            d++;
            if (d >= 4) d -= 4;
        } else {
            grid[x][y] = '.';
            d--;
            if (d < 0) d += 4;
        }

        x += dx[d];
        y += dy[d];
        if (x >= h) x -= h;
        if (x < 0) x += h;
        if (y >= w) y -= w;
        if (y < 0) y += w;
    }

    for (auto &row : grid) {
        cout << row << '\n';
    }

    return 0;
}

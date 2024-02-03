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

array dx{0, 1, 0, -1};
array dy{-1, 0, 1, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    int sx1 = -1, sy1 = -1;
    int sx2 = -1, sy2 = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'P') {
                if (sx1 == -1) {
                    sx1 = i;
                    sy1 = j;
                } else {
                    sx2 = i;
                    sy2 = j;
                }
            }
        }
    }

    queue<tuple<int, int, int, int>> q;
    vector d(n, vector(n, vector(n, vector(n, INF))));
    q.push({sx1, sy1, sx2, sy2});
    d[sx1][sy1][sx2][sy2] = 0;

    auto ok = [&](int x, int y) {
        return x >= 0 && y >= 0 && x < n && y < n && grid[x][y] != '#';
    };

    while (!q.empty()) {
        auto [x1, y1, x2, y2] = q.front();
        q.pop();

        if (x1 == x2 && y1 == y2) {
            cout << d[x1][y1][x2][y2] << '\n';
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx1 = x1 + dx[i];
            int ny1 = y1 + dy[i];
            int nx2 = x2 + dx[i];
            int ny2 = y2 + dy[i];

            if (!ok(nx1, ny1)) {
                nx1 = x1;
                ny1 = y1;
            }

            if (!ok(nx2, ny2)) {
                nx2 = x2;
                ny2 = y2;
            }

            if (d[nx1][ny1][nx2][ny2] == INF) {
                d[nx1][ny1][nx2][ny2] = d[x1][y1][x2][y2] + 1;
                q.push({nx1, ny1, nx2, ny2});
            }
        }
    }

    cout << "-1\n";

    return 0;
}

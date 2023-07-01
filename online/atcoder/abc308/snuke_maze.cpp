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

constexpr array<int, 4> dx = {0, 1, 0, -1};
constexpr array<int, 4> dy = {1, 0, -1, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int h, w;
    cin >> h >> w;

    vector<string> grid(h);
    for (auto &row : grid) {
        cin >> row;
    }

    string snuke = "snuke";
    if (grid[0][0] != 's') {
        cout << "No\n";
        return 0;
    }

    vector d(h, vector(w, array<int, 5>{}));
    for (auto &row : d) {
        for (auto &arr : row) {
            arr.fill(-1);
        }
    }

    d[0][0][0] = 0;
    queue<array<int, 3>> q;
    q.push({0, 0, 0});

    auto ok = [&](int x, int y, int m) {
        return x >= 0 && y >= 0 && x < h && y < w && d[x][y][m] == -1 && snuke[m] == grid[x][y];
    };

    while (!q.empty()) {
        auto [x, y, m] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nd = d[x][y][m] + 1;
            int nm = (m + 1) % 5;

            if (ok(nx, ny, nm)) {
                d[nx][ny][nm] = nd;
                q.push({nx, ny, nm});
            }
        }
    }

    const auto &last = d[h - 1][w - 1];
    if (*max_element(last.begin(), last.end()) != -1) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}

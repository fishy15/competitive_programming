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

array<int, 4> dx = {0, -1, 0, 1};
array<int, 4> dy = {1, 0, -1, 0};

int shortest_path(pair<int, int> start, pair<int, int> end, const vector<string> &grid, char zero) {
    int n = grid.size();

    auto [sx, sy] = start;
    auto [ex, ey] = end;

    deque<array<int, 3>> q;
    vector dist(n, vector(n, INF));

    q.push_back({0, sx, sy});
    dist[sx][sy] = 0;

    while (!q.empty()) {
        auto [d, x, y] = q.front();

        q.pop_front();
        if (dist[x][y] != d) {
            continue;
        }

        for (int i = 0; i < 4; i++) {
            auto nx = x + dx[i];
            auto ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                auto is_zero = grid[nx][ny] == zero;
                auto nd = d + (is_zero ? 0 : 1);
                if (nd < dist[nx][ny]) {
                    dist[nx][ny] = nd;
                    if (is_zero) {
                        q.push_front({nd, nx, ny});
                    } else {
                        q.push_back({nd, nx, ny});
                    }
                }
            }
        }
    }

    return dist[ex][ey];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    int d1 = shortest_path({0, 0}, {n-1, n-1}, grid, 'R');
    int d2 = shortest_path({0, n-1}, {n-1, 0}, grid, 'B');

    cout << d1 + d2 << '\n';

    return 0;
}

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

    int n, s;
    cin >> n >> s;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector min_bee(n, vector<int>(n, INF));

    auto valid = [&](int x, int y, string ok) {
        if (x >= 0 && y >= 0 && x < n && y < n) {
            return count(ok.begin(), ok.end(), grid[x][y]) > 0;
        }
        return false; 
    };

    queue<array<int, 2>> q;
    array<int, 2> start, end;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'H') {
                min_bee[i][j] = 0;
                q.push({i, j});
            } else if (grid[i][j] == 'M') {
                start = {i, j};
            } else if (grid[i][j] == 'D') {
                end = {i, j};
            }
        }
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (valid(nx, ny, "GM") && min_bee[nx][ny] == INF) {
                min_bee[nx][ny] = min_bee[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    vector min_reach(n, vector<int>(n));
    auto check = [&](int wait) {
        queue<array<int, 2>> q;
        
        if (wait >= min_bee[start[0]][start[1]]) {
            return false;
        }

        for (auto &v : min_reach) {
            fill(v.begin(), v.end(), INF);
        }

        min_reach[start[0]][start[1]] = wait * s;
        q.push(start);

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                int nt = min_reach[x][y] + 1;
                if (valid(nx, ny, "GHD") && min_reach[nx][ny] == INF && nt / s < min_bee[nx][ny]) {
                    min_reach[nx][ny] = nt;
                    q.push({nx, ny});
                }
            }
        }

        return min_reach[end[0]][end[1]] < INF;
    };

    int ans = -1;
    int l = 0;
    int r = n * n;

    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    cout << ans << '\n';

    return 0;
}

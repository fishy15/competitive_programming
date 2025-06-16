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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

array dx = {2, 1, -1, -2, -2, -1, 1, 2};
array dy = {1, 2, 2, 1, -1, -2, -2, -1};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector grid(n, vector(n, -1));
    queue<pair<int, int>> q;

    q.push({0, 0});
    grid[0][0] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        rep(i, 0, 8) {
            auto nx = x + dx[i];
            auto ny = y + dy[i];
            if (0 <= nx && nx < n && 0 <= ny && ny < n && grid[nx][ny] == -1) {
                grid[nx][ny] = grid[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    rep(i, 0, n) {
        rep(j, 0, n) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}

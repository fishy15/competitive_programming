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

array dx = {0, -1, 0, 1};
array dy = {1, 0, -1, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m;
    cin >> m;

    constexpr int n = 8;

    vector grid(n, vector(m, ' '));
    pair<int, int> s;
    rep(i, 0, n) {
        rep(j, 0, m) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                s = {i, j};
            }
        }
    }

    auto ok = [&](int x, int y) {
        return x >= 0 && x < n && grid[x][y] != 'X'; 
    };

    auto move = [&](int x, int y, int t) {
        if (x % 2 == 0) {
            y = (y - t % m + m) % m;
        } else {
            y = (y + t % m + m) % m;
        }
        return pair{x, y};
    };

    vector dist(n, vector(m, INF));

    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
    dist[s.first][s.second] = 0;
    pq.push({0, s.first, s.second});

    int ans = -1;

    while (!pq.empty()) {
        auto [t, x, y] = pq.top();
        pq.pop();

        if (dist[x][y] != t) continue;

        rep(wt, 0, m) {
            rep(i, 0, 4) {
                auto [cx, cy] = move(x, y, t + wt);
                auto nx = cx + dx[i];
                auto ny = (cy + dy[i] + m) % m;
                auto [nnx, nny] = move(nx, ny, -t - wt);
                if (ok(nnx, nny) && dist[nnx][nny] > t + wt + 1) {
                    if (grid[nnx][nny] == 'D') {
                        ans = t + wt + 1;
                        goto end;
                    }
                    dist[nnx][nny] = t + wt + 1;
                    pq.push({dist[nnx][nny], nnx, nny});
                }
            }
        }
    }

end:
    cout << ans << '\n';

    return 0;
}

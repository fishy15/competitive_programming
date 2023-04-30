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
#include <optional>

using namespace std;

using ll = long long;
using ld = long double;

constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;

constexpr int p_dx[4] = {1, 1, -1, -1};
constexpr int p_dy[4] = {-1, 1, 1, -1};
constexpr int q_dx[4] = {2, 0, -2, 0};
constexpr int q_dy[4] = {0, 2, 0, -2};

struct state {
    ll dist;
    int x, y;

    // inverse of what we want
    bool operator<(const state &other) const {
        return dist > other.dist;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    
    ll p, q;
    cin >> p >> q;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    auto ok = [&](int x, int y) {
        return x >= 0 && y >= 0 && x < n && y < m && grid[x][y] != '#';
    };

    auto move_p = [&](int x, int y, int i) -> optional<pair<int, int>> {
        int nx = x + p_dx[i];
        int ny = y + p_dy[i];
        if (ok(nx, ny) && (ok(nx, y) || ok(x, ny))) {
            return optional(pair{nx, ny});
        } else {
            return {};
        }
    };

    auto move_q = [&](int x, int y, int i) -> optional<pair<int, int>> {
        int nx = x + q_dx[i];
        int ny = y + q_dy[i];
        if (ok(nx, ny) && ok(x + q_dx[i] / 2, y + q_dy[i] / 2)) {
            return optional(pair(nx, ny));
        } else {
            return {};
        }
    };

    vector d(n, vector(m, INFLL));
    priority_queue<state> pq;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                d[i][j] = 0;
                pq.push({d[i][j], i, j});
            }
        }
    }

    while (!pq.empty()) {
        auto [cur_d, x, y] = pq.top();
        pq.pop();

        if (d[x][y] == cur_d) {
            // p moves
            for (int i = 0; i < 4; i++) {
                auto loc = move_p(x, y, i);
                if (loc) {
                    auto [nx, ny] = *loc;
                    if (cur_d + p < d[nx][ny]) {
                        d[nx][ny] = cur_d + p;
                        pq.push({d[nx][ny], nx, ny});
                    }
                }
            }

            // q moves
            for (int i = 0; i < 4; i++) {
                auto loc = move_q(x, y, i);
                if (loc) {
                    auto [nx, ny] = *loc;
                    if (cur_d + q < d[nx][ny]) {
                        d[nx][ny] = cur_d + q;
                        pq.push({d[nx][ny], nx, ny});
                    }
                }
            }
        }
    }

    auto ans = INFLL;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (d[i][j] == INFLL) 
                cout << "-1 ";
            else
                cout << d[i][j] << ' ';
        }
        cout << '\n';
    }

    // horizontal pieces
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            ans = min(ans, d[i][j] + d[i][j + 1]);
        }
    }

    // vertical pieces
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            ans = min(ans, d[i][j] + d[i + 1][j]);
        }
    }

    if (ans == INFLL) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}

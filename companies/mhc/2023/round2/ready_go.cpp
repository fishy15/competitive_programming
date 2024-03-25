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

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(std::forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), std::forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(std::forward<F>(f));
}

array<int, 4> dx = {1, 0, -1, 0};
array<int, 4> dy = {0, 1, 0, -1};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    m = grid[0].size();

    vector vis(n, vector<bool>(m));

    set<pair<int, int>> border;
    int sz = 0;
    auto dfs = y_combinator([&](auto self, int x, int y) -> void {
        vis[x][y] = true;
        sz++;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
                if (grid[nx][ny] == 'W') {
                    if (!vis[nx][ny]) {
                        self(nx, ny);
                    }
                } else if (grid[nx][ny] == '.') {
                    border.insert({nx, ny});
                }
            }
        }
    });

    map<pair<int, int>, int> total;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && grid[i][j] == 'W') {
                border = {};
                sz = 0;
                dfs(i, j);

                if (border.size() == 1) {
                    auto loc = *border.begin();
                    total[loc] += sz;
                }
            }
        }
    }

    int res = 0;
    for (auto [_, x] : total) {
        res = max(res, x);
    }

    /* cout << (res > 0 ? "YES" : "NO") << '\n'; */
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

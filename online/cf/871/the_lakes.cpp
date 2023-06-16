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
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

constexpr array<int, 4> dx = {1, 0, -1, 0};
constexpr array<int, 4> dy = {0, 1, 0, -1};

void solve() {
    int n, m;
    cin >> n >> m;

    vector grid(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vector vis(n, vector<bool>(m));
    
    auto ok = [&](int x, int y) { 
        return x >= 0 && y >= 0 && x < n && y < m && !vis[x][y] && grid[x][y] != 0;
    };

    auto dfs = y_combinator([&](auto self, int x, int y) -> int {
        vis[x][y] = true;

        int cur = grid[x][y];
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (ok(nx, ny)) {
                cur += self(nx, ny);
            }
        }

        return cur;
    });

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ok(i, j)) {
                ans = max(ans, dfs(i, j));
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

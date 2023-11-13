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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    vector vis(n, vector(n, false));

    auto nxt = [&](int x, int y) -> pair<int, int> {
        int nx = (x + 1) % n;
        while (grid[nx][y] != 'P') {
            nx++;
            if (nx >= n) {
                nx = 0;
            }
        }

        int ny = (y - 1 + n) % n;
        while (grid[nx][ny] != 'P') {
            ny--;
            if (ny < 0) {
                ny = n - 1;
            }
        }

        return {nx, ny};
    };

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'P' && !vis[i][j]) {
                vis[i][j] = true;
                int x = i;
                int y = j;
                while (true) {
                    auto [nx, ny] = nxt(x, y);
                    if (vis[nx][ny]) {
                        break;
                    } else {
                        vis[nx][ny] = true;
                        x = nx;
                        y = ny;
                    }
                }
                cnt++;
            }
        }
    }

    ll ans = 1;
    for (int i = 0; i < cnt; i++) {
        ans *= 2;
    }

    cout << ans << '\n';

    return 0;
}

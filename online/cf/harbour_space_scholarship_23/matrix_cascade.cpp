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

void solve() {
    int n;
    cin >> n;

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    vector flip(n, vector<bool>(n));
    vector psum(n, vector<int>(n));

    auto get = [&](int x, int y) {
        if (x >= 0 && y >= 0 && x < n && y < n) {
            return psum[x][y];
        }
        return 0;
    };

    auto get1 = [&](int x, int y) {
        if (x >= 0 && y >= 0 && x < n && y < n && flip[x][y]) {
            return 1;
        }
        return 0;
    };

    auto get_above = [&](int i, int j) {
        if (j == 0) {
            return get(i - 1, j) + get(i - 1, j + 1) - get(i - 2, j + 1) - get1(i - 2, j);
        } else if (j == n - 1) {
            return get(i - 1, j) + get(i - 1, j - 1) - get(i - 2, j - 1) - get1(i - 2, j);
        } else {
            return get(i - 1, j - 1) + get(i - 1, j + 1) - get(i - 2, j) + get1(i - 1, j);
        }
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            auto above_alr = get_above(i, j);
            psum[i][j] = above_alr;
            if ((above_alr % 2) != (grid[i][j] - '0')) {
                flip[i][j] = true;
                psum[i][j]++;
                ans++;
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

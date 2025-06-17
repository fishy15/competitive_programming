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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> grid(n);
    rep(i, 0, n) {
        cin >> grid[i];
    }

    auto ok = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < n;
    };

    auto iter_diag = [&]<typename F>(int s, F f) {
        rep(i, 0, n) {
            int j = s-i;
            if (ok(i, j)) {
                f(i, j);
            }
        }
    };

    vector is_min(n, vector<bool>(n));
    is_min[0][0] = true;
    rep(s, 0, 2*n-2) {
        char min_c = 'Z';
        iter_diag(s, [&](int i, int j) {
            if (is_min[i][j]) {
                if (ok(i+1, j)) {
                    min_c = min(min_c, grid[i+1][j]);
                }
                if (ok(i, j+1)) {
                    min_c = min(min_c, grid[i][j+1]);
                }
            }
        });
        iter_diag(s, [&](int i, int j) {
            if (is_min[i][j]) {
                if (ok(i+1, j) && grid[i+1][j] == min_c) {
                    is_min[i+1][j] = true;
                }
                if (ok(i, j+1) && grid[i][j+1] == min_c) {
                    is_min[i][j+1] = true;
                }
            }
        });
    }

    int cur_x = n-1;
    int cur_y = n-1;
    string s;
    while (cur_x != 0 || cur_y != 0) {
        s += grid[cur_x][cur_y];
        if (ok(cur_x-1, cur_y) && is_min[cur_x-1][cur_y]) {
            cur_x--;
        } else {
            cur_y--;
        }
    }

    s += grid[0][0];
    reverse(all(s));
    cout << s << '\n';

    return 0;
}

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

bool check(const vector<string> &grid) {
    for (auto &row : grid) {
        bool on_light = false;
        for (auto c : row) {
            if (c == '?') {
                if (on_light) {
                    return false;
                } else {
                    on_light = true;
                }
            } else if (c != '.') {
                on_light = false;
            }
        }
    }
    return true;
}

bool lit(const vector<string> &grid) {
    int n = sz(grid);
    vector<vector<bool>> ok(n, vector<bool>(n));
    rep(i, 0, n) {
        rep(j, 0, n) {
            if (grid[i][j] == '?') {
                int cur_x = i;
                int cur_y = j-1;
                while (cur_y >= 0 && grid[cur_x][cur_y] == '.') {
                    ok[cur_x][cur_y] = true;
                    cur_y--;
                }

                cur_x = i;
                cur_y = j+1;
                while (cur_y < n && grid[cur_x][cur_y] == '.') {
                    ok[cur_x][cur_y] = true;
                    cur_y++;
                }

                cur_x = i-1;
                cur_y = j;
                while (cur_x >= 0 && grid[cur_x][cur_y] == '.') {
                    ok[cur_x][cur_y] = true;
                    cur_x--;
                }

                cur_x = i+1;
                cur_y = j;
                while (cur_x < n && grid[cur_x][cur_y] == '.') {
                    ok[cur_x][cur_y] = true;
                    cur_x++;
                }
            }
        }
    }

    rep(i, 0, n) {
        rep(j, 0, n) {
            if (grid[i][j] == '.' && !ok[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool check_count(const vector<string> &grid) {
    int n = sz(grid);
    auto count = [&](int i, int j) {
        int ans = 0;
        if (i > 0) ans += grid[i-1][j] == '?';
        if (i < n-1) ans += grid[i+1][j] == '?';
        if (j > 0) ans += grid[i][j-1] == '?';
        if (j < n-1) ans += grid[i][j+1] == '?';
        return ans;
    };

    rep(i, 0, n) {
        rep(j, 0, n) {
            auto c = grid[i][j];
            if ('0' <= c && c <= '9') {
                int v = c - '0';
                if (v != count(i, j)) {
                    return false;
                }
            }
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> grid(n);
    vector<string> trans(n);
    rep(i, 0, n) {
        cin >> grid[i];
        rep(j, 0, n) {
            trans[j] += grid[i][j];
        }
    }

    if (check(grid) && check(trans) && lit(grid) && check_count(grid)) {
        cout << "1\n";
    } else {
        cout << "0\n";
    }

    return 0;
}

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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int cntr[300][300];
int ccntr[300][300];

void need(const vector<string> &grid, int x, int y, int n) {
    int cnt = 0;
    for (int d = -1; d <= 1; d++) {
        if (x + d - 1 >= 0 && x + d + 1 < n) {
            if (grid[x + d - 1][y] == 'X' && grid[x + d][y] == 'X' && grid[x + d + 1][y] == 'X') {
                cnt++;
            }
        }
        if (y + d - 1 >= 0 && y + d + 1 < n) {
            if (grid[x][y + d - 1] == 'X' && grid[x][y + d] == 'X' && grid[x][y + d + 1] == 'X') {
                cnt++;
            }
        }
    }
    cntr[x][y] = cnt;
}

int del(vector<string> &grid, int x, int y, int n) {
    int chg = 0;
    for (int d = -1; d <= 1; d++) {
        if (x + d - 1 >= 0 && x + d + 1 < n) {
            if (grid[x + d - 1][y] == 'X' && grid[x + d][y] == 'X' && grid[x + d + 1][y] == 'X') {
                for (int dd = -1; dd <= 1; dd++) {
                    ccntr[x + d + dd][y]--;
                    chg++;
                }
            }
        }
        if (y + d - 1 >= 0 && y + d + 1 < n) {
            if (grid[x][y + d - 1] == 'X' && grid[x][y + d] == 'X' && grid[x][y + d + 1] == 'X') {
                for (int dd = -1; dd <= 1; dd++) {
                    ccntr[x][y + d + dd]--;
                    chg++;
                }
            }
        }
    }
    if (chg) grid[x][y] = 'O';
    return chg > 0;
}

pair<int, vector<string>> ans(vector<string> grid, int a, int b, int c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ccntr[i][j] = cntr[i][j];
        }
    }

    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i % 3 == 0 && j % 3 == a) || (i % 3 == 1 && j % 3 == b) || (i % 3 == 2 && j % 3 == c)) {
                tot += del(grid, i, j, n);
            }
        }
    }
    return {tot, grid};
}

void solve() {
    int n; cin >> n;
    vector<string> grid;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        grid.push_back(s);
        for (int j = 0; j < n; j++) cntr[i][j] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'X') need(grid, i, j, n);
        }
    }

    int mans = INF;
    vector<string> gans;
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            for (int c = 0; c < 3; c++) {
                if (a != b && a != c && b != c) {
                    auto res = ans(grid, a, b, c, n);
                    if (res.first < mans) {
                        mans = res.first;
                        gans = res.second;
                    }
                }
            }
        }
    }

    for (string &s : gans) cout << s << '\n';
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

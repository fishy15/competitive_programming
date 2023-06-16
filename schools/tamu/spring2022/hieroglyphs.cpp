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
#include <bitset>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 910

using namespace std;

int r, c;
string grid[MAXN];
int cur[MAXN][MAXN];
string cards = "A234567890JQK";

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int idx(char c) {
    for (int i = 0; i < 13; i++) {
        if (c == cards[i]) return 1 << i;
    }
    return 0;
}

char rev(int x) {
    for (int i = 0; i < 13; i++) {
        if (x & (1 << i)) {
            return cards[i];
        }
    }

    return 33;
}

int rot(int x) {
    int a = (x >> 1) + ((x & 1) << 12);
    int b = ((x - (x & (1 << 12))) << 1) + (x >> 12);
    return a | b;
}

bool ok(int x, int y, int &nxt) {
    if (x >= 0 && y >= 0 && x < r && y < c && grid[x][y] == '?') {
        if ((cur[x][y] & nxt) != cur[x][y]) {
            cur[x][y] &= nxt;
            return true;
        }
    }

    return false;
}

queue<array<int, 2>> q;

void bfs() {
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nxt = rot(cur[x][y]);

            if (ok(nx, ny, nxt)) {
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> r >> c;

    string waste; getline(cin, waste);
    for (int i = 0; i < r; i++) {
        getline(cin, grid[i]);
        grid[i] += string(' ', c - grid[i].size());
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] != ' ') {
                if (grid[i][j] == '?') {
                    cur[i][j] = (1 << 13) - 1;
                } else {
                    cur[i][j] = idx(grid[i][j]);
                    q.push({i, j});
                }
            }
        }
    }

    bfs();

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '?') {
                if (cur[i][j] == 0) {
                    cout << "impossible\n";
                    return 0;
                } else {
                    int msb = cur[i][j] & -cur[i][j];
                    cerr << msb << endl;
                    if (cur[i][j] != msb) {
                        cur[i][j] = msb;
                        q.push({i, j});
                        bfs();
                    }
                }
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '?') {
                cout << rev(cur[i][j]);
            } else {
                cout << grid[i][j];
            }
        }
        cout << '\n';
    }

    return 0;
}

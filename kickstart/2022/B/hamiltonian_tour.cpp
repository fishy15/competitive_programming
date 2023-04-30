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

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

char conv(int dir) {
    return "SWNE"[dir];
}

int f(int dir) {
    return (dir + 1) % 4;
}

int back(int dir) {
    return (dir - 1 + 4) % 4;
}

string test(int r, int c, int sx, int sy, vector<vector<bool>> vis, int ex, int ey) {
    auto ok = [&](int x, int y) {
        return x >= 0 && y >= 0 && x < r && y < c && !vis[x][y];
    };

    string ans = "S";
    int dir = 0;

    int cx = sx + 1;
    int cy = sy;

    /* cout << "end: " << ex << ' ' << ey << '\n'; */
    while (!vis[cx][cy]) {
        vis[cx][cy] = true;

        /* cout << cx << ' ' << cy << '\n'; */
        
        if (ok(cx + dx[f(dir)], cy + dy[f(dir)])) {
            dir = f(dir);
        } else if (ok(cx + dx[dir], cy + dy[dir])) {
            // do nothing
        } else if (ok(cx + dx[back(dir)], cy + dy[back(dir)])) {
            dir = back(dir);
        } else {
            break;
        }

        ans += conv(dir);
        cx += dx[dir];
        cy += dy[dir];
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (!vis[i][j]) {
                return "";
            }
        }
    }

    bool done = false;
    for (int i = 0; i < 4; i++) {
        if (ex == cx + dx[i] && ey == cy + dy[i]) {
            ans += conv(i);
            done = true;
        }
    }

    if (!done) {
        return "";
    }

    return ans;
}

void solve() {
    int r, c; cin >> r >> c;
    vector<string> b(r);

    for (int i = 0; i < r; i++) {
        cin >> b[i];
    }

    r *= 2;
    c *= 2;

    vector<vector<bool>> vis(r, vector<bool>(c));
    int sx = -1;
    int sy = -1;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            vis[i][j] = (b[i / 2][j / 2] == '#');

            if (!vis[i][j] && sx == -1) {
                sx = i;
                sy = j;
            }
        }
    }

    vis[sx][sy] = true;

    int ex = sx;
    int ey = sy + 1;
    string end = "";

    while (ex < r && !vis[ex][ey]) {
        vis[ex][ey] = true;

        auto res = test(r, c, sx, sy, vis, ex, ey);
        if (!res.empty()) {
            cout << res << end << 'W' << '\n';
            return;
        }

        ex++;
        end += 'N';
    }

    cout << "IMPOSSIBLE\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

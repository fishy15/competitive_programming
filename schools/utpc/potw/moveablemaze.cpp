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

constexpr int MAX_SAVE = 5;
int d[20][20][MAX_SAVE + 1][4];
vector<array<int, 4>> adj[20][20][MAX_SAVE + 1][4];
string nrot = "NESW";
string erot = "ESWN";
string srot = "SWNE";
string wrot = "WNES";

string rot(string cur, int rot) {
    string res;
    for (char c : cur) {
        switch (c) {
        case 'N':
            res += nrot[rot];
            break;
        case 'W':
            res += wrot[rot];
            break;
        case 'S':
            res += srot[rot];
            break;
        case 'E':
            res += erot[rot];
            break;
        }
    }

    return res;
}

bool has(string s, char c) {
    return s.find(c) != string::npos;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int r, c;
    cin >> r >> c;

    int sx, sy;
    int dx, dy;
    cin >> sx >> sy;
    cin >> dx >> dy;

    sx--;
    sy--;
    dx--;
    dy--;

    vector<vector<string>> dir(r, vector<string>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> dir[i][j];
        }
    }

    array<int, 4> dr = {0, 0, -1, 1};
    array<int, 4> dc = {-1, 1, 0, 0};
    string cur_dir = "WENS";
    string opp_dir = "EWSN";

    auto ok = [r, c](int x, int y) { return x >= 0 && y >= 0 && x < r && y < c; };

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (int cap = 0; cap <= MAX_SAVE; cap++) {
                for (int dd = 0; dd < 4; dd++) {
                    string cur = rot(dir[i][j], dd);
                    string cur_cw = rot(cur, 1);
                    string cur_ccw = rot(cur, 3);

                    for (int a = 0; a < 4; a++) {
                        int ni = i + dr[a];
                        int nj = j + dc[a];

                        // use our turn on the destination node
                        if (ok(ni, nj)) {
                            if (has(cur, cur_dir[a])) {
                                for (int d2 = 0; d2 < 4; d2++) {
                                    if (has(rot(dir[ni][nj], d2), opp_dir[a])) {
                                        if (d2 == 0) {
                                            adj[i][j][cap][dd].push_back({ni, nj, min(MAX_SAVE, cap + 1), d2});
                                        } else if (d2 == 1 || d2 == 3) {
                                            adj[i][j][cap][dd].push_back({ni, nj, cap, d2});
                                        } else if (d2 == 2 && cap > 0) {
                                            adj[i][j][cap][dd].push_back({ni, nj, cap - 1, d2});
                                        }
                                    }
                                }
                            }
                        }

                        // use our turn on the current node
                        for (auto s : {cur_cw, cur_ccw}) {
                            if (ok(ni, nj)) {
                                if (has(s, cur_dir[a])) {
                                    for (int d2 = 0; d2 < 4; d2++) {
                                        if (has(rot(dir[ni][nj], d2), opp_dir[a])) {
                                            if (d2 == 0) {
                                                adj[i][j][cap][dd].push_back({ni, nj, cap, d2});
                                            } else if ((d2 == 1 || d2 == 3) && cap > 0) {
                                                adj[i][j][cap][dd].push_back({ni, nj, cap - 1, d2});
                                            } else if (d2 == 2 && cap > 1) {
                                                adj[i][j][cap][dd].push_back({ni, nj, cap - 2, d2});
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // move to the sides once
                    adj[i][j][cap][dd].push_back({i, j, cap, (dd + 1) % 4});
                    adj[i][j][cap][dd].push_back({i, j, cap, (dd + 3) % 4});

                    // stay in the same place
                    if (cap < MAX_SAVE) {
                        adj[i][j][cap][dd].push_back({i, j, cap + 1, dd});
                    }
                }
            }
        }
    }

    memset(d, 0x3f, sizeof d);
    queue<array<int, 4>> q;
    q.push({sx, sy, 0, 0});
    d[sx][sy][0][0] = 0;

    while (!q.empty()) {
        auto [i, j, cap, dd] = q.front();
        q.pop();

        for (auto [i2, j2, cap2, dd2] : adj[i][j][cap][dd]) {
            if (d[i2][j2][cap2][dd2] == INF) {
                d[i2][j2][cap2][dd2] = d[i][j][cap][dd] + 1;
                q.push({i2, j2, cap2, dd2});

                if (dx == i2 && dy == j2) {
                    cout << d[i][j][cap][dd] + 1 << '\n';
                    return 0;
                }
            }
        }
    }

    int ans = INF;
    for (int i = 0; i <= MAX_SAVE; i++) {
        for (int j = 0; j < 4; j++) {
            ans = min(ans, d[dx][dy][i][j]);
        }
    }

    cout << ans << '\n';

    return 0;
}

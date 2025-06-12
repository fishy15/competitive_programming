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

struct info {
    ll moves;
    ll area;
    int opt;
};

info better(const info &a, const info &b) {
    if (a.moves == b.moves) {
        return a.area > b.area ? a : b;
    }
    return a.moves > b.moves ? a : b;
}

void solve() {
    int n;
    cin >> n;

    vector grid(n, vector(n, -1));
    grid[n/2][n/2] = 0;

    int x1 = n/2;
    int x2 = n/2;
    int y1 = n/2;
    int y2 = n/2;

    auto moves = [&](int a, int b, int c, int d) {
        return (ll) (a + 1) * (n - b) * (c + 1) * (n - d);
    };

    auto area = [&](int a, int b, int c, int d) {
        return (ll) (b - a + 1) * (d - c + 1);
    };

    int cur = 1;
    while (cur < n * n) {
        info move{0, 0, -1};
        if (x1 > 0) {
            ll containing = moves(x1 - 1, x2, y1, y2);
            ll a = area(x1 - 1, x2, y1, y2);
            move = better(move, {containing, a, 0});
        }
        if (x2 < n-1) {
            ll containing = moves(x1, x2 + 1, y1, y2);
            ll a = area(x1, x2 + 1, y1, y2);
            move = better(move, {containing, a, 1});
        }
        if (y1 > 0) {
            ll containing = moves(x1, x2, y1 - 1, y2);
            ll a = area(x1, x2, y1 - 1, y2);
            move = better(move, {containing, a, 2});
        }
        if (y2 < n-1) {
            ll containing = moves(x1, x2, y1, y2 + 1);
            ll a = area(x1, x2, y1, y2 + 1);
            move = better(move, {containing, a, 3});
        }

        if (move.opt == 0) {
            x1--;
            rep(i, y1, y2+1) {
                if (grid[x1][i] == -1) {
                    grid[x1][i] = cur;
                    cur++;
                }
            }
        } else if (move.opt == 1) {
            x2++;
            rep(i, y1, y2+1) {
                if (grid[x2][i] == -1) {
                    grid[x2][i] = cur;
                    cur++;
                }
            }
        } else if (move.opt == 2) {
            y1--;
            rep(i, x1, x2+1) {
                if (grid[i][y1] == -1) {
                    grid[i][y1] = cur;
                    cur++;
                }
            }
        } else {
            y2++;
            rep(i, x1, x2+1) {
                if (grid[i][y2] == -1) {
                    grid[i][y2] = cur;
                    cur++;
                }
            }
        }
    }

    rep(i, 0, n) {
        rep(j, 0, n) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
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

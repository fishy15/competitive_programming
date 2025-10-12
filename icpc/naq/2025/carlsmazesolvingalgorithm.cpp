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

array dx = {1, 0, -1, 0};
array dy = {0, 1, 0, -1};

struct state {
    int x, y;
    int dir;

    state left() const {
        return {x, y, (dir + 3) % 4};
    }

    state right() const {
        return {x, y, (dir + 1) % 4};
    }

    state move() const {
        return {x + dx[dir], y + dy[dir], dir};
    }

    bool operator<(const state &other) const {
        return tie(x, y, dir) < tie(other.x, other.y, other.dir);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int r, c;
    cin >> r >> c;

    int sx, sy;
    cin >> sx >> sy;
    sx--;
    sy--;

    int ex, ey;
    cin >> ex >> ey;
    ex--;
    ey--;

    vector<string> grid(r);
    rep(i, 0, r) {
        cin >> grid[i];
    }

    state cur = {sx, sy, 0};

    auto ok = [&](state s) {
        return s.x >= 0 && s.y >= 0 && s.x < r && s.y < c && grid[s.x][s.y] == '0';
    };

    set<state> prev;
    while (true) {
        if (cur.x == ex && cur.y == ey) {
            cout << "1\n";
            return 0;
        } else if (prev.count(cur)) {
            cout << "0\n";
            return 0;
        }

        prev.insert(cur);
        if (ok(cur.left().move())) {
            cur = cur.left().move();
        } else if (ok(cur.move())) {
            cur = cur.move();
        } else {
            cur= cur.right();
        }
    }

    return 0;
}

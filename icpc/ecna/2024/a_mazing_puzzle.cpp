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
#include <optional>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int get_dir(char c) {
    return "NESW"s.find(c);
}

struct state {
    int r1, c1;
    int r2, c2;

    bool operator<(const state &st) const {
        return tie(r1, c1, r2, c2) < tie(st.r1, st.c1, st.r2, st.c2);
    }
};

struct dist_t {
    int dist;
    int bump;

    bool operator<(const dist_t &dt) const {
        return tie(dist, bump) < tie(dt.dist, dt.bump);
    }

    bool operator!=(const dist_t &dt) const {
        return *this < dt || dt < *this;
    }
};

struct res {
    int x, y, bump;
};

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int c, r, e;
    cin >> c >> r >> e;
    e--;

    int c1, r1; char d1_c;
    int c2, r2; char d2_c;
    cin >> c1 >> r1 >> d1_c >> c2 >> r2 >> d2_c;
    c1--;
    r1--;
    c2--;
    r2--;

    int d1 = get_dir(d1_c);
    int d2 = get_dir(d2_c);

    vector horz(r, vector<bool>(c));
    vector vert(r, vector<bool>(c));

    int sz;

    cin >> sz;
    for (int i = 0; i < sz; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        horz[y][x] = true;
    }

    cin >> sz;
    for (int i = 0; i < sz; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        vert[y][x] = true;
    }

    vector dist(r + 1, vector(c + 1, vector(r + 1, vector(c + 1, dist_t{INF, INF}))));
    priority_queue<pair<dist_t, state>, vector<pair<dist_t, state>>, greater<>> pq;
    state init{r1, c1, r2, c2};
    pq.push({{0, 0}, init});

    auto d = [&](state s) -> dist_t& {
        return dist[s.r1 + 1][s.c1 + 1][s.r2 + 1][s.c2 + 1];
    };

    d(init) = {0, 0};

    int dird = (d2 - d1 + 4) % 4;

    auto chk = [&horz, &vert](int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        
        if (x1 == x2 && vert[x1][y1]) {
            return false;
        }

        if (y1 == y2 && horz[x1][y1]) {
            return false;
        }

        return true;
    };

    auto move = [r, c, e, &chk](int x, int y, int d) -> res {
        int xp = x;
        int yp = y;

        if (x == -1 && y == -1) {
            return {-1, -1, 0};
        } else {
            x += dx[d];
            y += dy[d];
            if (x >= 0 && y >= 0 && x < r && y < c) {
                if (chk(xp, yp, x, y)) {
                    return {x, y, 0};
                } else {
                    return {xp, yp, 1};
                }
            } else if (x == -1 && y == e) {
                return {-1, -1, 0};
            } else {
                return {xp, yp, 1};
            }
        }
    };

    while (!pq.empty()) {
        auto [cur_d, state] = pq.top();
        auto [r1, c1, r2, c2] = state;
        pq.pop();

        if (d(state) != cur_d) continue;

        if (r1 == -1 && c1 == -1 && r2 == -1 && c2 == -1) {
            cout << cur_d.dist << ' ' << cur_d.bump << '\n';
            return 0;
        }

        for (int d1 = 0; d1 < 4; d1++) {
            int d2 = (d1 + dird) % 4;

            auto mov1 = move(r1, c1, d1);
            auto mov2 = move(r2, c2, d2);

            struct state new_state{mov1.x, mov1.y, mov2.x, mov2.y};
            dist_t new_d{cur_d.dist + 1, cur_d.bump + mov1.bump + mov2.bump};

            if (new_state.r1 == new_state.r2 && new_state.c1 == new_state.c2) {
                if (new_state.r1 != -1) {
                    continue;
                } 
            }

            if (new_d < d(new_state)) {
                d(new_state) = new_d;
                pq.push({new_d, new_state});
            }
        }
    }

    return 0;
}

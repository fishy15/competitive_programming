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
#define MAXN 1000000

using namespace std;

// ans[m][x][y] = min to reach (x', y') s.t. (x, y) = (x' & m, y' & m)
int ans[1 << 8][1 << 8][1 << 8];

int find_unset(int x) {
    for (int i = 0; i < 8; i++) {
        if ((x & (1 << i)) == 0) {
            return i;
        }
    }
    // should not be reached
    return -1;
}

// check if any bits of x are set outside of m
bool all_inside(int x, int m) {
    return x == (x & m);
}

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

void precomp() {
    for (int i = 0; i < (1 << 8); i++) {
        for (int j = 0; j < (1 << 8); j++) {
            for (int k = 0; k < (1 << 8); k++) {
                ans[i][j][k] = INF;
            }
        }
    }

    auto &d = ans[(1 << 8) - 1];
    queue<pair<int, int>> q;

    // represents all possibilities
    int x0 = 0b01010101;
    int y0 = 0b00110011;

    q.push({x0, y0});
    d[x0][y0] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        int m = 0b00001111;
        vector<pair<int, int>> nxt = {
            {x & y, y},
            {x | y, y},
            {x, x ^ y},
            {x, y ^ m},
        };

        for (auto [nx, ny] : nxt) {
            if (d[nx][ny] == INF) {
                d[nx][ny] = d[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    // m = mask of bits we care abt
    // s1, s2 = mask of bits that are set to 1
    for (int m = (1 << 8) - 2; m >= 0; m--) {
        int p = find_unset(m);
        int m_up = m ^ (1 << p);
        for (int x = 0; x < (1 << 8); x++) {
            if (!all_inside(x, m)) continue;
            for (int y = 0; y < (1 << 8); y++) {
                if (!all_inside(y, m)) continue;
                int x_up = x ^ (1 << p);
                int y_up = y ^ (1 << p);
                ckmin(ans[m][x][y], ans[m_up][x][y]);
                ckmin(ans[m][x][y], ans[m_up][x_up][y]);
                ckmin(ans[m][x][y], ans[m_up][x][y_up]);
                ckmin(ans[m][x][y], ans[m_up][x_up][y_up]);
            }
        }
    }
}

void solve() {
    int a, b, c, d, m;
    cin >> a >> b >> c >> d >> m;

    map<tuple<int, int, int>, pair<int, int>> needed;
    for (int i = 0; i < 30; i++) {
        auto init = tuple((a >> i) & 1, (b >> i) & 1, (m >> i) & 1);
        auto want = pair((c >> i) & 1, (d >> i) & 1);

        // if there is some contradiction
        if (needed.count(init) && needed[init] != want) {
            cout << "-1\n";
            return;
        } else {
            needed[init] = want;
        }
    }

    int x0 = 0b01010101;
    int y0 = 0b00110011;
    int mm = 0b00001111;

    int mask = 0;
    int x = 0;
    int y = 0;
    for (int i = 0; i < 8; i++) {
        auto init = tuple((x0 >> i) & 1, (y0 >> i) & 1, (mm >> i) & 1);
        if (needed.count(init)) {
            auto [xp, yp] = needed[init];
            mask ^= 1 << i;
            x ^= xp << i; 
            y ^= yp << i; 
        }
    }

    auto res = ans[mask][x][y];
    if (res == INF) {
        cout << "-1\n";
    } else {
        cout << res << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

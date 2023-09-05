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

struct sum_cnt : public pair<ll, ll> {
    sum_cnt() : sum_cnt(0, 0) {}
    sum_cnt(ll x, ll y) : pair<ll, ll>{x, y} {}
    sum_cnt &operator+=(const sum_cnt &other) {
        first += other.first;
        second += other.second;
        return *this;
    }

    sum_cnt operator+(const sum_cnt &other) const {
        return {first + other.first, second + other.second};
    }

    sum_cnt operator-(const sum_cnt &other) const {
        return {first - other.first, second - other.second};
    }
};

template<typename T>
struct BIT {
    int n, m;
    vector<vector<T>> bit;

    BIT(int n, int m) : n(n), m(m), bit(n + 1, vector<T>(m + 1)) {}

    void upd(int x, int y, T v) {
        x++;
        y++;
        while (x <= n) {
            auto cur_y = y;
            while (cur_y <= m) {
                bit[x][cur_y] += v;
                cur_y += cur_y & -cur_y;
            }
            x += x & -x;
        }
    }

    T qry(int rx, int ry) {
        T res{};
        while (rx > 0) {
            auto cur_ry = ry;
            while (cur_ry > 0) {
                res += bit[rx][cur_ry];
                cur_ry -= cur_ry & -cur_ry;
            }
            rx -= rx & -rx;
        }
        return res;
    }

    T qry(int x1, int y1, int x2, int y2) {
        return qry(x2, y2) - qry(x2, y1) - qry(x1, y2) + qry(x1, y1);
    }
};

constexpr int MAX_C = 100000;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector grid(n, vector<int>(m));
    vector<vector<pair<int, int>>> color_locs(MAX_C);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            grid[i][j]--;
            color_locs[grid[i][j]].push_back({i, j});
        }
    }

    BIT<sum_cnt> ul(n, m), ur(n, m), dl(n, m), dr(n, m);
    ll ans = 0;

    for (int c = 0; c < MAX_C; c++) {
        // set everything
        for (auto [x, y] : color_locs[c]) {
            ul.upd(x, y, {-x - y, 1});
            ur.upd(x, y, {-x + y, 1});
            dl.upd(x, y, {x - y, 1});
            dr.upd(x, y, {x + y, 1});
        }

        for (auto [x, y] : color_locs[c]) {
            auto res_ul = ul.qry(0, 0, x, y);
            auto res_ur = ur.qry(0, y, x, m);
            auto res_dl = dl.qry(x, 0, n, y);
            auto res_dr = dr.qry(x, y, n, m);

            ans += res_ul.first + res_ul.second * (x + y);
            ans += res_ur.first + res_ur.second * (x - y);
            ans += res_dl.first + res_dl.second * (-x + y);
            ans += res_dr.first + res_dr.second * (-x - y);
        }

        // unset everything
        for (auto [x, y] : color_locs[c]) {
            ul.upd(x, y, {x + y, -1});
            ur.upd(x, y, {x - y, -1});
            dl.upd(x, y, {-x + y, -1});
            dr.upd(x, y, {-x - y, -1});
        }
    }

    ans /= 2;
    cout << ans << '\n';

    return 0;
}

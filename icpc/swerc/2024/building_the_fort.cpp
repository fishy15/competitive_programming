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
#include <cassert>

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

constexpr int MAXD = 1e9;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    map<int, set<int>> by_x;
    int min_y = INF;

    rep(i, 0, n) {
        int x, y;
        cin >> x >> y;
        by_x[x].insert(y);
        min_y = min(y, min_y);
    }

    if (sz(by_x) == 1) {
        // everything lies on a single vertical line
        // n >= 3, so there is a distinct min and max y
        auto x = by_x.begin()->first;
        auto &ys = by_x.begin()->second;
        auto max_y = *rbegin(ys);
        if (x == MAXD) {
            by_x[x-1].insert(min_y);
            by_x[x-1].insert(max_y);
        } else {
            by_x[x+1].insert(min_y);
            by_x[x+1].insert(max_y);
        }
    }

    auto l = by_x.begin()->first;
    auto r = by_x.rbegin()->first;
    if (min_y == MAXD) {
        by_x[l].insert(MAXD-1);
        by_x[r].insert(MAXD-1);
        min_y--;
    }
    by_x[l].insert(min_y);
    by_x[r].insert(min_y);
    if (sz(by_x[l]) == 1) {
        by_x[l].insert(min_y+1);
    }
    if (sz(by_x[r]) == 1) {
        by_x[r].insert(min_y+1);
    }

    for (auto it = by_x.begin(); it != by_x.end(); it++) {
        auto &[x, ys] = *it;
        if (x == l) {
            if (!by_x.count(x+1)) {
                by_x[x+1].insert(min_y+1);
            }
        } else if (x == r) {
            if (!by_x.count(x-1)) {
                by_x[x-1].insert(min_y+1);
            }
        } else {
            if (!by_x.count(x-1)) {
                by_x[x-1].insert(min_y+1);
            }
            by_x[x].insert(min_y+1);
        }
    }

    vector<pair<int, int>> ord;
    for (auto &[x, ys] : by_x) {
        if (x == l) {
            // add these in y order
            for (auto y : ys) {
                if (y != min_y) {
                    ord.push_back({x, y});
                }
            }
        } else {
            // add in reverse order
            for (auto it = rbegin(ys); it != rend(ys); it++) {
                if (*it != min_y) {
                    ord.push_back({x, *it});
                }
            }
        }
    }

    for (auto it = rbegin(by_x); it != rend(by_x); it++) {
        if (it->second.count(min_y)) {
            ord.push_back({it->first, min_y});
        }
    }

    assert(sz(ord) <= 3 * n);
    cout << sz(ord) << '\n';
    for (auto [x, y] : ord) {
        cout << x << ' ' << y << '\n';
    }

    return 0;
}

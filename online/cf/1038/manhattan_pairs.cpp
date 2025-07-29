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

struct point {
    int x, y;
    int idx;
    bool top_x, top_y;
};

void solve() {
    int n;
    cin >> n;

    vector<point> pts(n);
    rep(i, 0, n) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].idx = i;
    }

    sort(all(pts), [](const auto &p1, const auto &p2) { return p1.x < p2.x; });
    rep(i, 0, n/2) {
        pts[i].top_x = false;
    }
    rep(i, n/2, n) {
        pts[i].top_x = true;
    }

    sort(all(pts), [](const auto &p1, const auto &p2) { return p1.y < p2.y; });
    rep(i, 0, n/2) {
        pts[i].top_y = false;
    }
    rep(i, n/2, n) {
        pts[i].top_y = true;
    }

    array<vector<int>, 4> grouped;
    for (const auto &p : pts) {
        int pos = 0;
        if (p.top_x) pos ^= 1;
        if (p.top_y) pos ^= 2;
        grouped[pos].push_back(p.idx);
    }

    vector<pair<int, int>> pairs;
    rep(i, 0, sz(grouped[0])) {
        pairs.push_back({grouped[0][i], grouped[3][i]});
    }
    rep(i, 0, sz(grouped[1])) {
        pairs.push_back({grouped[1][i], grouped[2][i]});
    }

    for (auto [x, y] : pairs) {
        cout << x+1 << ' ' << y+1 << '\n';
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

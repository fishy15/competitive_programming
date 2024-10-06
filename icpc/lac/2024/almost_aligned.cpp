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

// times when the max hull changes
// [(k, m)]
ld ller_time(pair<ll, ll> line1, pair<ll, ll> line2) {
    return ((ld) (line2.first - line1.first)) / (line1.second - line2.second);
}

pair<vector<pair<ll, ll>>, vector<ld>> times(vector<pair<ll, ll>> pts) {
    sort(pts.begin(), pts.end(), [](auto p1, auto p2) {
        return pair(p1.second, -p1.first) < pair(p2.second, -p2.first);
    });

    vector<pair<ll, ll>> st;
    for (ll i = 0; i < (ll) pts.size(); i++) {
        if (i > 0 && pts[i].second == pts[i - 1].second) {
            continue;
        }

        while (st.size() >= 2 && ller_time(st.end()[-1], pts[i]) <= ller_time(st.end()[-2], pts[i])) {
            st.pop_back();
        }
        st.push_back(pts[i]);
    }

    vector<ld> times;
    for (ll i = 0; i < (ll) st.size() - 1; i++) {
        times.push_back(ller_time(st[i], st[i + 1]));
    }

    return {st, times};
}

struct meteor {
    ll x, y, vx, vy;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;

    vector<meteor> pts(n);
    vector<pair<ll, ll>> up, down, left, right;
    for (ll i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y >> pts[i].vx >> pts[i].vy;

        up.push_back({pts[i].y, pts[i].vy});
        down.push_back({-pts[i].y, -pts[i].vy});
        left.push_back({-pts[i].x, -pts[i].vx});
        right.push_back({pts[i].x, pts[i].vx});
    }

    auto [upl, upt] = times(up);
    auto [downl, downt] = times(down);
    auto [leftl, leftt] = times(left);
    auto [rightl, rightt] = times(right);

    set<ld> tt = {0};
    for (auto t : upt) tt.insert(t);
    for (auto t : downt) tt.insert(t);
    for (auto t : leftt) tt.insert(t);
    for (auto t : rightt) tt.insert(t);

    auto comp = [&](const vector<pair<ll, ll>> &loc, const vector<ld> &tms, ld t) {
        auto idx = upper_bound(tms.begin(), tms.end(), t) - tms.begin();
        auto [k, m] = loc[idx];
        return k + m * t;
    };

    ld ans = 4e18;
    for (auto t : tt) {
        if (t >= 0) {
            auto y1 = comp(upl, upt, t);
            auto y2 = -comp(downl, downt, t);
            auto x1 = comp(rightl, rightt, t);
            auto x2 = -comp(leftl, leftt, t);

            ans = min(ans, abs(y1 - y2) * abs(x1 - x2));
        }
    }

    cout << fixed << setprecision(15);
    cout << ans << '\n';

    return 0;
}

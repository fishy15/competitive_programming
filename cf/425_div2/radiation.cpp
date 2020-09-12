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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, s;
vector<pair<int, int>> l;
vector<pair<int, int>> r;

struct event {
    ld pos;
    bool left;
    bool rem;
    bool operator<(const event &e2) {
        if (pos == e2.pos) {
            return rem < e2.rem;
        }
        return pos < e2.pos;
    }
};

pair<ld, ld> get_seg(ld pos, ld v, ld t, bool end) {
    if (end) {
        pos = 1e6 - pos;
    }

    pair<ld, ld> ans;
    if (pos / v <= t) {
        ans = {0, 1e6}; 
    } else if (pos / (v + s) > t) {
        return {-1, -1};
    } else {
        ans.first = pos;
        ans.second = pos + (t * (v + s) - pos) / s * (s - v) + eps;
        ans.second = min(ans.second, (ld)1e6);
    }

    if (end) {
        return {ceil(1e6 - ans.second), 1e6 - ans.first};
    }
    return {floor(ans.first), floor(ans.second)};
}

bool check(ld t) {
    vector<event> events;

    for (auto p : l) {
        auto [start, end] = get_seg(p.first, p.second, t, false);
        if (start > -eps) {
            events.push_back({start, true, false});
            events.push_back({end, true, true});
        }
    }

    for (auto p : r) {
        auto [start, end] = get_seg(p.first, p.second, t, true);
        if (start > -eps) {
            events.push_back({start, false, false});
            events.push_back({end, false, true});
        }
    }

    sort(events.begin(), events.end());
    int l_cnt = 0;
    int r_cnt = 0;

    for (auto e : events) {
        if (e.left) {
            if (e.rem) l_cnt--;
            else l_cnt++;
        } else {
            if (e.rem) r_cnt--;
            else r_cnt++;
        }

        if (l_cnt && r_cnt) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        int a, b, c; cin >> a >> b >> c;
        if (c == 1) {
            l.push_back({a, b});
        } else {
            r.push_back({a, b});
        }
    }

    ld l = 0;
    ld r = 1e6;
    ld ans = 1e6;
    for (int i = 0; i < 100; i++) {
        ld m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            r = m;
        } else {
            l = m;
        }
    }

    cout << setprecision(12) << fixed << ans << '\n';

    return 0;
}

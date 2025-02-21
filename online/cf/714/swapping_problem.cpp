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

struct segtree {
    int n;
    vector<ll> st;
    segtree(int _n) : n(_n), st(2 * _n, -INFLL) {}
    void upd(int x, ll y) {
        x += n;
        st[x] = max(st[x], y);
        while (x > 1) {
            st[x >> 1] = max(st[x], st[x ^ 1]);
            x >>= 1;
        }
    }
    ll qry(int l, int r) const {
        ll ans = -INFLL;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = max(st[l++], ans); 
            if (r & 1) ans = max(ans, st[--r]);
        }
        return ans;
    }
};

void flip_x(vector<pair<int, int>> &v) {
    for (auto &p : v) {
        p.first *= -1;
    }
}

void flip_y(vector<pair<int, int>> &v) {
    for (auto &p : v) {
        p.second *= -1;
    }
}

ll solve(vector<pair<int, int>> nums) {
    sort(all(nums));

    vector<int> ys;
    vector<array<int, 3>> events;
    for (auto [x, y] : nums) {
        ys.push_back(x);
        ys.push_back(y);
        events.push_back({x, y, 0});
        events.push_back({y, x, 1});
    }

    sort(all(ys));
    ys.erase(unique(all(ys)), end(ys));
    auto get_y = [&](int y) { return lower_bound(all(ys), y) - begin(ys); };

    segtree st_up(sz(ys));
    segtree st_down(sz(ys));

    sort(all(events), greater{});
    ll gain = 0;
    for (auto [x, y, typ] : events) {
        int ypos = get_y(y);
        if (typ == 0) {
            // query
            ll cost = max({
                st_up.qry(ypos, sz(ys)) + x + y + abs(x - y),
                st_down.qry(0, ypos) + x - y + abs(x - y)
            });
            gain = max(gain, cost);
        } else {
            // update
            st_up.upd(ypos, abs(x - y) - x - y);
            st_down.upd(ypos, abs(x - y) - x + y);
        }
    }

    return gain;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> nums(n);
    rep(i, 0, n) {
        cin >> nums[i].first;
    }
    rep(i, 0, n) {
        cin >> nums[i].second;
    }

    ll cost = 0;
    for (auto [a, b] : nums) {
        cost += abs(a - b);
    }

    ll savings = solve(nums);
    flip_x(nums);
    savings = max(savings, solve(nums));
    flip_y(nums);
    savings = max(savings, solve(nums));
    flip_x(nums);
    savings = max(savings, solve(nums));

    cout << cost - savings << '\n';

    return 0;
}

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

short collapse(short x, bool a, bool b) {
    short ans = x << 2;
    if (a) ans |= 2;
    if (b) ans |= 1;
    return ans;
}

tuple<short, bool, bool> extract(short res) {
    short x = res >> 2;
    bool a = (res & 2) > 0;
    bool b = (res & 1) > 0;
    return {x, a, b};
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<ll> f(n), d(n);
    rep(i, 0, n) {
        cin >> f[i];
    }
    rep(i, 0, n) {
        cin >> d[i];
    }

    // {location, index, added}
    vector<array<short, 2>> state(n);
    vector<vector<short>> events(4 * k + 1);
    int ans = n;

    // count of zero, one cost
    int in_interval = 0;
    int cost = 0;

    auto single_update = [&](int idx, bool current, bool add) {
        int delta = add ? 1 : -1;
        if (current) {
            state[idx][0] += delta;
        } else {
            state[idx][1] += delta;
        }
    };

    auto update = [&](int idx, int delta) {
        if (state[idx][0] > 0) {
            in_interval += delta;
        } else if (state[idx][1] > 0) {
            in_interval += delta;
            cost += delta;
        }
    };

    auto process_events = [&] {
        rep(i, 0, sz(events)) {
            for (auto res : events[i]) {
                auto [idx, current, add] = extract(res);
                update(idx, -1);
                single_update(idx, current, add);
                update(idx, 1);
            }

            if (in_interval == n) {
                ans = min(ans, cost);
            }
        }
    };

    rep(i, 0, n) {
        for (auto &v : events) v.clear();
        for (auto &v : state) v.fill(0);
        in_interval = 0;
        cost = 0;

        auto goal = f[i] * d[i];

        auto add_to_array = [&](ll x, short res) {
            auto off = x - goal + 2*k;
            if (off < 0) {
                auto [idx, current, add] = extract(res);
                update(idx, -1);
                single_update(idx, current, add);
                update(idx, +1);
            } else if (off < sz(events)) {
                events[off].push_back(res);
            }
        };

        auto add_event = [&](ll x, int idx) {
            auto current = f[idx] * d[idx];
            add_to_array(x - k, collapse(idx, x == current, true));
            add_to_array(x + 1, collapse(idx, x == current, false));
        };

        add_event(goal, i);

        rep(j, 0, n) {
            if (i != j) {
                auto current = f[j] * d[j];
                auto op1 = goal / f[j] * f[j];
                auto op2 = op1 + f[j];
                if (op1 != 0) {
                    add_event(op1, j);
                }
                add_event(op2, j);
                add_event(current, j);
            }
        }

        process_events();
    }

    cout << ans << '\n';
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

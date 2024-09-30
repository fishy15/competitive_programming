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

pair<int, int> comb(pair<int, int> a, pair<int, int> b) {
    return pair{max(a.first, b.first), max(a.second, b.second)};
}

struct segtree {
    int n;
    vector<pair<int, int>> st;

    segtree(int n) : n(n), st(2 * n) {}

    void upd(int x, int y) { 
        auto even = x % 2 == 0;
        x += n;
        st[x] = even ? pair{y, 0} : pair{0, y};
        while (x > 1) {
            st[x >> 1] = comb(st[x], st[x ^ 1]);
            x >>= 1;
        }
    }

    pair<int, int> qry(int l, int r) const {
        pair<int, int> ans = {0, 0};
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                ans = comb(ans, st[l]);
                l++;
            }

            if (r & 1) {
                r--;
                ans = comb(ans, st[r]);
            }

            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    segtree st(n);
    rep(i, 0, n) {
        st.upd(i, a[i]);
    }

    set<pair<int, int>> intervals;
    vector<bool> vis(n);
    vector<ll> benefit_fixed(n); // benefit if stay with the fixed alternating pattern
    vector<ll> benefit_off(n); // benefit if you can pick off fixed pattern
    multiset<ll, greater<ll>> benefit_max; // multiset of all benefits above
    int other_sum = 0;

    auto remove_interval = [&](int x, int y) {
        intervals.erase({x, y});
        benefit_max.erase(benefit_max.find(benefit_off[x]));
        benefit_max.erase(benefit_max.find(benefit_fixed[x]));

        auto len = y - x + 1;
        other_sum -= (len + 1) / 2;
    };
    auto remove_interval_p = [&](pair<int, int> p) {
        remove_interval(p.first, p.second);
    };

    auto add_interval = [&](int x, int y) {
        auto it = intervals.insert({x, y});
        auto len = y - x + 1;
        auto alt = (len + 1) / 2;

        // bests.first = best value if we stay on fixed pattern
        // bests.second = best value if we stay off of it
        auto bests = st.qry(x, y+1);
        if (x % 2 == 1) {
            swap(bests.first, bests.second);
        }
        benefit_fixed[x] = bests.first + (len + 1) / 2 - alt;
        benefit_off[x] = bests.second + len / 2 - alt;

        benefit_max.insert(benefit_fixed[x]);
        benefit_max.insert(benefit_off[x]);
        other_sum += alt;

        return it.first;
    };

    auto add_singleton = [&](int x) {
        vis[x] = true;
        auto it = add_interval(x, x);
        if (x > 0 && vis[x - 1]) {
            auto cur_int = *it;
            auto prev_int = *prev(it);

            remove_interval_p(cur_int);
            remove_interval_p(prev_int);
            it = add_interval(prev_int.first, cur_int.second);
        }

        if (x < n - 1 && vis[x + 1]) {
            auto cur_int = *it;
            auto nxt_int = *next(it);

            remove_interval_p(cur_int);
            remove_interval_p(nxt_int);
            it = add_interval(cur_int.first, nxt_int.second);
        }
    };

    vector<pair<int, int>> events;
    rep(i, 0, n) {
        events.push_back({a[i], i});
    }
    sort(all(events), greater{});

    ll ans = 0;
    for (auto [cur_min, x] : events) {
        add_singleton(x);
        auto cur = other_sum + *benefit_max.begin() + cur_min;
        ans = max(ans, cur);
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

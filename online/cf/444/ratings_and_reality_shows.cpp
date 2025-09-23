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

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j,0,sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a <= b); // or return inf if a == b
        if (a == b) return INFLL;
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, a, b, c, d, start, len;
    cin >> n >> a >> b >> c >> d >> start >> len;

    vector<pair<int, bool>> events(n);
    vector<int> ts = {0};
    rep(i, 0, n) {
        int y;
        cin >> events[i].first >> y;
        events[i].second = (y == 0);
        ts.push_back(events[i].first);
    }

    sort(all(ts));
    ts.erase(unique(all(ts)), end(ts));

    auto get_t = [&](int t) {
        auto it = lower_bound(all(ts), t);
        return it - begin(ts);
    };

    auto comp_rating_at = [&](int up, int down) {
        vector<ll> rating_at(sz(ts) + 1);
        rating_at[0] = start;
        int last_t = 0;
        for (auto [t, is_down] : events) {
            auto t_idx = get_t(t);
            if (t_idx != last_t) {
                rating_at[t_idx] = rating_at[t_idx-1];
            }

            if (is_down) {
                rating_at[t_idx] -= down;
            } else {
                rating_at[t_idx] += up;
            }
        }

        return rating_at;
    };

    auto rating_at_ab = comp_rating_at(a, b);
    auto rating_at_cd = comp_rating_at(c, d);
    auto ab_rmq = RMQ(rating_at_ab);
    auto cd_rmq = RMQ(rating_at_cd);
    auto max_t = *max_element(all(ts));

    auto check = [&](int t) {
        if (t > max_t) {
            return ab_rmq.query(0, n+1) >= 0;
        }

        // check that until time t, positive 
        auto t_idx = get_t(t);
        auto before_min = ab_rmq.query(0, t_idx);

        if (before_min < 0) {
            return false;
        }

        auto ab_start = t_idx == 0 ? start : rating_at_ab[t_idx - 1];
        auto cd_start = t_idx == 0 ? start : rating_at_cd[t_idx - 1];
        auto end_idx = get_t(t + len);
        auto show_min = cd_rmq.query(t_idx, end_idx) + (ab_start - cd_start);
        return show_min >= 0;
    };

    vector<int> to_try;
    to_try.push_back(0);
    for (auto t : ts) {
        to_try.push_back(t + 1);
        if (t - len + 1 >= 0) {
            to_try.push_back(t - len + 1);
        }
    }

    sort(all(to_try));
    to_try.erase(unique(all(to_try)), end(to_try));
    for (auto t : to_try) {
        if (check(t)) {
            cout << t << '\n';
            return 0;
        }
    }

    if (*min_element(all(rating_at_ab)) >= 0) {
        // already works, so just do show at the end
        auto ans = *max_element(all(ts)) + 1;
        cout << ans << '\n';
        return 0;
    }


    cout << "-1\n";

    return 0;
}

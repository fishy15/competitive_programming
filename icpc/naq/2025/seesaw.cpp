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

struct info {
    ll tot_weight;
    ll tot_objs; 
    ll cur_pos;

    bool operator<(const info &other) const {
        auto w1 = -tot_weight * other.tot_objs;
        auto w2 = -other.tot_weight * tot_objs;
        return tie(w1, cur_pos) < tie(w2, other.cur_pos);
    }
};

struct info_pos {
    ll tot_weight;
    ll tot_objs; 
    ll cur_pos;

    info_pos(info i) : tot_weight(i.tot_weight), tot_objs(i.tot_objs), cur_pos(i.cur_pos) {}

    bool operator<(const info_pos &other) const {
        return cur_pos < other.cur_pos;
    }
};

info from(info_pos i) {
    return info {
        i.tot_weight,
        i.tot_objs,
        i.cur_pos,
    };
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<ll, ll>> objs(n);
    ll torque = 0;
    for (auto &[a, b] : objs) {
        cin >> a >> b;
        torque += a * b;
    }

    if (torque > 0) {
        reverse(all(objs));
        for (auto &[a, b] : objs) {
            a *= -1;
        }
    }

    ld torque_left = abs(torque);

    // now, all operations should be moving objects to the right
    set<info> weight_ord;
    set<info_pos> pos_ord;
    rep(i, 0, n) {
        info cur{objs[i].second, 1, objs[i].first};
        weight_ord.insert(cur);
        pos_ord.insert(cur);
    }

    ld ans = 0;
    while (torque_left > eps) {
        auto cur_info = *begin(weight_ord);
        auto nxt_it = pos_ord.upper_bound(info_pos(cur_info));
        auto wanted = torque_left / cur_info.tot_weight;
        if (nxt_it == end(pos_ord)) {
            ans += wanted * cur_info.tot_objs;
            torque_left = 0;
        } else {
            auto nxt = *nxt_it;
            ld dist_left = nxt.cur_pos - cur_info.cur_pos;
            if (wanted < dist_left) {
                ans += wanted * cur_info.tot_objs;
                torque_left = 0;
            } else {
                torque_left -= dist_left * cur_info.tot_weight;
                ans += dist_left * cur_info.tot_objs;

                weight_ord.erase(cur_info);
                weight_ord.erase(from(nxt));
                pos_ord.erase(cur_info);
                pos_ord.erase(nxt);

                info comb = {
                    cur_info.tot_weight + nxt.tot_weight,
                    cur_info.tot_objs + nxt.tot_objs,
                    nxt.cur_pos,
                };
                weight_ord.insert(comb);
                pos_ord.insert(comb);
            }
        }
    }

    cout << fixed << setprecision(15);
    cout << ans << '\n';

    return 0;
}

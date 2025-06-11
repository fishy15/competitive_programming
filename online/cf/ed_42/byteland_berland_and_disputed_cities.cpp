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

constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<ll, char>> locs(n);
    vector<ll> bs, ps, rs;
    rep(i, 0, n) {
        cin >> locs[i].first >> locs[i].second;
        switch (locs[i].second) {
            case 'B': bs.push_back(locs[i].first); break;
            case 'R': rs.push_back(locs[i].first); break;
            case 'P': ps.push_back(locs[i].first); break;
        }
    }

    ll cost = 0;
    if (ps.empty()) {
        if (!bs.empty()) {
            cost += bs.back() - bs[0];
        }
        if (!rs.empty()) {
            cost += rs.back() - rs[0];
        }
    } else {
        ll first_p = ps[0];
        ll last_p = ps.back();
        if (!bs.empty() && bs[0] < first_p) {
            cost += first_p - bs[0];
        }
        if (!rs.empty() && rs[0] < first_p) {
            cost += first_p - rs[0];
        }

        if (!bs.empty() && bs.back() > last_p) {
            cost += bs.back() - last_p;
        }
        if (!rs.empty() && rs.back() > last_p) {
            cost += rs.back() - last_p;
        }

        rep(i, 0, sz(ps) - 1) {
            auto p1 = ps[i];
            auto p2 = ps[i+1];
            auto b_start = lower_bound(all(bs), p1);
            auto b_end = lower_bound(all(bs), p2);
            auto r_start = lower_bound(all(rs), p1);
            auto r_end = lower_bound(all(rs), p2);

            // case 1: we connect through b and r independently
            ll cost1 = 2 * (p2 - p1);

            // case 2: we connect p1 to p2, and connect all bs and all rs and to the best one
            ll cost2 = p2 - p1;
            if (b_start != b_end) {
                ll biggest_gap = max(*b_start - p1, p2 - *prev(b_end));
                for (auto it = b_start; next(it) != b_end; it++) {
                    ckmax(biggest_gap, *next(it) - *it);
                }
                cost2 += (p2 - p1) - biggest_gap;
            }
            if (r_start != r_end) {
                ll biggest_gap = max(*r_start - p1, p2 - *prev(r_end));
                for (auto it = r_start; next(it) != r_end; it++) {
                    ckmax(biggest_gap, *next(it) - *it);
                }
                cost2 += (p2 - p1) - biggest_gap;
            }

            cost += min(cost1, cost2);
        }
    }

    cout << cost << '\n';

    return 0;
}


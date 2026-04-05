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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<pair<ll, ll>> ranges(n);
    rep(i, 0, n) {
        cin >> ranges[i].first >> ranges[i].second;
    }

    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<>> pq;
    rep(i, 0, q) {
        ll x;
        cin >> x;
        pq.push({x, i});
    }

    vector<ll> ans(q);

    vector<array<ll, 2>> ops;
    for (auto [a, b] : ranges) {
        ops.push_back({a, 1});
        ops.push_back({b+1, -1});
    }

    sort(all(ops));

    ll tot_before = 0;
    ll cur = 0;
    ll last_x = -1;
    for (auto [x, t] : ops) {
        if (cur > 0) {
            if (last_x != x) {
                while (!pq.empty()) {
                    auto [qpos, qi] = pq.top();
                    auto at_rate = (qpos - tot_before + cur - 1) / cur;
                    auto achieved_at = last_x + at_rate - 1;
                    if (achieved_at < x) {
                        ans[qi] = achieved_at;
                        pq.pop();
                    } else {
                        break;
                    }
                }
            }

            // update counts
            tot_before += (ll) (x - last_x) * cur;
        }

        cur += t;
        last_x = x;
    }

    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}

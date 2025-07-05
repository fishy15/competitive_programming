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

constexpr ll MAX = 1'000'000'000'000'000'000;

vector<ll> zebra;
vector<ll> zebra_psum;

void precomp() {
    ll cur = 1;
    while (cur <= MAX) {
        zebra.push_back(cur);
        cur = 4 * cur + 1;
    }

    zebra_psum.push_back(zebra[0]);
    rep(i, 1, sz(zebra)) {
        zebra_psum.push_back(zebra_psum.back() + zebra[i]);
    }
}

map<pair<ll, int>, ll> full_cache;

ll solve(ll r, ll k, int cur_idx) {
    if (k > 5 * cur_idx) {
        return 0;
    }

    if (cur_idx == 0) {
        return k == 0 ? 1 : 0;
    } else if (cur_idx == 1) {
        return (k <= r && k <= 4) ? 1 : 0;
    }

    auto cur = zebra[cur_idx - 1];

    int max_limit = 4;
    int fit_limit = 0;
    while (fit_limit < max_limit && fit_limit * cur <= r) {
        fit_limit++;
    }

    bool can_cache = (4 * zebra_psum[cur_idx - 1] <= r);
    if (can_cache && full_cache.count({k, cur_idx})) {
        return full_cache[{k, cur_idx}];
    }
 
    ll ans = 0;
    rep(i, 0, fit_limit) {
        if (k - i >= 0) {
            ans += solve(r - i * cur, k - i, cur_idx - 1);
        }
    }

    if (k == max_limit && r - max_limit * cur >= 0) {
        ans++;
    }

    if (can_cache) {
        full_cache[{k, cur_idx}] = ans;
    }

    return ans;
}

void solve() {
    ll l, r, k;
    cin >> l >> r >> k;
    cout << solve(r, k, sz(zebra)) - solve(l - 1, k, sz(zebra)) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

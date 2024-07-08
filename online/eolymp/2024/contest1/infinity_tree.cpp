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

constexpr int L = 50;

ll bits_until(ll end) {
    end++; // make exclusive
    ll ans = 0;
    for (int i = 0; i < L; i++) {
        ll grp = 1LL << (i + 1);
        ll full_grps = end / grp;
        ans += full_grps * grp / 2; // half of each group filled
        ll remain = end - full_grps * grp;
        ans += max(0LL, remain - grp / 2); // delete first half
    }
    return ans;
}

vector<ll> group_ends;

void precomp(ll n) {
    ll prev = 0;
    ll cur = 1;

    group_ends = {0};
    while (cur <= n) {
        group_ends.push_back(cur);
        auto cnt = bits_until(cur) - bits_until(prev);
        prev = cur;
        cur += cnt;
    }
}

vector<ll> get_pars(ll x) {
    int idx = lower_bound(all(group_ends), x) - group_ends.begin();
    vector<ll> res = {x};
    while (idx >= 2) {
        auto l = group_ends[idx - 2] + 1;
        auto r = group_ends[idx - 1];
        auto before = l-1;
        auto end = r;
        ll ans = -1;
        while (l <= r) {
            ll m = (l + r) / 2;
            auto mov = end + (bits_until(m) - bits_until(before));
            if (mov >= x) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        idx--;
        x = ans;
        res.push_back(x);
    }

    return res;
}

void solve() {
    ll u, v;
    cin >> u >> v;

    auto res1 = get_pars(u);
    auto res2 = get_pars(v);

    while (sz(res1) && sz(res2) && res1.back() == res2.back()) {
        res1.pop_back();
        res2.pop_back();
    }

    cout << sz(res1) + sz(res2) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);


    ll n;
    int q;
    cin >> n >> q;

    precomp(n);

    while (q--) {
        solve();
    }

    return 0;
}

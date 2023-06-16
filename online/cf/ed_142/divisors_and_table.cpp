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
#include <unordered_set>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

set<int> pf(ll x) {
    set<int> res;

    auto process = [&](int p) {
        if (x % p == 0) {
            res.insert(p);
            while (x % p == 0) {
                x /= p;
            }
        }
    };

    process(2);

    for (ll i = 3; i * i <= x; i += 2) {
        process(i);
    }

    if (x != 1) {
        process(x);
    }

    return res;
}

vector<int> ff(ll x) {
    vector<int> res;
    for (ll i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            res.push_back(i);
            if (i * i != x) {
                res.push_back(x / i);
            }
        }
    }
    return res;
}

vector<int> merge(set<int> &a, set<int> &b) {
    vector<int> res;
    for (auto x : a) res.push_back(x);
    for (auto x : b) {
        if (!a.count(x)) {
            res.push_back(x);
        }
    }
    return res;
}

unordered_set<ll> gen_mul(const vector<int> &a, const vector<int> &b) {
    unordered_set<ll> res;
    for (auto x : a) {
        for (auto y : b) {
            res.insert((ll) x * y);
        }
    }
    return res;
}

void solve() {
    int n, m1, m2;
    cin >> n >> m1 >> m2;

    auto p1 = pf(m1);
    auto p2 = pf(m2);
    auto ps = merge(p1, p2);
    auto tot = gen_mul(ff(m1), ff(m2));
    auto tot_v = vector<ll>(tot.begin(), tot.end());
    sort(tot_v.begin(), tot_v.end());

    auto g = [&](ll x) { return lower_bound(tot_v.begin(), tot_v.end(), x) - tot_v.begin(); };
    auto p = [&](ll x) {
        auto it = lower_bound(tot_v.begin(), tot_v.end(), x);
        return it != tot_v.end() && *it == x;
    };

    vector<pair<ll, ll>> ans(tot_v.size());

    auto try_set = [&](ll val, ll factor1, ll factor2) {
        if (factor1 <= n && factor2 <= n) {
            int idx = g(val);
            if (ans[idx].first == 0) {
                ans[idx] = {factor1, factor2};
            } else {
                ans[idx] = min(ans[idx], {factor1, factor2});
            }
        }
    };

    ans[g(1)] = {1, 1};

    for (int i = 0; i < (int) tot_v.size(); i++) {
        if (ans[i].first == 0) continue;
        auto [f1, f2] = ans[i];

        ll t = tot_v[i];
        for (auto pu : ps) {
            if (p(t * pu)) {
                try_set(t * pu, f1 * pu, f2);
                try_set(t * pu, f1, f2 * pu);
            }
        }
    }

    ll ans_xor = 0;
    ll cnt = 0;
    for (auto [f, _] : ans) {
        ans_xor ^= f;
        if (f != 0) cnt++;
    }

    cout << cnt << ' ' << ans_xor << '\n';
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

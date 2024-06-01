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

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n, b, x;
    cin >> n >> b >> x;

    vector<int> cnt(n);
    for (auto &x : cnt) {
        cin >> x;
    }

    ll l = 1;
    ll r = accumulate(cnt.begin(), cnt.end(), 0LL);

    auto f = [&](ll groups) {
        ll benefit = 0;
        for (auto c : cnt) {
            ll base = c / groups;
            auto extra = c % groups;
            auto non_extra = groups - extra;

            benefit += extra * (base + 1) * (c - base - 1) * b;
            benefit += non_extra * base * (c - base) * b;
        }

        benefit /= 2;
        benefit -= (ll) x * (groups - 1);
        
        return benefit;
    };

    ll ans = 0;
    while (l <= r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        auto v1 = f(m1);
        auto v2 = f(m2);
        ans = max({ans, v1, v2});
        if (v1 < v2) {
            l = m1+1;
        } else {
            r = m2-1;
        }
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

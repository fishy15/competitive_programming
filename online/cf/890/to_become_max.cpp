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
    int n;
    ll k;
    cin >> n >> k;

    vector<ll> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    auto solve = [&nums, n, k](int x) {
        ll l = nums[x];
        ll r = l + k;

        auto check = [&nums, n, k, x](ll v) {
            ll req = 0;
            for (int i = x; i < n; i++) {
                if (v <= nums[i]) {
                    return req <= k;
                } else {
                    req += (v - nums[i]);
                    v--;
                }
            }

            return false;
        };

        ll ans = -1;
        while (l <= r) {
            ll m = l + (r - l) / 2;
            if (check(m)) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        return ans;
    };

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, solve(i));
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

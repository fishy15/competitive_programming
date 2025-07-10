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

ll ceil_div(ll a, ll b) {
    return (a + b - 1) / b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<ll> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    sort(all(nums));

    vector<ll> flat_suff_min(n+1, INFLL);
    for (int i = n-1; i >= 0; i--) {
        flat_suff_min[i] = min(flat_suff_min[i+1], nums[i]);
    }

    vector<ll> sloped_pref_min(n+1, INFLL);
    rep(i, 0, n) {
        sloped_pref_min[i+1] = min(sloped_pref_min[i], nums[i] - i);
    }

    auto ans_small = [&](int x) {
        return min(sloped_pref_min[x] + x, flat_suff_min[x]);
    };

    auto nums_match = nums;
    rep(i, 0, n) {
        nums_match[i] += n - i;
    }

    auto match_min = *min_element(all(nums_match));
    auto match_extra = accumulate(all(nums_match), 0LL) - n * match_min;

    auto ans_match = [&](ll x) {
        auto to_sub = (x - n) / 2;
        auto ans = match_min + (x - n);
        if (to_sub > match_extra) {
            ans -= ceil_div(to_sub - match_extra, n);
        }
        return ans;
    };

    auto nums_nomatch = nums;
    rep(i, 0, n-1) {
        nums_nomatch[i] += n - i - 1;
    }

    ll above_last = 0;
    rep(i, 0, n) {
        above_last += max(0LL, nums_nomatch[i] - nums_nomatch.back());
    }

    ll min_before = INFLL;
    ll extra_before = 0;
    if (n > 1) {
        min_before = *min_element(begin(nums_nomatch), end(nums_nomatch) - 1);
        extra_before = accumulate(begin(nums_nomatch), end(nums_nomatch) - 1, 0LL) - (n - 1) * min_before;
    }

    auto ans_nomatch = [&](ll x) {
        auto to_sub = (x - n + 1) / 2;
        if (n == 1) {
            return nums_nomatch.back() - to_sub;
        }

        auto cur_min = min_before + (x - n + 1);
        auto last = nums_nomatch.back();

        if (to_sub <= extra_before) {
            return min(cur_min, last);
        } else {
            to_sub -= extra_before;
        }

        // now we have n-1 things at cur_min, and 1 thing at the last value
        ll in_between;
        if (cur_min > last) {
            in_between = (cur_min - last) * (n - 1);
        } else {
            in_between = last - cur_min;
        }

        if (to_sub <= in_between) {
            return min(cur_min, last);
        } else {
            cur_min = min(cur_min, last);
            to_sub -= in_between;
        }

        // now n things at last value
        cur_min -= ceil_div(to_sub, n);
        return cur_min;
    };

    while (q--) {
        int k;
        cin >> k;

        if (k <= n) {
            cout << ans_small(k) << ' ';
        } else if (n % 2 == k % 2) {
            cout << ans_match(k) << ' ';
        } else {
            cout << ans_nomatch(k) << ' ';
        }
    }
    cout << '\n';

    return 0;
}

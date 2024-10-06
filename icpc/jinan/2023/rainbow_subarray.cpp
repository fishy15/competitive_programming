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

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        nums[i] -= i;
    }

    // now want to make everything "flat"
    int r = 0;
    int ans = 1;

    multiset<int> lower, upper;
    ll lo_sum = 0;
    ll hi_sum = 0;

    auto normalize = [&] {
        int tot = lower.size() + upper.size();
        while ((int) lower.size() < tot / 2) {
            auto it = upper.begin();
            lo_sum += *it;
            hi_sum -= *it;
            lower.insert(*it);
            upper.erase(it);
        }

        while ((int) upper.size() < (tot + 1) / 2) {
            auto it = prev(lower.end());
            hi_sum += *it;
            lo_sum -= *it;
            upper.insert(*it);
            lower.erase(it);
        }

        if (!lower.empty()) {
            while (*prev(lower.end()) > *upper.begin()) {
                auto it_lo = prev(lower.end());
                auto it_hi = upper.begin();
                lo_sum += *it_hi - *it_lo;
                hi_sum += *it_lo - *it_hi;
                upper.insert(*it_lo);
                lower.insert(*it_hi);
                lower.erase(it_lo);
                upper.erase(it_hi);
            }
        }
    };


    auto check = [&] {
        if (lower.size() + upper.size() <= 1) {
            return true;
        }

        auto median = *upper.begin();
        auto from_lo = (ll) lower.size() * median - lo_sum;
        auto from_hi = hi_sum - (ll) upper.size() * median;
        return from_lo + from_hi <= k;
    };

    auto add = [&](int v) {
        upper.insert(v);
        hi_sum += v;
        normalize();
    };

    auto remove = [&](int v) {
        auto it = lower.find(v);
        if (it != lower.end()) {
            lower.erase(it);
            lo_sum -= v;
        } else {
            upper.erase(upper.find(v));
            hi_sum -= v;
        }
        normalize();
    };

    for (int l = 0; l < n; l++) {
        while (r < n) {
            add(nums[r]);
            if (!check()) {
                remove(nums[r]);
                break;
            }
            r++;
        }

        ans = max(ans, r - l);
        remove(nums[l]);
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

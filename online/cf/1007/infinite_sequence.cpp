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

int get_next(const vector<int> &nums) {
    int n = sz(nums);
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (2 * i <= n) {
            res ^= nums[i];
        }
    }
    return res;
}

int brute(vector<int> nums, int x) {
    while (sz(nums) <= x) {
        nums.push_back(get_next(nums));
    }
    return nums[x];
}

void solve() {
    int n;
    ll l, r;
    cin >> n >> l >> r;

    vector<int> nums(n+1);
    rep(i, 0, n) {
        cin >> nums[i+1];
    }

    if (n % 2 == 0) {
        nums.push_back(get_next(nums));
        n++;
    }

    // make n the size of the array
    n++;

    auto initial = accumulate(all(nums), 0, bit_xor{});
    auto comp = [&](auto &&self, ll x) {
        if (x < n) {
            return nums[x];
        } else {
            auto last_idx = x / 2;
            if (last_idx < n) {
                return accumulate(begin(nums), begin(nums) + last_idx + 1, 0, bit_xor{});
            } else if (last_idx % 2 == 1) {
                return initial;
            } else {
                return initial ^ self(self, last_idx);
            }
        }
    };

    auto ans = comp(comp, l);
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

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

void solve() {
    int n;
    cin >> n;

    vector<ll> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    sort(all(nums));
    auto ans = -1LL;
    rep(i, 0, n - 2) {
        if (nums[i] + nums[i+1] > nums[i+2]) {
            auto s = (nums[i] + nums[i+1] + nums[i+2]) / 2;
            auto area_sq = s * (s - nums[i]) * (s - nums[i+1]) * (s - nums[i+2]);
            ans = max(ans, area_sq);
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

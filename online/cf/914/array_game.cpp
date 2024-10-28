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
    int n, k;
    cin >> n >> k;

    vector<ll> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    sort(nums.begin(), nums.end());

    if (k >= 3) {
        cout << "0\n";
        return;
    }

    ll ans = nums[0];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = min(ans, abs(nums[i] - nums[j]));
        }
    }

    if (k == 2) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                auto d = abs(nums[i] - nums[j]);
                auto it = lower_bound(nums.begin(), nums.end(), d);
                if (it != nums.begin()) {
                    ans = min(ans, abs(d - *prev(it)));
                }
                if (it != nums.end()) {
                    ans = min(ans, abs(d - *it));
                }
            }
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

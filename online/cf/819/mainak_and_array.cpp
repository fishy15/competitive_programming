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
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    if (n == 1) {
        cout << "0\n";
        return;
    }

    // adjacent to each other
    int ans = -INF;
    for (int i = 0; i < n; i++) {
        int nxt = i == n - 1 ? 0 : i + 1;
        ans = max(ans, nums[i] - nums[nxt]);
    }

    // only move max or min
    ans = max(ans, *max_element(nums.begin() + 1, nums.end()) - nums[0]);
    ans = max(ans, nums[n - 1] - *min_element(nums.begin(), nums.end() - 1));

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

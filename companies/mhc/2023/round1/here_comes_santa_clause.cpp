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

void pr_half(ll x) {
    if (x % 2 == 0) {
        cout << x / 2 << '\n';
    } else {
        cout << x / 2 << ".5\n";
    }
}

void solve() {
    int n;
    cin >> n;

    vector<ll> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    sort(nums.begin(), nums.end());

    if (n == 5) {
        auto left3 = abs((nums[3] + nums[4]) - (nums[0] + nums[2]));
        auto right3 = abs((nums[2] + nums[4]) - (nums[0] + nums[1]));
        pr_half(max(left3, right3));
    } else {
        auto ans = abs((nums[n - 1] + nums[n - 2]) - (nums[0] + nums[1]));
        pr_half(ans);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

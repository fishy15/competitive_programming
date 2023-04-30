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

// prefix sums should be all non-negative
int calc(vector<int> nums) {
    if (nums.empty()) {
        return 0;
    }

    int n = nums.size();

    multiset<int> flippable;
    ll psum = 0;
    int flips = 0;
    for (int i = 0; i < n; i++) {
        psum += nums[i];
        flippable.insert(nums[i]);

        if (psum < 0) {
            psum -= 2 * *flippable.begin();
            flippable.erase(flippable.begin());
            flips++;
        }
    }
    
    return flips;
}

void solve() {
    int n, m;
    cin >> n >> m;
    m--;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    auto before = vector<int>(nums.begin() + 1, nums.begin() + m + 1);
    for (auto &x : before) x *= -1;
    reverse(before.begin(), before.end());

    auto after = vector<int>(nums.begin() + m + 1, nums.end());

    cout << calc(before) + calc(after) << '\n';
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

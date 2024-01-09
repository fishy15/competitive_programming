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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

vector<pair<int, int>> solve_positive(vector<int> nums) {
    int n = nums.size();
    vector<pair<int, int>> ops;
    auto maxi = max_element(nums.begin(), nums.end());
    auto mini = min_element(nums.begin(), nums.end());
    auto maxi_idx = maxi - nums.begin();

    while (abs((int) nums[maxi_idx]) < abs(*mini)) {
        ops.push_back({maxi_idx, maxi_idx});
        nums[maxi_idx] *= 2;
    }

    for (int i = 0; i < n; i++) {
        if (nums[i] < 0) {
            ops.push_back({i, maxi_idx});
            nums[i] += *maxi;
        }
    }

    for (int i = 1; i < n; i++) {
        ops.push_back({i, i - 1});
        nums[i] += nums[i - 1];
    }

    return ops;
}

vector<pair<int, int>> solve_negative(vector<int> nums) {
    int n = nums.size();
    vector<pair<int, int>> ops;
    auto maxi = max_element(nums.begin(), nums.end());
    auto mini = min_element(nums.begin(), nums.end());
    auto mini_idx = mini - nums.begin();

    while (abs(nums[mini_idx]) < abs(*maxi)) {
        ops.push_back({mini_idx, mini_idx});
        nums[mini_idx] *= 2;
    }

    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            ops.push_back({i, mini_idx});
            nums[i] += *mini;
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        ops.push_back({i, i + 1});
        nums[i] += nums[i + 1];
    }

    return ops;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    vector<pair<int, int>> ops;
    if (*min_element(nums.begin(), nums.end()) == 0) {
        ops = solve_positive(nums);
    } else if (*max_element(nums.begin(), nums.end()) == 0) {
        ops = solve_negative(nums);
    } else {
        auto ops1 = solve_positive(nums);
        auto ops2 = solve_negative(nums);
        ops = ops1.size() < ops2.size() ? ops1 : ops2;
    }

    cout << ops.size() << '\n';
    for (auto [a, b] : ops) {
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
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

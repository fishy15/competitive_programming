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
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    bool all_equal = count(nums.begin(), nums.end(), nums[0]) == n;
    if (all_equal) {
        cout << "0\n";
        return;
    }

    if (count(nums.begin(), nums.end(), 1) > 0) {
        cout << "-1\n";
        return;
    }

    vector<array<int, 2>> op;
    while (count(nums.begin(), nums.end(), nums[0]) != n) {
        int min_idx = min_element(nums.begin(), nums.end()) - nums.begin();
        for (int i = 0; i < n; i++) {
            if (i != min_idx && nums[i] != nums[min_idx]) {
                op.push_back({i + 1, min_idx + 1});
                nums[i] = (nums[i] + nums[min_idx] - 1) / nums[min_idx];
            }
        }
    }

    cout << op.size() << '\n';
    for (auto [x, y] : op) {
        cout << x << ' ' << y << '\n';
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

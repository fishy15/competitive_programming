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
    int n, c;
    cin >> n >> c;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    n = nums.size();

    if (nums[0] != 1) {
        cout << "No\n";
        return;
    }

    for (int i = 1; i < n; i++) {
        int cur_not_done = i;
        while (cur_not_done < n) {
            auto base = nums[cur_not_done] / nums[i];
            if (*lower_bound(nums.begin(), nums.end(), base) != base) {
                cout << "No\n";
                return;
            }

            auto at_least_nxt = nums[i] * (base + 1);
            cur_not_done = lower_bound(nums.begin(), nums.end(), at_least_nxt) - nums.begin();
        }
    }

    cout << "Yes\n";
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

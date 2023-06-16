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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

vector<pair<int, int>> compress(int n, const vector<int> &nums) {
    vector<pair<int, int>> res;
    for (int i = 0; i < n - 1; i++) {
        int d = nums[i + 1] - nums[i];
        if (res.empty() || res.back().first != d) {
            res.push_back({d, 1});
        } else {
            res.back().second++;
        }
    }

    return res;
}

int solve(int n, vector<pair<int, int>> nums) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = nums[i].second;
        if (i < n - 1) {
            cur++;
            if (nums[i + 1].second == 1 && i < n - 2 
                && nums[i + 1].first + nums[i + 2].first == 2 * nums[i].first) {
                cur++;
                if (nums[i + 2].second == 1 && i < n - 3 && nums[i + 3].first == nums[i].first) {
                    cur += nums[i + 3].second;
                }
            }
        }
        ans = max(ans, cur);
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<pair<int, int>> c = compress(n, nums);

    int a1 = solve(c.size(), c);
    reverse(c.begin(), c.end());
    int a2 = solve(c.size(), c);

    cout << max(a1, a2) + 1 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

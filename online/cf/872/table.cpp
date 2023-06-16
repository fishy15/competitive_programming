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

ll calc(int n, int m, vector<int> nums) {
    if (n < m) swap(n, m);
    sort(nums.begin(), nums.end());

    if (n == 1) {
        return (ll) (m - 1) * (nums[n * m - 1] - nums[0]);
    } else {
        ll first_col = (ll) (m - 1) * (nums[n * m - 1] - nums[1]);
        ll rest = (ll) (n - 1) * m * (nums[n * m - 1] - nums[0]);
        return first_col + rest;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> nums(n * m), neg_nums(n * m);
    for (int i = 0; i < n * m; i++) {
        cin >> nums[i];
        neg_nums[i] = -nums[i];
    }

    cout << max(calc(n, m, nums), calc(n, m, neg_nums)) << '\n';
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

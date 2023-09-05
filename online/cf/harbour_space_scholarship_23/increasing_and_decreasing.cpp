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
    int x, y, n;
    cin >> x >> y >> n;

    vector<int> nums(n);
    nums[n - 1] = y;
    for (int i = n - 2; i > 0; i--) {
        int diff = n - i - 1;
        nums[i] = nums[i + 1] - diff;
    }

    nums[0] = x;
    if (nums[1] - nums[0] > nums[2] - nums[1]) {
        for (auto x : nums) {
            cout << x << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
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

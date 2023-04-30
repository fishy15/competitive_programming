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

bool check(int x, const vector<int> &nums) {
    int l = 0;
    int r = (int) nums.size() - 1;
    while (l <= r) {
        while (l <= r && nums[l] == x) l++;
        while (r >= l && nums[r] == x) r--;

        if (l <= r && nums[l] != nums[r]) {
            return false;
        }

        l++;
        r--;
    }

    return true;
}

void solve() {
    int n; cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int idx = 0;
    for (idx = 0; idx < n; idx++) {
        if (nums[idx] != nums[n - idx - 1]) {
            if (check(nums[idx], nums) || check(nums[n - idx - 1], nums)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

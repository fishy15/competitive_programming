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

    vector<ll> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    sort(nums.begin(), nums.end());

    ll gap = 0;
    for (int i = 0; i < n - 1; i++) {
        gap = gcd(gap, nums[n-1] - nums[i]);
    }

    int steps = n;
    for (int i = n - 2; i >= 0; i--) {
        int diff = (n - 1) - i;
        if (nums[i] != nums[n-1] - diff * gap) {
            steps = diff;
            break;
        }
    }

    ll cost = 0;
    for (int i = 0; i < n - 1; i++) {
        cost += (nums[n-1] - nums[i]) / gap;
    }

    cout << cost + steps << '\n';
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

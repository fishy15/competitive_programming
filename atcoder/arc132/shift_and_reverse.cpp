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
#define MAXN 100010

using namespace std;

int n;
int nums[MAXN];

void solve_asc() {
    int one = find(nums, nums + n, 1) - nums;
    int ans = min(one, (n - one) + 2);
    cout << ans << '\n';
}

void solve_desc() {
    int one = find(nums, nums + n, 1) - nums;
    int ans = min((one + 1) + 1, (n - one - 1) + 1);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int one = find(nums, nums + n, 1) - nums;
    int nxt = (one + 1) % n;

    if (nums[nxt] == 2) {
        solve_asc();
    } else {
        solve_desc();
    }

    return 0;
}

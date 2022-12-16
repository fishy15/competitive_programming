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

int min_reduce(int x) {
    int y = x;

    int cnt = 0;
    while (x % 2 == y % 2) {
        y /= 2;
        cnt++;
    }

    return cnt;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 == 1) {
        int ans = INF;
        for (int i = 0; i < n; i++) {
            ans = min(ans, min_reduce(nums[i]));
        }

        cout << ans << '\n';
    } else {
        cout << "0\n";
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

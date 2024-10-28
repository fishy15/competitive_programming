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
    int n, m;
    cin >> n >> m;
    swap(n, m);

    if (n == 1) {
        cout << "0\n";
    } else {
        cout << min(n, m + 1) << '\n';
    }

    vector<int> nums(n);
    iota(nums.begin(), nums.end(), 0);

    for (int i = 0; i < m; i++) {
        for (auto x : nums) {
            cout << x << ' ';
        }
        cout << '\n';

        if (i < n - 2) {
            rotate(nums.begin(), nums.begin() + 1, nums.end());
        }
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

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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    auto mx = *max_element(all(nums));
    auto mn = *min_element(all(nums));
    auto mx_count = count(all(nums), mx);

    if ((mx - 1) - mn > k) {
        cout << "Jerry\n";
    } else if (mx_count > 1 && mx - mn > k) {
        cout << "Jerry\n";
    } else {
        auto total = accumulate(all(nums), 0LL);
        if (total % 2 == 0) {
            cout << "Jerry\n";
        } else {
            cout << "Tom\n";
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

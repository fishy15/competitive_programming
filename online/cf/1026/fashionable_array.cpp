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
    int n;
    cin >> n;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    sort(all(nums));

    int first_odd = -1;
    int last_odd = -1;
    int first_even = -1;
    int last_even = -1;

    rep(i, 0, n) {
        if (nums[i] % 2 == 0) {
            if (first_even == -1) {
                first_even = i;
            }
            last_even = i;
        } else {
            if (first_odd == -1) {
                first_odd = i;
            }
            last_odd = i;
        }
    }

    int ans = n;
    if (first_odd != -1) {
        ans = min(ans, first_odd + ((n-1) - last_odd));
    }
    if (first_even != -1) {
        ans = min(ans, first_even + ((n-1) - last_even));
    }
    cout << ans << '\n';
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

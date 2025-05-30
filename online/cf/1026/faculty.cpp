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

    vector<int> nums;
    int mx = 0;

    vector<ll> ans(n);

    rep(i, 0, n) {
        int x;
        cin >> x;

        if (mx == 0) {
            ans[i] = 0;
        } else {
            ans[i] = ans[i-1];
            if (x <= mx) {
                ans[i] = max(ans[i], (ll) x % mx + mx % x);
            } else {
                if (2 * mx > x) {
                    ans[i] = x;
                } else {
                    // we increase by more than twice, so ok to loop
                    for (auto y : nums) {
                        ans[i] = max(ans[i], (ll) x % y + y % x);
                    }
                }
            }
        }

        nums.push_back(x);
        mx = max(mx, x);
    }

    for (auto x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
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

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

    vector<ll> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    vector<array<ll, 3>> dp(n+1);
    for (int i = n-1; i >= 0; i--) {
        dp[i][0] = min(dp[i+1][0], dp[i+1][1]) + nums[i];
        dp[i][1] = min(dp[i+1][0], dp[i+1][2]) + max(0LL, nums[i] - i);
        dp[i][2] = min(dp[i+1][0], dp[i+1][2]) + (nums[i] - 1);
    }

    cout << dp[0][0] << '\n';
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

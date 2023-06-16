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

template<typename T>
T ckmin(T &a, T b) {
    return a = min(a, b);
}

ll sub(ll x, ll d) {
    if (x == 0) return 0;
    return d - x;
}

void solve() {
    int n, d; cin >> n >> d;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<vector<array<ll, 4>>> dp(n, vector<array<ll, 4>>(n, array<ll, 4>{INFLL, INFLL, INFLL, INFLL}));

    for (int l = n - 1; l >= 0; l--) {
        dp[l][l][0b00] = nums[l];
        dp[l][l][0b11] = sub(nums[l], d);

        for (int r = l; r < n; r++) {
            for (int i = l; i < r; i++) {
                ckmin(dp[l][r][0b00], dp[l][i][0b00] + dp[i + 1][r][0b00] - min(nums[i], nums[i + 1]));
                ckmin(dp[l][r][0b00], dp[l][i][0b01] + dp[i + 1][r][0b00]);
                ckmin(dp[l][r][0b00], dp[l][i][0b00] + dp[i + 1][r][0b10]);
                ckmin(dp[l][r][0b00], dp[l][i][0b01] + dp[i + 1][r][0b10] - min(sub(nums[i], d), sub(nums[i + 1], d)));

                ckmin(dp[l][r][0b01], dp[l][i][0b00] + dp[i + 1][r][0b01] - min(nums[i], nums[i + 1]));
                ckmin(dp[l][r][0b01], dp[l][i][0b01] + dp[i + 1][r][0b01]);
                ckmin(dp[l][r][0b01], dp[l][i][0b00] + dp[i + 1][r][0b11]);
                ckmin(dp[l][r][0b01], dp[l][i][0b01] + dp[i + 1][r][0b11] - min(sub(nums[i], d), sub(nums[i + 1], d)));

                ckmin(dp[l][r][0b10], dp[l][i][0b10] + dp[i + 1][r][0b00] - min(nums[i], nums[i + 1]));
                ckmin(dp[l][r][0b10], dp[l][i][0b11] + dp[i + 1][r][0b00]);
                ckmin(dp[l][r][0b10], dp[l][i][0b10] + dp[i + 1][r][0b10]);
                ckmin(dp[l][r][0b10], dp[l][i][0b11] + dp[i + 1][r][0b10] - min(sub(nums[i], d), sub(nums[i + 1], d)));

                ckmin(dp[l][r][0b11], dp[l][i][0b10] + dp[i + 1][r][0b01] - min(nums[i], nums[i + 1]));
                ckmin(dp[l][r][0b11], dp[l][i][0b11] + dp[i + 1][r][0b01]);
                ckmin(dp[l][r][0b11], dp[l][i][0b10] + dp[i + 1][r][0b11]);
                ckmin(dp[l][r][0b11], dp[l][i][0b11] + dp[i + 1][r][0b11] - min(sub(nums[i], d), sub(nums[i + 1], d)));
            }
        }
    }

    cout << *min_element(dp[0][n - 1].begin(), dp[0][n - 1].end()) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

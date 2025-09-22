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

    string s;
    cin >> s;

    vector<int> r_pos;
    rep(i, 0, n) {
        if (s[i] == '0') {
            r_pos.push_back(i);
        }
    }

    if (r_pos.empty()) {
        cout << "YES\n";
        return;
    }

    // 0 = left, 1 = right
    vector<array<bool, 2>> dp(sz(r_pos));
    if (r_pos[0] == 0) {
        dp[0][0] = true;
    }

    // it can always look this way, will decide later if it is matched
    dp[0][1] = true;

    rep(i, 1, sz(r_pos)) {
        if (dp[i-1][0]) {
            if (r_pos[i-1] == r_pos[i] - 1) {
                dp[i][0] = true;
            }
            dp[i][1] = true;
        }

        if (dp[i-1][1]) {
            if (r_pos[i-1] == r_pos[i] - 1 || r_pos[i-1] == r_pos[i] - 2) {
                dp[i][0] = true;
            }
            if (r_pos[i-1] == r_pos[i] - 1) {
                dp[i][1] = true;
            }
        }
    }

    if (dp.back()[0] || (dp.back()[1] && r_pos.back() == n-1)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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

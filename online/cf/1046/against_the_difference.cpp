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
    vector<vector<int>> locs(n+1);
    rep(i, 0, n) {
        cin >> nums[i];
        locs[nums[i]].push_back(i);
    }

    vector<int> nxt(n, -1);
    rep(i, 1, n+1) {
        rep(j, 0, sz(locs[i])) {
            if (j + i <= sz(locs[i])) {
                nxt[locs[i][j]] = locs[i][i + j - 1] + 1;
            }
        }
    }

    vector<int> dp(n + 1);
    rep(i, 0, n) {
        dp[i + 1] = max(dp[i], dp[i + 1]);
        if (nxt[i] != -1) {
            dp[nxt[i]] = max(dp[nxt[i]], dp[i] + nums[i]);
        }
    }

    cout << dp[n] << '\n';
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

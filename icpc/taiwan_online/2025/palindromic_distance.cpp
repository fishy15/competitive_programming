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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

void solve() {
    string s;
    cin >> s;

    int n = sz(s);
    // cost ot turn [l, r) into a palindrome
    vector dp(n+1, vector(n+1, INF));
    for (int l = n; l >= 0; l--) {
        for (int r = l; r <= n; r++) {
            if (r - l <= 1) {
                dp[l][r] = 0;
            } else {
                if (s[l] == s[r-1]) {
                    ckmin(dp[l][r], dp[l+1][r-1]);
                } else {
                    ckmin(dp[l][r], dp[l+1][r-1] + 1);
                }
                ckmin(dp[l][r], dp[l+1][r] + 1);
                ckmin(dp[l][r], dp[l][r-1] + 1);
            }
        }
    }

    cout << dp[0][n] << '\n';
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

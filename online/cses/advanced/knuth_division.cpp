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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> x(n);
    rep(i, 0, n) {
        cin >> x[i];
    }

    vector<ll> psum(n + 1);
    partial_sum(all(x), psum.begin() + 1);

    vector dp(n, vector(n, INFLL));
    vector opt(n, vector(n, -1));

    for (int i = n-1; i >= 0; i--) {
        dp[i][i] = 0;
        opt[i][i] = i;
        rep(j, i+1, n) {
            auto cost = psum[j + 1] - psum[i];
            pair<ll, int> best = {INFLL, -1};
            rep(k, opt[i][j-1], min(j-1, opt[i+1][j])+1) {
                best = min(best, {dp[i][k] + dp[k+1][j] + cost, k});
            }
            dp[i][j] = best.first;
            opt[i][j] = best.second;
        }
    }

    cout << dp[0][n-1] << '\n';

    return 0;
}

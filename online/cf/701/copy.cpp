/*
 * Let dp[i] represent how many valid arrays of length i exist such that the final number satisifies only
 * the prefix condition, not the equality condition (if it satisfies both, then it is not counted). We note
 * that dp[0] = 1 and dp[i] = sum(dp[j] if sum(b_j, b_j+1, ..., b_i-1) != 0). We also note that if x is
 * the largest index such that sum(b_x, b_x+1, ..., b_i-1) = 0, then dp[x] represents the initial part
 * of the sum, so dp[i] = sum(dp[j] if x <= j < i). We can use a map to maintain the last position.
 */

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
    int n; cin >> n;
    vector<ll> nums(n);
    vector<ll> ssum(n);
    vector<ll> psum(n);
    map<ll, int> prev;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        ssum[i] = nums[i];
        if (i < n - 1) ssum[i] += ssum[i + 1];
    }

    psum[0] = 1;
    prev[ssum[0]] = 0;
    for (int i = 1; i < n; i++) {
        psum[i] = psum[i - 1];
        ll x = psum[i - 1];
        if (prev.count(ssum[i])) {
            if (prev[ssum[i]] == 0) {
                x--;
            } else {
                x -= psum[prev[ssum[i]] - 1];
            }
            if (x < 0) x += MOD;
        }
        psum[i] += x;
        if (psum[i] >= MOD) psum[i] -= MOD;
        prev[ssum[i]] = i;
    }

    cout << psum[n - 1] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

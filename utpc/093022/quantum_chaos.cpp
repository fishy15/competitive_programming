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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    
    vector<pair<int, int>> q(n);
    for (int i = 0; i < n; i++) {
        cin >> q[i].first >> q[i].second;
    }

    vector<ll> dp(1 << n);
    for (int i = 0; i < n; i++) {
        dp[1 << i] = q[i].first + q[i].second * n;
    }

    for (int i = 1; i < (1 << n); i++) {
        if (dp[i] != 0) continue;

        ll sum_a = 0;
        ll sum_b = 0;
        ll k = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sum_a += q[j].first;
                sum_b += q[j].second;
                k++;
            }
        }

        k--;

        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sum_a -= q[j].first;
                sum_b -= q[j].second;

                ll val = dp[i ^ (1 << j)]
                       + k * sum_a * q[j].first
                       + (n - k) * sum_b * q[j].second;

                dp[i] = max(dp[i], val);

                sum_a += q[j].first;
                sum_b += q[j].second;
            }
        }
    }

    cout << dp[(1 << n) - 1] << '\n';

    return 0;
}

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

int best(const vector<ll> &diff) {
    int sz = diff.size();

    vector<int> dp(1 << sz);
    for (int m = 0; m < (1 << sz); m++) {
        if (m > 0) {
            ll pos_sum = 0;
            ll neg_sum = 0;

            for (int j = 0; j < sz; j++) {
                if (m & (1 << j)) {
                    if (diff[j] > 0) pos_sum += diff[j];
                    else neg_sum += diff[j];
                }
            }

            if (pos_sum == -neg_sum) {
                dp[m]++;
            }
        }

        for (int j = 0; j < sz; j++) {
            int nxt_m = m ^ (1 << j);
            if (m < nxt_m) {
                dp[nxt_m] = max(dp[nxt_m], dp[m]);
            }
        }
    }

    return dp.back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    vector<ll> diff(n + 1);
    for (int i = 0; i <= n; i++) {
        int p = (i == 0) ? 0 : a[i - 1];
        int c = (i == n) ? 0 : a[i];
        diff[i] = c - p;
    }

    vector<ll> diff_no_zero;
    for (auto x : diff) {
        if (x != 0) {
            diff_no_zero.push_back(x);
        }
    }

    auto common = best(diff_no_zero);
    auto needed = diff_no_zero.size();

    cout << needed - common << '\n';

    return 0;
}

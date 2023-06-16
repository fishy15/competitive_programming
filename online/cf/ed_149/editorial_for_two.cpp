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

void solve() {
    int n, k;
    cin >> n >> k;

    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<int> left_cnt(n), right_cnt(n + 1);
    auto check = [&](ll m) {
        ll sum = 0;
        priority_queue<ll> pq;

        for (int i = 0; i < n; i++) {
            pq.push(nums[i]);
            sum += nums[i];

            while (sum > m) {
                sum -= pq.top();
                pq.pop();
            }

            left_cnt[i] = pq.size();
        }

        pq = {};
        sum = 0;

        for (int i = n - 1; i >= 0; i--) {
            pq.push(nums[i]);
            sum += nums[i];

            while (sum > m) {
                sum -= pq.top();
                pq.pop();
            }

            right_cnt[i] = pq.size();
        }

        for (int i = 0; i < n; i++) {
            if (left_cnt[i] + right_cnt[i + 1] >= k) {
                return true;
            }
        }

        return false;
    };

    ll lo = 0;
    ll hi = accumulate(nums.begin(), nums.end(), 0LL);
    ll ans = -1;

    while (lo <= hi) {
        ll m = lo + (hi - lo) / 2;
        if (check(m)) {
            ans = m;
            hi = m - 1;
        } else {
            lo = m + 1;
        }
    }

    cout << ans << '\n';
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

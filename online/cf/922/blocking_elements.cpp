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
    int n;
    cin >> n;

    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<ll> psum(n + 1);
    for (int i = 0; i < n; i++) {
        psum[i + 1] = psum[i] + nums[i];
    }

    nums.push_back(0);
    n++;

    ll l = 0;
    ll r = accumulate(nums.begin(), nums.end(), 0LL);
    ll ans = INFLL;

    auto comp = [&](ll m) {
        vector<ll> dp(n, INFLL);

        // {dp value, psum}
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> cur;
        cur.push({0, 0});
        for (int i = 0; i < n; i++) {
            // remove values that we cannot keep until now
            while (!cur.empty() && psum[i] - cur.top().second > m) {
                cur.pop();
            }

            cur.push({cur.top().first + nums[i], psum[i + 1]});
        }

        return cur.top().first;
    };

    while (l <= r) {
        auto m = l + (r - l) / 2;
        auto res = comp(m);
        ans = min(ans, max(res, m));
        if (res < m) {
            r = m - 1;
        } else {
            l = m + 1;
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

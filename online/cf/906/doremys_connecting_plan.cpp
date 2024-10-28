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
    int n, c;
    cin >> n >> c;

    vector<ll> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    ll cur = nums[0];
    vector<pair<ll, ll>> needed;
    needed.reserve(n - 1);
    for (int i = 1; i < n; i++) {
        ll tot = (ll) c * (i + 1);
        needed.push_back({tot - nums[i], nums[i]});
    }

    sort(needed.begin(), needed.end());
    for (auto [limit, to_add] : needed) {
        if (cur >= limit) {
            cur += to_add;
        } else {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
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

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
    ll n, l, r; cin >> n >> l >> r;
    l--; r--;

    vector<ll> nums(n);
    for (ll i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums.begin(), nums.end());

    ll ans = 0;
    auto lb = [&](ll x) { return lower_bound(nums.begin(), nums.end(), x) - nums.begin(); };
    auto ub = [&](ll x) { return upper_bound(nums.begin(), nums.end(), x) - nums.begin(); };
    for (int i = 0; i < n; i++) {
        ans += ub(r - nums[i]) - lb(l - nums[i]);
        if (l <= 2 * nums[i] && 2 * nums[i] <= r) {
            ans--;
        }
    }

    ans /= 2;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

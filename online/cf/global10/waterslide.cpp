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
    vector<ll> nums;
    ll ans = 0;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        nums.push_back(x);
    }

    for (int i = n - 1; i > 0; i--) {
        if (nums[i] < nums[i - 1]) {
            ans += nums[i - 1] - nums[i];
        }
    }

    cout << ans << '\n';
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

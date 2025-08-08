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

ll cost(int x, int y) {
    return abs(x - y);
}

ll cost_diff(pair<int, int> a, pair<int, int> b) {
    array<int, 4> nums{a.first, a.second, b.first, b.second};
    sort(all(nums));
    return cost(nums[0], nums[3]) + cost(nums[1], nums[2]) - cost(a.first, a.second) - cost(b.first, b.second);
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, n) {
        cin >> b[i];
    }

    vector<pair<int, int>> ints;
    ll base_cost = 0;
    rep(i, 0, n) {
        base_cost += cost(a[i], b[i]);
        if (a[i] < b[i]) {
            ints.push_back({a[i], b[i]});
        } else {
            ints.push_back({b[i], a[i]});
        }
    }

    sort(all(ints));
    ll ans = INFLL;
    rep(i, 0, n-1) {
        ans = min(ans, base_cost + cost_diff(ints[i], ints[i+1]));
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

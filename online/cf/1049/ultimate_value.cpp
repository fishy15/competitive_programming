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

void solve() {
    int n;
    cin >> n;

    vector<ll> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    ll cur_cost = 0;
    rep(i, 0, n) {
        if (i % 2 == 0) {
            cur_cost += nums[i];
        } else {
            cur_cost -= nums[i];
        }
    }

    // testing single swap
    ll even_min_loss = -INFLL;
    ll odd_max_gain = -INFLL;
    ll best_gain = 0;
    rep(i, 0, n) {
        if (i % 2 == 0) {
            best_gain = max(best_gain, (-2 * nums[i] + i) + odd_max_gain);
            even_min_loss = max(even_min_loss, -2 * nums[i] - i);
        } else {
            best_gain = max(best_gain, (2 * nums[i] + i) + even_min_loss);
            odd_max_gain = max(odd_max_gain, 2 * nums[i] - i);
        }
    }

    best_gain = max(best_gain, (ll) (n - 1) / 2 * 2);
    cout << cur_cost + best_gain << '\n';
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

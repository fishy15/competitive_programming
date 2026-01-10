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
    vector<ll> psum(n + 1);
    rep(i, 0, n) {
        cin >> nums[i];
        psum[i+1] = psum[i] + nums[i];
    }

    // exclusive
    auto sum = [&](int l, int r) {
        return psum[r] - psum[l];
    };

    // inclusive
    auto works = [&](int l, int r) {
        if (r - l + 1 >= 3) {
            auto goal = nums[l] ^ nums[r];
            return goal == sum(l+1, r);
        }
        return false;
    };

    set<pair<ll, int>> ord;
    ll ans = 0;
    for (int i = n-1; i >= 0; i--) {
        auto it = ord.lower_bound({-2 * nums[i] - sum(0, i), 0});
        while (it != end(ord)) {
            if (works(i, it->second)) {
                ans++;
            }
            it++;
        }
        ord.insert({nums[i] - sum(0, i), i});
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;

    while (t--) {
        solve();
    }

    return 0;
}

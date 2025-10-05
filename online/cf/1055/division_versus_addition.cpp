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

ll cost(ll x) {
    ll moves = 0;
    while (x > 1) {
        x /= 2;
        moves++;
        if (x > 1) {
            x++;
        }
    }
    return moves;
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<ll> nums(n);
    vector<ll> psum(n+1);
    vector<ll> gsum(n+1);
    rep(i, 0, n) {
        cin >> nums[i];
        psum[i+1] = psum[i] + cost(nums[i]);
        gsum[i+1] = (cost(nums[i] + 1) - cost(nums[i])) + gsum[i];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;

        auto ans = (psum[r] - psum[l]) + (gsum[r] - gsum[l]) / 2;
        cout << ans << '\n';
    }
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

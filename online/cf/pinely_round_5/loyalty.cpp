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
    int n, x;
    cin >> n >> x;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    sort(all(nums), greater<>{});

    ll ans = 0;
    ll cur = 0;
    int l = 0;
    int r = n;
    vector<int> ord;
    ord.reserve(n);
    while (l < r) {
        if (cur / x < (cur + nums[l]) / x) {
            ans += nums[l];
            cur += nums[l];
            ord.push_back(nums[l]);
            l++;
        } else {
            r--;
            cur += nums[r];
            ord.push_back(nums[r]);
        }
    }

    cout << ans << '\n';
    for (auto a : ord) {
        cout << a << ' ';
    }
    cout << '\n';
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

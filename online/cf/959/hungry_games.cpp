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
    ll x;
    cin >> n >> x;

    vector<ll> nums(n);
    vector<ll> psum(n + 1);
    rep(i, 0, n) {
        cin >> nums[i];
        psum[i + 1] = psum[i] + nums[i];
    }

    auto find_first_ge_x = [&](int start) {
        int l = start;
        int r = n;
        int ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (psum[m] - psum[start] > x) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    };

    vector<int> ans_at(n + 1);
    for (int i = n-1; i >= 0; i--) {
        auto idx = find_first_ge_x(i);
        if (idx == -1) {
            ans_at[i] = n - i;
        } else {
            ans_at[i] = ans_at[idx] + (idx - i - 1);
        }
    }

    auto total = accumulate(all(ans_at), 0LL);
    cout << total << '\n';
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

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    multiset<int> pref, suf;
    pref.insert(nums[0]);
    ll pref_sum = nums[0];

    rep(i, 1, n) {
        suf.insert(nums[i]);
    }
    ll suf_sum = accumulate(nums.begin()+1, nums.end(), 0LL);

    ll ans = 0;
    rep(i, 1, n) {
        // process split
        auto big_left = pref_sum - *pref.begin();
        auto small_left = pref_sum - *pref.rbegin();

        auto big_right = suf_sum - *suf.begin();
        auto small_right = suf_sum - *suf.rbegin();
        
        ans = max({
            ans,
            abs(big_left - big_right),
            abs(small_left - big_right),
            abs(big_left - small_right),
            abs(small_left - small_right)
        });

        pref.insert(nums[i]);
        pref_sum += nums[i];
        suf.erase(suf.find(nums[i]));
        suf_sum -= nums[i];
    }

    cout << ans << '\n';

    return 0;
}

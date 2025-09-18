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

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    map<int, int> cnt;
    int r = 0;
    ll cur = 0;
    ll ans = 0;
    rep(l, 0, n) {
        while (r < n && (sz(cnt) < k || cnt.count(nums[r]))) {
            cnt[nums[r]]++;
            cur += nums[r];
            r++;
        }

        ans = max(ans, cur);
        cur -= nums[l];
        cnt[nums[l]]--;
        if (cnt[nums[l]] == 0) {
            cnt.erase(nums[l]);
        }
    }

    cout << ans << '\n';

    return 0;
}

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
    int n, q;
    cin >> n >> q;

    vector<ll> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    auto comp_ans = [&](ll mask) {
        ll ans = 0;
        set<int> shifted_up;
        for (int i = 30; i >= 0; i--) {
            if (mask & (1 << i)) {
                pair<ll, int> best = {INFLL, -1};
                rep(j, 0, n) {
                    ll cost;
                    if (shifted_up.count(j)) {
                        cost = 1 << i;
                    } else if (nums[j] & (1 << i)) {
                        cost = 0;
                    } else {
                        auto save = nums[j] & ((1 << i) - 1);
                        cost = (1 << i) - save;
                    }
                    best = min(best, pair{cost, j});
                }

                ans += best.first;
                if (best.first > 0) {
                    shifted_up.insert(best.second);
                }
            }
        }

        return ans;
    };

    auto cur_or = accumulate(all(nums), 0LL, bit_or{});
    auto cur_popcnt = __builtin_popcountll(cur_or);

    array<int, 32> ans{};
    ans.fill(-1);
    ans[cur_popcnt] = 0;
    for (int i = cur_popcnt + 1; i <= 31; i++) {
        // set first 0
        int p = 0;
        while ((1 << p) & cur_or) p++;
        cur_or ^= 1 << p;
        ans[i] = comp_ans(cur_or);
    }

    while (q--) {
        int x;
        cin >> x;
        auto res = upper_bound(all(ans), x) - begin(ans) - 1;
        cout << res << '\n';
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

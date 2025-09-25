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
#include <chrono>
#include <random>

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_idx(int l, int r) {
    return uniform_int_distribution(l, r - 1)(rng);
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    auto ord = nums;
    sort(all(ord));
    ord.erase(unique(all(ord)), end(ord));

    auto get = [&](int x) -> int { return lower_bound(all(ord), x) - begin(ord); };
    vector<vector<int>> locs(sz(ord));
    rep(i, 0, n) {
        locs[get(nums[i])].push_back(i);
    }

    auto get_count = [&](int x, int l, int r) {
        const auto &loc = locs[get(x)];
        auto start_it = lower_bound(all(loc), l);
        auto end_it = lower_bound(all(loc), r);
        return (int) (end_it - start_it);
    };

    vector<int> sample;
    vector<int> ans;
    while (q--) {
        sample.clear();
        ans.clear();

        int l, r;
        cin >> l >> r;
        l--;

        auto goal = (r - l) / 3;

        constexpr int trials = 6 * 20;
        rep(_, 0, trials) {
            auto v = nums[rand_idx(l, r)];
            sample.push_back(v);
        }

        sort(all(sample));
        sample.erase(unique(all(sample)), end(sample));
        for (auto x : sample) {
            if (get_count(x, l, r) > goal) {
                ans.push_back(x);
            }
        }

        if (ans.empty()) {
            cout << "-1\n";
        } else {
            for (auto x : ans) cout << x << ' ';
            cout << '\n';
        }
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

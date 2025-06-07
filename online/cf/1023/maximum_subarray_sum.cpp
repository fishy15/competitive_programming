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

template<typename T>
ll kadane(T start, T end) {
    // best sum with 0s as -infs
    ll cur_sum = 0;
    ll best_sum = 0;
    auto cur = start;
    while (cur != end) {
        auto [x, present] = *cur;
        if (present) {
            cur_sum = max(x, cur_sum + x);
        } else {
            cur_sum = 0;
        }
        best_sum = max(best_sum, cur_sum);
        cur += 1;
    }
    return best_sum;
}

template<typename T>
ll not_kadane(T start, T end) {
    // best sum with 0s as -infs
    ll cur_sum = 0;
    ll best_sum = 0;
    auto cur = start;
    while (cur != end) {
        auto [x, present] = *cur;
        if (present) {
            cur_sum += x;
        } else {
            break;
        }
        best_sum = max(best_sum, cur_sum);
        cur += 1;
    }
    return best_sum;
}

constexpr ll MIN = -1e18;

void solve() {
    int n;
    ll k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<pair<ll, bool>> nums(n);
    rep(i, 0, n) {
        cin >> nums[i].first;
        nums[i].second = (s[i] == '1');
    }

    auto cur_mx = kadane(all(nums));
    if (cur_mx > k) {
        cout << "No\n";
        return;
    }

    auto zero_it = find_if(all(nums), [](auto p) { return !p.second; });
    if (zero_it == end(nums)) {
        if (cur_mx == k) {
            cout << "Yes\n";
            for (auto [x, _] : nums) {
                cout << x << ' ';
            }
            cout << '\n';
        } else {
            cout << "No\n";
        }
    } else {
        auto zero_pos = (int) (zero_it - begin(nums));
        auto before = not_kadane(rbegin(nums) + (n - zero_pos), rend(nums));
        auto after = not_kadane(begin(nums) + zero_pos + 1, end(nums));
        auto needed = k - before - after;

        cout << "Yes\n";
        rep(i, 0, n) {
            auto [x, present] = nums[i];
            if (present) {
                cout << x << ' ';
            } else if (i == zero_pos) {
                cout << needed << ' ';
            } else {
                cout << MIN << ' ';
            }
        }
        cout << '\n';
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

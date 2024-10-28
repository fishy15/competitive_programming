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

// change if necessary
#define MAXN 1000000

using namespace std;

int get_idx(int n) {
    int cnt = 0;
    while (n > 1) {
        n >>= 1;
        cnt++;
    }
    return cnt;
}

bool is_p(int x) {
    return (x & (x - 1)) == 0;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    ll total = accumulate(nums.begin(), nums.end(), 0LL);
    if (total % n != 0) {
        cout << "No\n";
        return;
    }

    auto goal = total / n;
    array<int, 31> to_add{}, to_rem{}, solo_a{}, solo_r{};
    for (auto x : nums) {
        auto d = abs(x - goal);
        if (d == 0) continue;

        int cur_p = 1;
        while (cur_p <= d) cur_p *= 2;
        int left = cur_p - d;

        // if it is a power of two
        if ((left & (left - 1)) == 0) {
            if (x < goal) {
                to_add[get_idx(cur_p)]++;
                to_rem[get_idx(left)]++;
            } else {
                to_rem[get_idx(cur_p)]++;
                to_add[get_idx(left)]++;
            }
        } else {
            cout << "No\n";
            return;
        }

        if (is_p(d)) {
            if (x < goal) {
                solo_a[get_idx(d)]++;
            } else {
                solo_r[get_idx(d)]++;
            }
        }
    }

    for (int i = 30; i >= 1; i--) {
        if (to_add[i] > to_rem[i]) {
            int d = to_add[i] - to_rem[i];
            if (d <= solo_a[i - 1] && 2 * d <= to_rem[i - 1]) {
                to_add[i] -= d;
                to_rem[i - 1] -= 2 * d;
            } else {
                cout << "No\n";
                return;
            }
        } else if (to_add[i] < to_rem[i]) {
            int d = to_rem[i] - to_add[i];
            if (d <= solo_r[i - 1] && 2 * d <= to_add[i - 1]) {
                to_rem[i] -= d;
                to_add[i - 1] -= 2 * d;
            } else {
                cout << "No\n";
                return;
            }
        }
    }

    if (to_add == to_rem) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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

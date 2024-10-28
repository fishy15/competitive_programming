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

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    map<int, int> cnt;
    for (auto x : nums) {
        cnt[x]++;
    }

    vector<int> cur;
    vector<pair<int, int>> mov;
    vector<int> rep_size;
    for (auto [v, c] : cnt) {
        if (c % 2 == 1) {
            cout << "-1\n";
            return;
        } else {
            for (int i = 0; i < c; i += 2) {
                mov.push_back({0, v});
                cur.push_back(v);
                cur.push_back(v);
            }
        }
    }

    reverse(cur.begin(), cur.end());

    auto get_last_mismatch = [&]{
        for (int i = n - 1; i >= 0; i--) {
            if (nums[i] != cur[i]) {
                return i;
            }
        }
        return -1;
    };

    int base = 0;
    auto rev = [&](int k) {
        if (k > 1) {
            for (int i = 0; i < k; i++) {
                mov.push_back({base + i + k, cur[i]});
            }
            reverse(cur.begin(), cur.begin() + k);
            base += 2 * k;
            rep_size.push_back(2 * k);
        }
    };

    int idx;
    while ((idx = get_last_mismatch()) != -1) {
        int need_loc = -1;
        for (int i = idx; i >= 0; i--) {
            if (cur[i] == nums[idx]) {
                need_loc = i;
                break;
            }
        }
        rev(need_loc + 1);
        rev(idx + 1);
    }

    rep_size.push_back(2 * n);

    cout << mov.size() << '\n';
    for (auto [a, b] : mov) {
        cout << a << ' ' << b << '\n';
    }

    cout << rep_size.size() << '\n';
    for (auto x : rep_size) {
        cout << x << ' ';
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

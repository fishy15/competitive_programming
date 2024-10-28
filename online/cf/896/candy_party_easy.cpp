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

    ll total = accumulate(nums.begin(), nums.end(), 0LL);
    if (total % n != 0) {
        cout << "No\n";
        return;
    }

    auto goal = total / n;
    vector<int> to_rem, to_add;
    for (auto x : nums) {
        auto d = abs(x - goal);
        if (d == 0) continue;

        int cur_p = 1;
        while (cur_p <= d) cur_p *= 2;
        int left = cur_p - d;

        // if it is a power of two
        if ((left & (left - 1)) == 0) {
            if (x < goal) {
                to_add.push_back(cur_p);
                to_rem.push_back(left);
            } else {
                to_rem.push_back(cur_p);
                to_add.push_back(left);
            }
        } else {
            cout << "No\n";
            return;
        }
    }

    sort(to_add.begin(), to_add.end());
    sort(to_rem.begin(), to_rem.end());

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

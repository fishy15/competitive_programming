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

map<int, int> iter(const map<int, int> &old) {
    map<int, int> res;
    for (auto it = old.begin(); it != old.end(); it++) {
        auto [v, c] = *it;
        if (c > 1) {
            res[0] += c - 1;
        }

        if (next(it) != old.end()) {
            res[next(it)->first - v]++;
        }
    }
    return res;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    map<int, int> cur_step;
    for (int i = 0; i < n - 1; i++) {
        cur_step[nums[i + 1] - nums[i]]++;
    }

    for (int i = 0; i < n - 2; i++) {
        cur_step = iter(cur_step);
    }

    cout << cur_step.begin()->first << '\n';
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

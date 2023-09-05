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

// first are endpoints of checking
// second are endpoints of valid inner interval
struct opt {
    ll l, r, bl, br;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    ll m;
    cin >> n >> m >> k;

    vector<array<ll, 2>> nums(n);
    set<ll> added;
    for (int i = 0; i < n; i++) {
        cin >> nums[i][0];
        nums[i][1] = i;
    }

    vector<opt> opts;

    if (k >= n + 1) {
        // everyone wins
        cout << m + 1 << ' ' << 0 << '\n';
    } else if (k == 1) {
        sort(nums.begin(), nums.end());
        opts.push_back({-INF, nums[0][0], 0, m});
        for (int i = 0; i < n - 1; i++) {
            opts.push_back({nums[i][0], nums[i + 1][0], 0, m});
        }
        opts.push_back({nums.back()[0], INF, 0, m});
    } else {
        // need to reduce to handle duplicates properly
        map<ll, array<int, 2>> info;
        for (auto [x, i] : nums) {
            if (info.count(x)) {
                auto &entry = info[x];
                entry[0] = max<int>(i, entry[0]);
                entry[1]++;
            } else {
                info[x] = {(int) i, 1};
            }
        }

        // [0, 1, .., k - 1]
        opts.push_back({-INF, nums[k - 1][0], 0, m});

        for (int i = 0; i < n - 1; i++) {
            opts.push_back({nums[i][0], nums[i + 1][0], 0, m});
        }

        opts.push_back({nums.back()[0], INF, 0, m});
    }

    /* solve(opts); */

    return 0;
}

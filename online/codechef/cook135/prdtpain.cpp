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

ll calc(ll a, ll b, ll c) {
    return (b - a) * (c - b);
}

void solve() {
    int n; cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        set<int> ms;

        int min_v = nums[i];
        int max_v = nums[i];

        for (int j = i + 1; j < n; j++) {
            if (j - i + 1 >= 3) {
                max_v = nums[j];

                int s = (max_v + min_v) / 2;
                auto it = ms.lower_bound(s);

                ll cur = 0;
                if (it != ms.end()) {
                    cur = max(cur, calc(min_v, *it, max_v));
                }

                if (it != ms.begin()) {
                    cur = max(cur, calc(min_v, *prev(it), max_v));
                }

                if (it != ms.end() && next(it) != ms.end()) {
                    cur = max(cur, calc(min_v, *next(it), max_v));
                }

                sum += cur;
            }

            ms.insert(nums[j]);
        }
    }

    cout << sum << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

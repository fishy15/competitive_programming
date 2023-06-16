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

template<typename T>
T ckmax(T &a, T b) {
    return a = max(a, b);
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> prev_same(k, -1);
    vector<int> nums(n);
    vector<int> back(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        nums[i]--;

        back[i] = prev_same[nums[i]];
        prev_same[nums[i]] = i;
    }
    
    vector<int> cold(k), hot(k);
    for (int i = 0; i < k; i++) {
        cin >> cold[i];
    }

    for (int i = 0; i < k; i++) {
        cin >> hot[i];
    }

    // only_one[end][start of restricted range]
    // restriction is that segments cant cross into restriction, inside disjoint
    vector only_one(n + 1, vector<ll>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            only_one[i + 1][j] = only_one[i][j];
        }

        int ps = back[i];
        int diff = cold[nums[i]] - hot[nums[i]];
        if (ps != -1) {
            for (int j = ps; j <= i + 1; j++) {
                // create a new bound
                ckmax(only_one[i + 1][i + 1], only_one[ps+1][j] + diff);
            }

            for (int j = 0; j <= ps + 1; j++) {
                // within a restriction bound
                ckmax(only_one[i + 1][j], only_one[ps + 1][j] + diff);
            }
        }
    }

    ll ans = 0;
    for (auto &v : only_one) {
        ckmax(ans, *max_element(v.begin(), v.end()));
    }

    ans = -ans;
    for (int i = 0; i < n; i++) {
        ans += cold[nums[i]]; 
    }

    cout << ans << '\n';
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

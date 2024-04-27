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
    int n, k;
    cin >> n >> k;

    vector<int> nums;
    if (k == 1) {
        nums.push_back(3);
        for (int p = 1; p < 20; p++) {
            nums.push_back(1 << p);
        }
    } else {
        int p = 0;

        // from 1 to k-1
        while ((1 << (p + 1)) <= k) {
            nums.push_back(1 << p);    
            p++;
        }
    
        if (k & (k - 1)) {
            // if not a power of 2, add diff from last power of 2
            int v = k - (1 << p);
            if (v != 0) {
                nums.push_back(v);
            }
        }

        p++;

        // add k+1
        nums.push_back(k+1);

        // add power of 2 + k
        nums.push_back(k + (1 << p) - 1);

        while (p < 20) {
            nums.push_back(1 << p);
            p++;
        }
    }

    cout << nums.size() << '\n';
    for (auto x : nums) {
        cout << x << ' ';
    }
    cout << '\n';

    /*
    vector<bool> can_make(n + 1);
    int sz = nums.size();
    for (int m = 0; m < (1 << sz); m++) {
        int sum = 0;
        for (int i = 0; i < sz ;i++) {
            if (m & (1 << i)) {
                sum += nums[i];
            }
        }
        if (sum <= n) {
            can_make[sum] = true;
        }
    }

    for (int i = 0; i <= n; i++) {
        if (!can_make[i]) {
            cout << "dont work " << i << '\n';
        }
    }
    */
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

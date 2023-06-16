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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

void solve() {
    int m; cin >> m;
    vector<array<ll, 2>> nums(m);
    ll sum = 0;

    for (int i = 0; i < m; i++) {
        cin >> nums[i][0] >> nums[i][1];
        sum += nums[i][0] * nums[i][1];
    }

    sort(nums.begin(), nums.end());
    for (ll i = sum; i >= max(2LL, sum - 10000); i--) {
        auto nums2 = nums;
        ll cur = i;
        ll sum2 = sum;
        for (auto &p : nums2) {
            while (cur % p[0] == 0 && p[1] > 0) {
                cur /= p[0];
                p[1]--;
                sum2 -= p[0];
            }
        }

        if (cur == 1 && i == sum2) {
            cout << i << '\n'; 
            return;
        }
    }
        
    cout << "0\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

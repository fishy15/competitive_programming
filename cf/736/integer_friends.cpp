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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int lg[MAXN];

void solve() {
    int n; cin >> n;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    if (n == 1) {
        cout << "1\n";
        return;
    }

    vector<vector<ll>> diff(n - 1, vector<ll>(20));
    for (int i = 0; i < n - 1; i++) {
        if (nums[i] == nums[i + 1]) {
            diff[i][0] = nums[i];
        } else {
            diff[i][0] = abs(nums[i + 1] - nums[i]);
        }
    }
    
    for (int k = 1; k < 20; k++) {
        for (int i = 0; i + (1 << k) < n; i++) {
            diff[i][k] = gcd(diff[i][k - 1], diff[i + (1 << (k - 1))][k - 1]);
        }
    }

    auto qry = [&](int a, int b) {
        int k = lg[b - a + 1];
        return gcd(diff[a][k], diff[b - (1 << k) + 1][k]);
    };

    int res = 0;
    for (int i = 0; i < n - 1; i++) {
        int l = i;
        int r = n - 2;
        int ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (qry(i, m) != 1) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        if (ans != -1) {
            res = max(res, ans - i + 1);
        }
    }

    cout << res + 1 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    lg[1] = 0;
    for (int i = 2; i < MAXN; i++) {
        lg[i] = lg[i / 2] + 1;
    }

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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
    int n; cin >> n;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    if (n == 1) {
        cout << "0\n";
        return;
    }

    int ans = INF;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = nums[j] - nums[i];
            d /= j - i;
            double cur = nums[i] - d * i;
            int cnt = 0;

            for (int k = 0; k < n; k++) {
                if (fabs(nums[k] - cur) > eps) {
                    cnt++;
                }
                cur += d;
            }

            ans = min(ans, cnt);
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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
#define MAXN 1000000

using namespace std;

struct BIT {
    int n;
    vector<int> bit;
    BIT(int n) : n(n), bit(n + 1) {}
    
    void upd(int x, int v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    int qry(int x) {
        x++;
        int res = 0;
        while (x > 0) {
            res += bit[x];
            x -= x & -x;
        }
        return res;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vector<int> nums(n * m);

    for (int i = 0; i < n * m; i++) {
        cin >> nums[i];
    }

    vector<int> nums2 = nums;
    sort(nums2.begin(), nums2.end());
    map<int, int> loc;

    for (int i : nums2) {
        if (!loc.count(i)) {
            loc[i] = upper_bound(nums2.begin(), nums2.end(), i) - nums2.begin() - 1;
        }
    }

    BIT bit(m);
    ll ans = 0;
    for (int i : nums) {
        ans += bit.qry(loc[i]);
        bit.upd(loc[i], 1);
        loc[i]--;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

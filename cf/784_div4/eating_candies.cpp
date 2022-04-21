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
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    map<ll, int> a, b;

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        a[sum] = i + 1;
    }

    sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum += nums[i];
        b[sum] = n - i;
    }

    int ans = 0;
    for (auto [x, cnt] : a) {
        if (b.count(x)) {
            int res = cnt + b[x];
            if (res <= n) {
                ans = max(ans, cnt + b[x]);
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    while (n--) solve();

    return 0;
}

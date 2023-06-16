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

int check(int x, int y) {
    if (x > y) swap(x, y);
    int ans = 0;
    while (2 * x < y) {
        x *= 2;
        ans++;
        if (x > y) swap(x, y);
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans += check(nums[i], nums[i + 1]);
    }

    cout << ans << '\n';
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

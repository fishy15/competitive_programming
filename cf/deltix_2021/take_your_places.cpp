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

void solve() {
    int n; cin >> n;
    vector<int> nums(n);

    int cnt[2] = {0, 0};
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        cnt[nums[i] % 2]++;
    }

    if (abs(cnt[0] - cnt[1]) > 1) {
        cout << "-1\n";
        return;
    }

    int cnt2[2] = {0, 0};
    int first = cnt[0] >= cnt[1] ? 0 : 1;
    cnt2[0] = first == 0 ? 0 : 1;
    cnt2[1] = 1 - cnt2[0];

    vector<int> cur(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += max(0, i - cnt2[nums[i] % 2]);
        cnt2[nums[i] % 2] += 2;
    }

    if (cnt[0] == cnt[1]) {
        cnt2[0] = 1;
        cnt2[1] = 0;
        ll ans2 = 0;
        for (int i = 0; i < n; i++) {
            ans2 += max(0, i - cnt2[nums[i] % 2]);
            cnt2[nums[i] % 2] += 2;
        }
        ans = min(ans, ans2);
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

int n, k;
set<int> nums;
vector<vector<int>> lines;
ll dp[MAXN];
ll sum[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.insert(x);
    }

    while (!nums.empty()) {
        auto it = nums.begin();
        lines.push_back({*it});
        while (nums.count(*it + k)) {
            it = nums.find(*it + k);
            nums.erase(*it - k);
            lines.rbegin()->push_back(*it);
        }
        nums.erase(it);
    }

    dp[0] = 1;
    dp[1] = 1;
    sum[0] = 1;

    for (int i = 2; i < n + 10; i++) {
        dp[i] = sum[i - 2] + 1;
        if (dp[i] >= MOD) dp[i] -= MOD;
        sum[i - 1] = sum[i - 2] + dp[i - 1];
        if (sum[i - 1] >= MOD) sum[i - 1] -= MOD;
    }

    for (int i = 1; i < n + 10; i++) {
        sum[i] = sum[i - 1] + dp[i];
        if (sum[i] >= MOD) sum[i] -= MOD;
    }

    ll ans = 1;
    for (auto &v : lines) {
        int sz = (int)(v.size());
        ans *= sum[sz - 1] + 1;
        ans %= MOD;
    }

    ans--;
    if (ans < 0) ans += MOD;
    cout << ans << '\n';

    return 0;
}

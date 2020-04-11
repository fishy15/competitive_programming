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
#define MAXN 1000000

using namespace std;

int n, m, k;
int nums[MAXN + 1];
int off[MAXN + 1];
ll dp[2001];
ll pre[2011];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums, nums + n);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        off[a] = max(off[a], b);
    }

    for (int i = 0; i <= k; i++) {
        pre[i + 1] = pre[i] + nums[i];
    }

    for (int i = 1; i <= k; i++) {
        dp[i] = dp[i - 1] + nums[i - 1];

        for (int j = 1; j <= i; j++) {
            int dd = j - off[j];
            ll v = dp[i - j] + pre[i] - pre[i - dd];
            dp[i] = min(dp[i], v);
        }
    }

    cout << dp[k] << '\n';

    return 0;
}

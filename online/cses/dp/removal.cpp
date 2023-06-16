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
#define MAXN 5000

int n;
int nums[MAXN];
ll dp[MAXN][MAXN];
ll pre[MAXN + 1];
bool vis[MAXN][MAXN];

using namespace std;

ll sum(int l, int r) {
    return pre[r + 1] - pre[l];
}

ll solve(int l, int r) {
    if (vis[l][r]) return dp[l][r];
    vis[l][r] = true;
    if (l == r) return dp[l][r] = nums[l];
    return dp[l][r] = max(nums[l] + sum(l + 1, r) - solve(l + 1, r), nums[r] + sum(l, r - 1) - solve(l, r - 1));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + nums[i - 1];
    }

    cout << solve(0, n - 1) << '\n';

    return 0;
}

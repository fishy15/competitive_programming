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
#define MAXN 1000010

using namespace std;

int n, k;
ll nums[MAXN];
ll dp[2 * MAXN];

ll &ckmax(ll &a, ll b) {
    return a = max(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i <= 2 * n; i++) {
        if (i > 0) ckmax(dp[i], dp[i - 1]);
        if (i < n) {
            ckmax(dp[i + k + 1], dp[i] + nums[i]);
            ckmax(dp[i + k / 2 + 1], dp[i] + nums[i] / 2);
        }
    }

    cout << dp[2 * n] << '\n';

    return 0;
}

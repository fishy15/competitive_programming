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
#define MAXN 410

using namespace std;

int n;
int nums[MAXN];
ll dp[MAXN][MAXN];

ll g(int i, int j) {
    if (i == 0) return nums[j];
    return nums[j] - nums[i - 1];
}

ll get(int i, int j) {
    if (j < i) return -1;
    if (dp[i][j]) return dp[i][j];
    // split into two equal
    for (int m = i; m < j; m++) {
        ll res1 = get(i, m);
        ll res2 = get(m + 1, j);
        if (res1 != -1 && res2 != -1 && res1 == res2) {
            return dp[i][j] = res1 + res2;
        }
    }

    // split with one in middle
    int m2 = j;
    for (int m = i; m < j; m++) {
        while (g(i, m) > g(m2, j) && m + 1 < m2) m2--;
        if (g(i, m) == g(m2, j)) {
            ll res1 = get(i, m);
            ll res2 = get(m2, j);
            ll res3 = get(m + 1, m2 - 1);
            if (res1 != -1 && res2 != -1 && res3 != -1) {
                return dp[i][j] = res1 + res2 + res3;
            }
        }
    }

    return dp[i][j] = -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        dp[i][i] = nums[i];
    }

    for (int i = 1; i < n; i++) {
        nums[i] += nums[i - 1];
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ans = max(ans, get(i, j));
        }
    }

    cout << ans << '\n';

    return 0;
}

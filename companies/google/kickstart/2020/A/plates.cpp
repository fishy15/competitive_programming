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
#define MAXN 1000

using namespace std;

// dp[pos][used]
int dp[100][3001];

void solve() {
    int n, k, p; cin >> n >> k >> p;
    vector<vector<int>> stacks;

    // reset
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j <= 3000; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        vector<int> cur;
        for (int j = 0; j < k; j++) {
            int x; cin >> x;
            cur.push_back(x);
        }
        stacks.push_back(cur);
    }

    for (int i = 0; i < n; i++) {
        int cur = 0;
        if (i > 0) {
            for (int j = 0; j < 3000; j++) {
                dp[i][j] = dp[i - 1][j];
            }
        }
        for (int j = 0; j < k; j++) {
            cur += stacks[i][j];
            if (i == 0) {
                dp[i][j + 1] = cur;
            } else {
                for (int a = j + 1; a <= 3000; a++) {
                    if (dp[i - 1][a - j - 1]) {
                        dp[i][a] = max(dp[i][a], dp[i - 1][a - j - 1] + cur);
                    }
                }
            }
        }
    }

    cout << dp[n - 1][p];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
        cout << '\n';
    }

    return 0;
}

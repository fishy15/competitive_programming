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
#define MAXN 200010

using namespace std;

int n;
vector<ll> loc[MAXN];
ll mm[MAXN][2];
ll dp[MAXN][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, c; cin >> x >> c;
        loc[c].push_back(x);
    }

    for (int i = 1; i <= n; i++) {
        if (!loc[i].empty()) {
            sort(loc[i].begin(), loc[i].end());
            mm[i][0] = *loc[i].begin();
            mm[i][1] = loc[i].back();
        }
    }

    for (int i = 1; i <= n; i++) {
        if (loc[i].empty()) {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = dp[i - 1][1];
            mm[i][0] = mm[i - 1][0];
            mm[i][1] = mm[i - 1][1];
        } else {
            ll diff = mm[i][1] - mm[i][0];
            dp[i][0] = min(dp[i - 1][0] + abs(mm[i - 1][0] - mm[i][1]), 
                dp[i - 1][1] + abs(mm[i - 1][1] - mm[i][1])) + diff;

            dp[i][1] = min(dp[i - 1][0] + abs(mm[i - 1][0] - mm[i][0]), 
                dp[i - 1][1] + abs(mm[i - 1][1] - mm[i][0])) + diff;
        }
    }

    cout << min(dp[n][0] + abs(mm[n][0]), dp[n][1] + abs(mm[n][1])) << '\n';

    return 0;
}

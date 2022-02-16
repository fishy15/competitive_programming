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
#define MAXN 210

using namespace std;

int n;
ll val[MAXN];
ll pre[MAXN];
ll dp[MAXN][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + val[i];
    }

    for (int e = 0; e < n; e++) {
        for (int s = e; s >= 0; s--) {
            if (e == s) {
                dp[s][e] = 0;
            } else {
                dp[s][e] = INFLL;
                for (int i = s; i < e; i++) {
                    dp[s][e] = min(dp[s][e], dp[s][i] + dp[i + 1][e] + pre[e + 1] - pre[s]);
                }
            }
        }
    }

    cout << dp[0][n - 1] << '\n';

    return 0;
}

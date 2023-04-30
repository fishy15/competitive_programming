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
#include <functional>
#include <numeric>
#include <bitset>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n;
ld prob[17][17];
ld dp[1 << 17];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> prob[i][j];
        }
    }

    int end = (1 << n) - 1;
    dp[end] = 1;

    for (int m = end; m > 0; m--) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (m & (1 << i)) {
                cnt++;
            }
        }

        if (cnt == 1) continue;

        int div = cnt * (cnt - 1) / 2;

        for (int i = 0; i < n; i++) {
            if (m & (1 << i)) {
                for (int j = i + 1; j < n; j++) {
                    if (m & (1 << j)) {
                        dp[m ^ (1 << j)] += dp[m] * prob[i][j] / div;
                        dp[m ^ (1 << i)] += dp[m] * prob[j][i] / div;
                    }
                }
            }
        }
    }

    cout << fixed << setprecision(10);
    for (int i = 0; i < n; i++) {
        cout << dp[1 << i] << '\n';
    }

    return 0;
}

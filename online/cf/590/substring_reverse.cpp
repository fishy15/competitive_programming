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
string s;

int ok[1 << 20];
int dp[1 << 20];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    n = s.size();

    for (int i = 0; i < n; i++) {
        int m = 0;
        for (int j = 1; j <= 20 && i + j <= n; j++) {
            int c = s[i + j - 1] - 'a';
            if ((m >> c) & 1) break;
            m ^= 1 << c;
            dp[m] = j;
            ok[m] = j;
        }
    }

    for (int m = 0; m < (1 << 20); m++) {
        for (int j = 0; j < 20; j++) {
            if ((m >> j) & 1) {
                int m2 = m ^ (1 << j);
                dp[m] = max(dp[m], dp[m2]);
            }
        }
    }

    int ans = 0;
    int all = (1 << 20) - 1;
    for (int i = 0; i < (1 << 20); i++) {
        if (ok[i] > 0) {
            ans = max(ans, ok[i] + dp[all ^ i]);
        }
    }

    cout << ans << '\n';

    return 0;
}

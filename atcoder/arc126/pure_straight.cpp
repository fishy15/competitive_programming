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
#define MAXN 210
#define MAXK 16

using namespace std;

int n, k;
int nums[MAXN];
ll dp[MAXN][1 << MAXK];

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

int rel_median(int m, int i) {
    int cnt = 0;
    for (int i = 0; i < k; i++) {
        if (m & (1 << i)) cnt++;
    }

    if (cnt < k / 2) {
        return -i - (k / 2 - cnt);
    } else if (k % 2 == 1 && cnt == k / 2) {
        return 0;
    } else {
        return i - (cnt - k / 2);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        nums[i]--;
    }

    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        int c = nums[i];
        for (int m = 0; m < (1 << k); m++) {
            ckmin(dp[i + 1][m], dp[i][m]);

            if (!(m & (1 << c))) {
                // calculate inversion
                int inv = 0;
                for (int j = c + 1; j < k; j++) {
                    if (m & (1 << j)) inv++;
                }

                ckmin(dp[i + 1][m ^ (1 << c)], dp[i][m] + inv + rel_median(m, i));
            }
        }
    }

    cout << dp[n][(1 << k) - 1] << '\n';

    return 0;
}

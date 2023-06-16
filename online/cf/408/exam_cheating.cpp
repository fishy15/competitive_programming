/*
 * We can use dynamic programming, with the states dp[n][p][k][k]. The first number represents the index
 * of the problem, the second index is how many times we have peeked, the third index is how many questions
 * can we look at ahead for person A, and the fourth index is how many questions we can look at ahead for
 * person B. For the transitions, we consider the cases where we start a new peek at only A, only B, both, 
 * or neither. We note that there the peek intervals should not overlap for different people. This DP can
 * be solved in O(npk^2) time, which is unfortunately too slow. However, we won't need more than 
 * 2 * ceil(n / k) peeks, so setting p = 2 * ceil(n / k) gives us a time complexity of O(n(n / k)k^2)
 * = O(n^2k), which is fine.
 */
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
#define MAXN 1000000

using namespace std;

int n, p, k;
int r, s;
int dp[2][1010][55][55];
bool has_a[1010];
bool has_b[1010];

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

int get_val(int orig, int idx, int a, int b) {
    if (orig == -1) return -1;
    if ((has_a[idx] && a > 0) || (has_b[idx] && b > 0)) orig++;
    return orig;
}

int dec(int x) {
    return max(0, x - 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> p >> k;

    cin >> r;
    for (int i = 0; i < r; i++) {
        int x; cin >> x;
        x--;
        has_a[x] = true;
    }

    cin >> s;
    for (int i = 0; i < s; i++) {
        int x; cin >> x;
        x--;
        has_b[x] = true;
    }

    p = ckmin(p, 2 * (n + k - 1) / k);

    for (int j = 0; j <= p; j++) {
        for (int a = 0; a < k; a++) {
            for (int b = 0; b < k; b++) {
                dp[0][j][a][b] = -1;
            }
        }
    }

    dp[0][0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        int cur = i & 1;
        int nxt = cur ^ 1;

        // reset row
        for (int j = 0; j <= p; j++) {
            for (int a = 0; a < k; a++) {
                for (int b = 0; b < k; b++) {
                    dp[nxt][j][a][b] = -1;
                }
            }
        }

        // start a new segment for A
        for (int j = 0; j < p; j++) {
            for (int b = 0; b < k; b++) {
                ckmax(dp[nxt][j + 1][k - 1][dec(b)], get_val(dp[cur][j][0][b], i, k, b));
            }
        }

        // start a new segment for B
        for (int j = 0; j < p; j++) {
            for (int a = 0; a < k; a++) {
                ckmax(dp[nxt][j + 1][dec(a)][k - 1], get_val(dp[cur][j][a][0], i, a, k));
            }
        }

        // start a new segment for both
        for (int j = 0; j < p - 1; j++) {
            ckmax(dp[nxt][j + 2][k - 1][k - 1], get_val(dp[cur][j][0][0], i, k, k));
        }

        // don't start anything
        for (int j = 0; j <= p; j++) {
            for (int a = 0; a < k; a++) {
                for (int b = 0; b < k; b++) {
                    ckmax(dp[nxt][j][dec(a)][dec(b)], get_val(dp[cur][j][a][b], i, a, b));
                }
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= p; j++) {
        for (int a = 0; a < k; a++) {
            for (int b = 0; b < k; b++) {
                ckmax(ans, dp[n & 1][j][a][b]);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}

/*
 * Because of the condition that each rectangle must be adjacent to a side, there must be a 
 * line that goes from one end to another (this is true of subrectangles as well).
 * Therefore, we can try splitting the rectangle on various lines and solve for each 
 * subrectangle independently using DP, maintaining which sides we can place windows on.
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
#define MAXN 610

using namespace std;

ll n, m, k;
ll best[MAXN][MAXN][16];

ll ckmin(ll &a, ll b) {
    return a = min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;

    for (int sum = 0; sum <= n + m; sum++) {
        for (int x = 0; x <= sum; x++) {
            int y = sum - x;
            if (x > n || y > m) continue;
            for (int open = 0; open < 16; open++) {
                if (x > 0 && y > 0) {
                    best[x][y][open] = INFLL;
                    int up = open & 1;
                    int down = open & 2;
                    int left = open & 4;
                    int right = open & 8;

                    int sw = 2 * up + 1 * down + 8 * left + 4 * right;
                    if (open > sw) {
                        best[x][y][open] = best[x][y][sw];
                    } else {
                        if (up || down || (left && right)) {
                            for (int i = 1; i < x; i++) {
                                ckmin(best[x][y][open], best[i][y][open - right] + best[x - i][y][open - left]);
                            }
                        }

                        if (left || right || (up && down)) {
                            for (int i = 1; i < y; i++) {
                                ckmin(best[x][y][open], best[x][i][open - down] + best[x][y - i][open - up]);
                            }
                        }

                        if (open) {
                            ckmin(best[x][y][open], (x * y - k) * (x * y - k));
                        }

                        ckmin(best[x][y][open], INFLL);
                    }
                }
            }
        }
    }

    cout << best[n][m][15] << '\n';

    return 0;
}

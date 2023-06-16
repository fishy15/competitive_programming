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
#define MAXN 1000000

using namespace std;

int k;
long double cur[8][8][8][8];
long double nxt[8][8][8][8];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> k;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cur[i][j][i][j] = 1;
        }
    }

    for (int z = 0; z < k; z++) {
        // orig pos loop
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                // new pos loop
                for (int a = 0; a < 8; a++) {
                    for (int b = 0; b < 8; b++) {
                        int cnt = 4;
                        if (a == 0 || a == 7) cnt--;
                        if (b == 0 || b == 7) cnt--;
                        if (a) nxt[i][j][a - 1][b] += cur[i][j][a][b] / cnt;
                        if (a < 7) nxt[i][j][a + 1][b] += cur[i][j][a][b] / cnt;
                        if (b) nxt[i][j][a][b - 1] += cur[i][j][a][b] / cnt;
                        if (b < 7) nxt[i][j][a][b + 1] += cur[i][j][a][b] / cnt;
                    }
                }
            }
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (int a = 0; a < 8; a++) {
                    for (int b = 0; b < 8; b++) {
                        cur[i][j][a][b] = nxt[i][j][a][b];
                        nxt[i][j][a][b] = 0;
                    }
                }
            }
        }
    }

    long double ans = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            long double val = 1;
            for (int a = 0; a < 8; a++) {
                for (int b = 0; b < 8; b++) {
                    val *= 1 - cur[a][b][i][j];
                }
            }
            ans += val;
        }
    }

    cout << fixed << setprecision(6) << ans << '\n';

    return 0;
}

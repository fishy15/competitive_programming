// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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

int n, m;
string s, t;
int dp[3001][3001][4];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> s >> t;
    n = (int)(s.size());
    m = (int)(t.size());

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j][0] = dp[i - 1][j - 1][0] + 1;
                dp[i][j][1] = i - 1;
                dp[i][j][2] = j - 1;
                dp[i][j][3] = 1;
            } 

            if (dp[i - 1][j][0] > dp[i][j - 1][0]) {
                if (dp[i - 1][j][0] > dp[i][j][0]) {
                    dp[i][j][0] = dp[i - 1][j][0];
                    dp[i][j][1] = i - 1;
                    dp[i][j][2] = j;
                    dp[i][j][3] = 0;
                }
            } else {
                if (dp[i][j - 1][0] > dp[i][j][0]) {
                    dp[i][j][0] = dp[i][j - 1][0];
                    dp[i][j][1] = i;
                    dp[i][j][2] = j - 1;
                    dp[i][j][3] = 0;
                }
            }
        }
    }

    string ans = "";

    int curX = n;
    int curY = m;

    while (curX > 0 || curY > 0) {
        if (dp[curX][curY][3]) {
            ans += s[curX - 1];
        }

        //cout << "\t" << curX << ' ' << curY << '\n';
        //cout << "\t[" << dp[curX][curY][0] << ' ' << dp[curX][curY][1] << ' ' << dp[curX][curY][2] << ' ' << dp[curX][curY][3] << "] \n";
        int nextX, nextY;
        nextX = dp[curX][curY][1];
        nextY = dp[curX][curY][2];
        curX = nextX;
        curY = nextY;

        //cout << curX << ' ' << curY << '\n';
        //cout << "[" << dp[curX][curY][0] << ' ' << dp[curX][curY][1] << ' ' << dp[curX][curY][2] << ' ' << dp[curX][curY][3] << "] ";
    }

    /* for (int i = 0; i <= 4; i++) { */
    /*     for (int j = 0; j <= 4; j++) { */
    /*         cout << "[" << dp[j][i][0] << ' ' << dp[j][i][1] << ' ' << dp[j][i][2] << ' ' << dp[j][i][3] << "] "; */
    /*     } */
    /*     cout << '\n'; */
    /* } */

    for (int i = (int)(ans.size()) - 1; i >= 0; i--) {
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}

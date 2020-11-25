/*
 * Let dp[r][g][y][3] store the minimum number of moves needed to create a proper subsequence of 
 * r Rs, g Gs, and y Ys, and the last index marks which letter is the last letter of the prefix. To 
 * transition, we can calculate the number of swaps needed to bring an R, G, or Y to the front of the prefix.
 * We can then include this cost with the minimum cost to get to a valid previous state (preventing two of
 * the same color from being next to each other).
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
#define MAXN 410

using namespace std;

int n;
string s;
bool vis[MAXN][MAXN][MAXN][3];
int dp[MAXN][MAXN][MAXN][3];
int pref[MAXN][3];
vector<int> idx[3];

int ckmin(int &a, int b) {
    return a = min(a, b);
}

// so far have r, g, y for each color
// and last char is last
int solve(int r, int g, int y, int last) {
    if (r < 0 || g < 0 || y < 0) return INF;
    if (vis[r][g][y][last]) return dp[r][g][y][last];
    vis[r][g][y][last] = true;
    dp[r][g][y][last] = INF;
    if (r == 0 && g == 0 && y == 0) return dp[r][g][y][last] = 0;

    int pr = r;
    int pg = g;
    int py = y;

    if (last == 0) pr--;
    else if (last == 1) pg--;
    else py--;

    if (pr < 0 || pg < 0 || py < 0) return dp[r][g][y][last];

    int to_move = pr + pg + py;
    if (last == 0) {
        int cur = idx[0][r - 1];
        to_move = cur - to_move;
        to_move += max(0, g - pref[cur][1]);
        to_move += max(0, y - pref[cur][2]);
    } else if (last == 1) {
        int cur = idx[1][g - 1];
        to_move = cur - to_move;
        to_move += max(0, r - pref[cur][0]);
        to_move += max(0, y - pref[cur][2]);
    } else {
        int cur = idx[2][y - 1];
        to_move = cur - to_move;
        to_move += max(0, r - pref[cur][0]);
        to_move += max(0, g - pref[cur][1]);
    }

    for (int i = 0; i < 3; i++) {
        if (i == last) continue;
        ckmin(dp[r][g][y][last], solve(pr, pg, py, i) + to_move);
    }

    return dp[r][g][y][last];
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    cin >> n;
    cin >> s;

    for (int i = 0; i < n; i++) {
        if (i) {
            pref[i][0] = pref[i - 1][0];
            pref[i][1] = pref[i - 1][1];
            pref[i][2] = pref[i - 1][2];
        }
        switch (s[i]) {
            case 'R': 
                pref[i][0]++; 
                idx[0].push_back(i); 
                break;
            case 'G': 
                pref[i][1]++; 
                idx[1].push_back(i); 
                break;
            case 'Y': 
                pref[i][2]++; 
                idx[2].push_back(i); 
                break;
        }
    }

    int r = pref[n - 1][0];
    int g = pref[n - 1][1];
    int y = pref[n - 1][2];

    int ans = min({solve(r, g, y, 0), solve(r, g, y, 1), solve(r, g, y, 2)});
    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}

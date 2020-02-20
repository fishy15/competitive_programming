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
#define MAXN 1000

using namespace std;

struct rect {
    int x1, x2, y1, y2;
};

int n;
int grid[MAXN][MAXN];
int dp[MAXN + 1][MAXN + 1];
rect r[MAXN * MAXN + 1];

int main() {
    ifstream fin("art.in");
    ofstream fout("art.out");

    fin >> n;

    for (int i = 1; i <= n * n; i++) {
        r[i].x1 = INF;
        r[i].y1 = INF;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> grid[i][j];
            if (grid[i][j] != 0) {
                int num = grid[i][j];
                r[num].x1 = min(r[num].x1, i);
                r[num].x2 = max(r[num].x2, i);
                r[num].y1 = min(r[num].y1, j);
                r[num].y2 = max(r[num].y2, j);
            }
        }
    }

    int cnt = 0;

    for (int i = 1; i <= n*n; i++) {
        if (r[i].x1 != INF) {
            cnt++;
            dp[r[i].x1][r[i].y1]++;
            dp[r[i].x1][r[i].y2 + 1]--;
            dp[r[i].x2 + 1][r[i].y1]--;
            dp[r[i].x2 + 1][r[i].y2 + 1]++;
        }
    } 

    set<int> bad;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }

            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }

            if (i > 0 && j > 0) {
                dp[i][j] -= dp[i - 1][j - 1];
            }

            if (dp[i][j] > 1 && grid[i][j] != 0) {
                bad.insert(grid[i][j]);
            }
        }
    }    

    if (bad.empty() && cnt == 1) {
        fout << n * n - 1 << '\n';
    } else {
        fout << n * n - (int)(bad.size()) << '\n';
    }

    return 0;
}

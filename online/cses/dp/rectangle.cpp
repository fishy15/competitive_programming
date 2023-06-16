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

int n, m;
int dp[501][501];

int calc(int x, int y) {
    if (x == y) return 0;
    if (dp[x][y]) return dp[x][y];
    if (dp[y][x]) return dp[y][x];

    dp[x][y] = INF;
    for (int i = 1; i < x; i++) {
        dp[x][y] = min(dp[x][y], calc(i, y) + calc(x - i, y) + 1);
    }

    for (int i = 1; i < y; i++) {
        dp[x][y] = min(dp[x][y], calc(x, i) + calc(x, y - i) + 1);
    }

    return dp[x][y];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    cout << calc(n, m) << '\n';

    return 0;
}

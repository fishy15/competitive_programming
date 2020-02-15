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

int n, m, c;
int mon[MAXN];
int dp[MAXN + 1][MAXN];
vector<int> p[MAXN];

int main() {
    ifstream fin("time.in");
    ofstream fout("time.out");

    fin >> n >> m >> c;

    for (int i = 0; i < n; i++) {
        fin >> mon[i];
    }

    for (int i = 0; i < m; i++) {
        int a, b; fin >> a >> b;
        a--; b--;
        p[b].push_back(a);
    }

    for (int i = 0; i <= MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;

    for (int t = 1; t <= MAXN; t++) {
        for (int i = 0; i < n; i++) {
            int val = -1;

            for (int x : p[i]) {
                val = max(val, dp[t - 1][x]);
            }

            if (val != -1) {
                dp[t][i] = val + mon[i];
            }
        }
    }

    int ans = 0;
    for (int t = 0; t <= MAXN; t++) {
        int val = dp[t][0] - c * t * t;
        ans = max(ans, val);
    }

    fout << ans << '\n';

    return 0;
}

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
#define MAXN 310

using namespace std;

int n, m;
ll cows[MAXN][MAXN];
ll dp[MAXN][MAXN];

int main() {
    ifstream fin("pieaters.in");
    ofstream fout("pieaters.out");

    fin >> n >> m;
    for (int i = 0; i < n; i++) {
        ll w; int a, b;
        fin >> w >> a >> b;
        cows[a][b] = max(cows[a][b], w);
    }

    for (int sz = 0; sz <= m; sz++) {
        for (int l = 0; l <= m; l++) {
            int r = l + sz;
            if (r <= m) {
                int prev = 0;
                if (sz > 0) {
                    prev = max(dp[l + 1][r], dp[l][r - 1]);
                }
                
                dp[l][r] = prev + cows[l][r];
            }
        }
    }

    fout << dp[0][m] << '\n';

    return 0;
}

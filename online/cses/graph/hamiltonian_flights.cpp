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
int edge[20][20];
ll dp[1<<20][20];
int q;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        edge[a][b]++;
    }
    
    q = 1 << n;
    dp[1][0] = 1;

    for (int i = 2; i < q; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (!(i & 1 << j)) continue;
            for (int k = j + 1; k < n; k++) {
                if (!(i & (1 << k))) continue;
                int mask = i - (1 << j);
                dp[i][j] += dp[mask][k] * edge[k][j];
                dp[i][j] %= MOD;
                swap(j, k);
                mask = i - (1 << j);
                dp[i][j] += dp[mask][k] * edge[k][j];
                dp[i][j] %= MOD;
                swap(j, k);
            }
        }
    }

    cout << dp[q - 1][n - 1] << '\n';

    return 0;
}

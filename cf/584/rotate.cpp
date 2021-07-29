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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> grid(m, vector<int>(n + 1));
    vector<int> pp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[j][i];
            grid[j][n] = max(grid[j][n], grid[j][i]);
        }
    }

    for (int i = 0; i < m; i++) pp.push_back(i);

    sort(pp.begin(), pp.end(), [n, &grid](const int a, const int b) {
        return grid[a][n] > grid[b][n];
    });

    m = min(m, n);

    vector<ll> dp(1 << n);
    for (int i = 0; i < m; i++) {
        vector<ll> dp2(1 << n);
        vector<ll> calc(1 << n);
        auto &curcol = grid[pp[i]];
        for (int st = 0; st < n; st++) {
            for (int j = 1; j < (1 << n); j++) {
                int k = 0;
                while (!((1 << k) & j)) k++;
                int p = st + k;
                if (p >= n) p -= n;
                calc[j] = calc[j - (1 << k)] + curcol[p];
            }
            for (int j = 0; j < (1 << n); j++) {
                if (!(j & 1)) continue;
                for (int k = j;; k = (k - 1) & j) {
                    int add = j - k;
                    dp2[j] = max(dp2[j], dp[k] + calc[add]);
                    if (k == 0) break;
                }
            }
        }
        swap(dp, dp2);
    }
    cout << dp[(1 << n) - 1] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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
#include <functional>
#include <numeric>

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
    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<vector<int>> psum_row(n, vector<int>(m + 1));
    vector<vector<int>> psum_col(m, vector<int>(n + 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            psum_row[i][j + 1] = psum_row[i][j] + (grid[i][j] - '0');
            psum_col[j][i + 1] = psum_col[j][i] + (grid[i][j] - '0');
        }
    }

    int ans = INF;
    for (int i = 0; i < n; i++) {
        for (int j = i + 4; j < n; j++) {
            vector<int> before_sum(m);
            vector<int> after_sum(m);

            int mid_sum = 0;

            for (int k = 0; k < m; k++) {
                int between = psum_col[k][j] - psum_col[k][i + 1];

                after_sum[k] 
                    = (j - i - 1 - between) 
                    + mid_sum 
                    + (k - psum_row[i][k]) 
                    + (k - psum_row[j][k]);

                mid_sum += between;

                before_sum[k] 
                    = (j - i - 1 - between) 
                    - mid_sum 
                    - (k + 1 - psum_row[i][k + 1])
                    - (k + 1 - psum_row[j][k + 1]);
            }

            int min_before = before_sum[0];
            for (int k = 0; k < m - 3; k++) {
                min_before = min(min_before, before_sum[k]);
                ans = min(ans, min_before + after_sum[k + 3]);
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

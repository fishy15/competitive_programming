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
#define MAXN 50

using namespace std;

int n;
vector<int> nums;

// l r lo hi
int dp[MAXN][MAXN][MAXN][MAXN];

int main() {
    ifstream fin("subrev.in");
    ofstream fout("subrev.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        x--;
        nums.push_back(x);
        dp[i][i][x][x] = 1;
    }

    for (int i = 0; i < n - 1; i++) {
        int a = min(nums[i], nums[i + 1]);
        int b = max(nums[i], nums[i + 1]);
        dp[i][i + 1][a][b] = 2;
    }

    for (int sz = 0; sz < n; sz++) {
        for (int l = 0; l < n; l++) {
            int r = l + sz;
            if (r >= n) break;
            for (int diff = 0; diff < 50; diff++) {
                for (int lo = 0; lo < 50; lo++) {
                    int hi = lo + diff;
                    if (hi >= 50) break;
                    if (sz >= 1) {
                        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], dp[l + 1][r][lo][hi]); 
                        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], dp[l][r - 1][lo][hi]); 
                    }

                    if (lo < hi) {
                        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], dp[l][r][lo + 1][hi]);
                        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], dp[l][r][lo][hi - 1]);
                    }

                    if (lo == nums[l] && sz >= 1) {
                        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], dp[l + 1][r][lo][hi] + 1);
                        /* cout << dp[l + 1][r][lo][hi] + 1 << '\n'; */
                    }

                    if (hi == nums[r] && sz >= 1) {
                        /* cout << dp[l][r - 1][lo][hi] + 1 << '\n'; */
                        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], dp[l][r - 1][lo][hi] + 1);
                    }

                    int a = min(nums[l], nums[r]);
                    int b = max(nums[l], nums[r]);

                    if (lo == a && hi == b && sz >= 2) {
                        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], dp[l + 1][r - 1][lo][hi] + 2);
                    } else if ((lo == a || hi == b) && sz >= 2) {
                        dp[l][r][lo][hi] = max(dp[l][r][lo][hi], dp[l + 1][r - 1][lo][hi] + 1);
                    }

                    if (dp[l][r][lo][hi] > r - l + 1) {
                        dp[l][r][lo][hi] = r - l + 1;
                    }
                    
                    if (dp[l][r][lo][hi] > 13) cout << l << ' ' << r << ' ' << lo << ' ' << hi << ' ' << dp[l][r][lo][hi] << '\n'; 
                }
            }
        }
    }

    cout << dp[0][n - 1][0][49] << '\n';

    return 0;
}

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

int dp[510][510][510][2];

int &ckmin(int &a, int b) {
    return a = min(a, b);
}

void solve() {
    int n; cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int max_v = *max_element(v.begin(), v.end());

    // reset
    for (int i = 0; i < n; i++) {
        for (int a = 1; a <= max_v; a++) {
            for (int b = 1; b <= max_v; b++) {
                dp[i][a][b][0] = INF;
                dp[i][a][b][1] = INF;
            }
        }
    }

    // transition from 0 to i
    for (int i = 1; i < n; i++) {
        int new_max = i - v[0];
        if (new_max <= 0 || new_max > max_v) continue;
        if (v[i] == new_max) {
            dp[i][min(v[0], v[i])][new_max][1] = 1;
        } else if (v[i] < new_max) {
            dp[i][min(v[0], v[i])][new_max][0] = 1;
        }
    }

    // solve for the rest
    for (int i = 1; i < n; i++) {
        for (int a = 1; a <= max_v; a++) {
            for (int b = 1; b <= max_v; b++) {
                for (int j = i + 1; j < n; j++) {
                    int max_needed = (j - i) - a;
                    if (max_needed <= 0 || max_needed > max_v) continue;
                    
                    if (dp[i][a][b][0] != INF) {
                        int moves = dp[i][a][b][0] + 1;
                        if (max_needed == b) {
                            if (v[j] == b) {
                                ckmin(dp[j][min(a, v[j])][b][1], moves);
                            } else if (v[j] < b) {
                                ckmin(dp[j][min(a, v[j])][b][0], moves);
                            }
                        }
                    }

                    if (dp[i][a][b][1] != INF) {
                        int moves = dp[i][a][b][1] + 1;
                        if (max_needed <= b) {
                            if (v[j] == max_needed) {
                                ckmin(dp[j][min(a, v[j])][max_needed][1], moves);
                            } else if (v[j] < max_needed) {
                                ckmin(dp[j][min(a, v[j])][max_needed][0], moves);
                            }
                        }
                    }
                }
            }
        }
    }

    int ans = INF;
    for (int a = 1; a <= max_v; a++) {
        for (int b = 1; b <= max_v; b++) {
            ckmin(ans, dp[n - 1][a][b][1]);
        }
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

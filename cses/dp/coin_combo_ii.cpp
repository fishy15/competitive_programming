#include <iostream>
#include <fstream>
#include <vector>
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

int n, x;
vector<int> coins;
int dp[MAXN + 1];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> x;

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        int c; cin >> c;
        coins.push_back(c);
    }

    for (int& c : coins) {
        for (int i = 1; i <= x; i++) {
            if (i - c >= 0) {
                dp[i] += dp[i - c];

                if (dp[i] >= MOD) {
                    dp[i] -= MOD;
                }
            }
        }
    }

    cout << dp[x] << '\n';
    return 0;
}

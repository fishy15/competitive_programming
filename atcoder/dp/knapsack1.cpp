// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstring>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100

using namespace std;

int v[MAXN];
int w[MAXN];
ll dp[100001];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n, w_max; cin >> n >> w_max;

    memset(dp, 0x3f, 800008);

    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
    }

    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = w[i]; j <= w_max; j++) {
            if (dp[j - w[i]] < INFLL) {
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }
    }

    for (int i = 1; i <= w_max; i++) {
        if (dp[i] == INFLL) dp[i] = 0;
        dp[i] = max(dp[i], dp[i - 1]);
    }

    cout << dp[w_max] << '\n';

    return 0;
}

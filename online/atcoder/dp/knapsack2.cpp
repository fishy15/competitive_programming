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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, w;
ll dp[100001];
vector<array<int, 2>> vals;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> w;
    vals = vector<array<int, 2>>(n);

    for (int i = 0; i < n; i++) {
        cin >> vals[i][0] >> vals[i][1];
    }

    for (int i = 0; i <= 100000; i++) {
        dp[i] = INF;
    }

    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 100000; j >= vals[i][1]; j--) {
            dp[j] = min(dp[j], dp[j - vals[i][1]] + vals[i][0]);
        }
    }

    int ans = 0;

    for (int i = 0; i <= 100000; i++) {
        if (dp[i] <= w) {
            ans = max(ans, i);
        }
    }

    cout << ans << '\n';

    return 0;
}

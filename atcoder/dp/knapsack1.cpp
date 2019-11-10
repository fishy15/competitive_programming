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

    for (int i = 0; i < n; i++) {
        for (int j = w; j >= vals[i][0]; j--) {
            dp[j] = max(dp[j], dp[j - vals[i][0]] + vals[i][1]);
        }
    }

    for (int i = 1; i <= w; i++) {
        dp[i] = max(dp[i], dp[i - 1]);
    }

    cout << dp[w] << '\n';

    return 0;
}

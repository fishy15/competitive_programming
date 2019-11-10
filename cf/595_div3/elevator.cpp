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
#define MAXN 200000

using namespace std;

int n, c; 
vector<int> a;
vector<int> b;

ll dp[MAXN][2];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> c;

    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        a.push_back(x);
    }

    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        b.push_back(x);
    }

    dp[0][1] = c;

    for (int i = 1; i < n; i++) {
        dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + a[i - 1];
        dp[i][1] = min(dp[i - 1][0] + c, dp[i - 1][1]) + b[i - 1];
    }

    for (int i = 0; i < n; i++) {
        cout << min(dp[i][0], dp[i][1]) << ' ';
    }

    cout << '\n';

    return 0;
}

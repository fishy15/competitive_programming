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
#define MAXN 300000

using namespace std;

int n, k;
ll arr[MAXN];
ll diff[MAXN];
int slen;

ll dp[5001][5001];

ll solve(int a, int b) {
    if ((!a && !b) || a < 0 || b < 0) return 0;
    if (dp[a][b]) return dp[a][b];

    ll v1 = 0, v2 = 0;
    if (a > 0) {
        if (dp[a - 1][b]) v1 = dp[a - 1][b];
        else v1 = solve(a - 1, b);
    }
    if (b > 0) {
        if (dp[a][b - 1]) v2 = dp[a][b - 1];
        else v2 = solve(a, b - 1);
    }

    return dp[a][b];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr, arr + n);

    ll sum = 0;
    for (int i = 1; i < n; i++) {
        diff[i - 1] = arr[i] - arr[i - 1];
        sum += diff[i - 1];
    }

    int shortt = n % k;
    int longg = k - shortt;
    swap(shortt, longg);
    slen = n / k;
    
    for (int sum = 1; sum <= k; sum++) {
        for (int a = 0; a <= sum; a++) {
            int b = sum - a;
            ll v1 = 0, v2 = 0;
            if (a > 0) {
                v1 = dp[a - 1][b];
            }
            if (b > 0) {
                v2 = dp[a][b - 1];
            }

            dp[a][b] = max(v1, v2) + diff[slen * a + (slen + 1) * b - 1];
        }
    }

    ll v1 = 0, v2 = 0; 
    if (shortt > 0) {
        v1 = dp[shortt - 1][longg];
    }
    if (longg > 0) {
        v2 = dp[shortt][longg - 1];
    }

    cout << sum - max(v1, v2) << '\n';

    return 0;
}

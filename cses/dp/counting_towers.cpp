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
#define MAXN 1000010

using namespace std;

ll dp[MAXN];
ll sum;
ll pow_sum;

ll add(ll a, ll b) {
    a += b;
    if (a >= MOD) a-= MOD;
    return a;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    dp[0] = 1;
    sum = 1;
    pow_sum = 1;

    for (int i = 1; i < MAXN; i++) {
        dp[i] = add(sum, pow_sum);
        sum = add(sum, dp[i]);
        pow_sum = add(3 * pow_sum % MOD, dp[i]);
    }

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        cout << dp[n] << '\n';
    }

    return 0;
}

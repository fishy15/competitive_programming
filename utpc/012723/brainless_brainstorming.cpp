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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> opt1(n);

    for (int i = 0 ; i < n; i++) {
        cin >> opt1[i];
    }

    for (int i = 0 ; i < n; i++) {
        int x;
        cin >> x;
        opt1[i] = max(x, opt1[i]);
    }

    for (int i = 0 ; i < n; i++) {
        int x;
        cin >> x;
        opt1[i] = max(x, opt1[i]);
    }

    vector<ll> dp(n);

    for (int i = 0; i < n; i++) {
        ll prev2 = 0;
        if (i >= 2) prev2 = dp[i - 2];
        dp[i] = prev2 + opt1[i];
        if (i >= 1) dp[i] = max(dp[i], dp[i - 1]);
    }

    cout << dp[n - 1] << '\n';

    return 0;
}

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

int n;
ll x;
ll w[20];
pair<int, ll> dp[1 << 20];

pair<int, int> comb(pair<int, ll> a, pair<int, ll> b) {
    if (a.first == b.first) {
        return max(a, b);
    }
    return min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    for (int i = 1; i < (1 << n); i++) {
        dp[i] = {INF, 0};
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                int prev = i ^ (1 << j);
                pair<int, ll> nxt;
                if (dp[prev].second < w[j]) {
                    nxt = {dp[prev].first + 1, x - w[j]};
                } else {
                    nxt = {dp[prev].first, dp[prev].second - w[j]};
                }
                dp[i] = comb(dp[i], nxt);
            }
        }
    }

    cout << dp[(1 << n) - 1].first << '\n';

    return 0;
}

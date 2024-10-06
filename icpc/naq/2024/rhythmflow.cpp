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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

int score(int a, int b) {
    auto d = abs(a - b);
    if (d <= 15) return 7;
    else if (d <= 23) return 6;
    else if (d <= 43) return 4;
    else if (d <= 102) return 2;
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> exp(n);
    rep(i, 0, n) {
        cin >> exp[i];
    }

    vector<int> actual(m);
    rep(i, 0, m) {
        cin >> actual[i];
    }

    vector dp(n+1, vector<ll>(m+1));
    rep(i, 0, n) {
        rep(j, 0, m) {
            ckmax(dp[i+1][j], dp[i][j]);
            ckmax(dp[i][j+1], dp[i][j]);
            ckmax(dp[i+1][j+1], dp[i][j] + score(exp[i], actual[j]));
        }
    }

    ll ans = 0;
    for (auto &v : dp) {
        ckmax(ans, *max_element(all(v)));
    }

    cout << ans << '\n';

    return 0;
}

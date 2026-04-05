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
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    ll k, e;
    cin >> n >> k >> e;
    
    vector<pair<ll, ll>> pos(n+1);
    rep(i, 0, n) {
        cin >> pos[i].first;
    }
    rep(i, 0, n) {
        cin >> pos[i].second;
    }
    pos[n].first = k;

    auto cost = [&](int i, int j) {
        auto d = abs(pos[i].first - pos[j].first);
        if (d > e) {
            return INFLL;
        }
        return pos[i].second * d;
    };

    sort(all(pos));
    n++;

    vector<ll> dp(n, INFLL);
    dp[0] = 0;
    rep(i, 1, n) {
        rep(j, 0, i) {
            dp[i] = min(dp[i], dp[j] + cost(j, i));
        }
    }

    rep(i, 0, n) {
        if (pos[i].first == k) {
            cout << dp[i] << '\n';
            return 0;
        }
    }

    return 0;
}

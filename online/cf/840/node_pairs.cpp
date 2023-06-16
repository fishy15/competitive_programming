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

pair<int, ll> comb(pair<int, ll> a, pair<int, ll> b) {
    if (a.first == b.first) {
        return a.second > b.second ? a : b;
    }
    return a.first < b.first ? a : b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int p;
    cin >> p;

    vector<int> choose;
    for (int i = 2; i * (i - 1) / 2 <= p; i++) {
        choose.push_back(i * (i - 1) / 2);
    }

    // num nodes, 
    vector<pair<int, ll>> dp(p + 1, {INF, 0});
    dp[0] = {0, 0};
    for (int x = 1; x <= p; x++) {
        for (int i = 0; i < (int) choose.size(); i++) {
            if (choose[i] > x) break;

            int nn = i + 2;
            auto pr = dp[x - choose[i]];
            dp[x] = comb(dp[x], {pr.first + nn, pr.second + pr.first * nn});
        }
    }

    cout << dp[p].first << ' ' << dp[p].second << '\n';

    return 0;
}

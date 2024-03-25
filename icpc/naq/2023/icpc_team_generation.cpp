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

    vector<array<int, 2>> p(n);
    for (auto &[x, y] : p) {
        cin >> x >> y;
        x--;
        y--;
    }

    vector<int> dp(n + 1);
    for (int i = 2; i < n; i++) {
        dp[i+1] = dp[i];
        int max_min = -1;
        int min_max = INF;

        for (int j = i - 2; j <= i; j++) {
            max_min = max(max_min, p[j][0]);
            min_max = min(min_max, p[j][1]);
        }

        if (max_min <= i - 2 && min_max >= i) {
            dp[i+1] = max(dp[i+1], dp[i-2] + 1);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}

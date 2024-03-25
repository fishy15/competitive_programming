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

    int n, l;
    cin >> n >> l;
    l *= 5;

    vector<int> dp(l + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        for (int i = l; i >= x; i--) {
            dp[i] = max(dp[i], dp[i - x] + 1);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}

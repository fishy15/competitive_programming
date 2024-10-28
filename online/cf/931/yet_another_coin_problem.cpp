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

int ans[1000];

void precomp() {
    fill(ans, ans + 1000, INF);
    ans[0] = 0;

    vector<int> coins = {15, 10, 6, 3, 1};
    for (auto c : coins) {
        for (int i = c; i < 1000; i++) {
            ans[i] = min(ans[i], ans[i - c] + 1);
        }
    }
}

void solve() {
    int n;
    cin >> n;

    int ans = 0;
    if (n >= 1000) {
        int gap_size = n - 999;
        int times_del = (gap_size + 14) / 15;
        ans += times_del;
        n -= 15 * times_del;
    }

    ans += ::ans[n];

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

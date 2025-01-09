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

// [l, r]
pair<ll, ll> lucky(int l, int r, int k) {
    int len = r - l + 1;
    int m = (l + r) / 2;
    if (len < k) {
        return {0LL, 0LL};
    } else if (len % 2 == 0) {
        auto [low, lc] = lucky(l, m, k);
        auto hi = low + (m+1 - l) * lc;
        return {low + hi, 2 * lc};
    } else {
        auto [low, lc] = lucky(l, m-1, k);
        auto hi = low + (m+1 - l) * lc;
        return {low + m + hi, 2 * lc + 1};
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    auto ans = lucky(1, n, k);
    cout << ans.first << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

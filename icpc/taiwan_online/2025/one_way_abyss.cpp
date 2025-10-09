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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<array<int, 3>> shafts(m);
    for (auto &[x, y, z] : shafts) {
        cin >> x >> y >> z;
        x--;
        y--;
    }

    vector<ll> dp(n);
    for (auto [x, y, v] : shafts) {
        auto new_x = dp[y] + v;
        auto new_y = dp[x] + v;
        tie(dp[x], dp[y]) = {new_x, new_y};
    }

    cout << *max_element(all(dp)) << '\n';
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

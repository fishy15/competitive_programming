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

constexpr int MAXN = 3e5;
constexpr int L = 20;

ll ans[L];
ll counts[L][MAXN];
ll sums[L][2 * MAXN];
ll diffs[L][MAXN];

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n+1);
    rep(i, 0, n) {
        int x;
        cin >> x;
        nums[x]++;
    }

    ll ans = 0;
    ll old = 0;
    rep(i, 0, n+1) {
        auto c = (ll) nums[i];
        ans += c * (c - 1) * (c - 2) / 6;
        ans += c * (c - 1) * old / 2;
        old += c;
    }

    cout << ans << '\n';
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

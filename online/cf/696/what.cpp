/*
 * The inverse operation specificed is taking some node such that p_i = i and swapping it with some other 
 * location. Starting from an ordered permutation, we can move each value to the end that is the farthest 
 * away (1 or n). This will maximize the difference at each point, so this gives us the maximum cost.
 */
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

void solve() {
    int n; cin >> n;
    vector<int> nums(n + 1);
    vector<pair<int, int>> ss;
    iota(nums.begin(), nums.end(), 0);
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        int x = abs(i - 1) > abs(i - n) ? 1 : n;
        ans += (ll)(i - x) * (i - x);
        swap(nums[i], nums[x]);
        ss.push_back({i, x});
    }

    cout << ans << '\n';
    for (int i = 1; i <= n; i++) cout << nums[i] << ' ';
    cout << '\n';
    cout << n - 1 << '\n';
    for (int i = n - 2; i >= 0; i--) cout << ss[i].first << ' ' << ss[i].second << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

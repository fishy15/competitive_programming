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
    vector<int> nums;
    set<int> no;
    for (int i = 0; i < n; i++) {
        no.insert(2 * i + 1);
        no.insert(2 * i + 2);
        int x; cin >> x;
        nums.push_back(x);
    }
    vector<int> rest;
    for (int x : nums) no.erase(x);
    for (int x : no) rest.push_back(x);

    vector<int> lower(n);
    vector<int> higher(n);

    for (int i = 0; i < n; i++) {
        auto it = lower_bound(rest.begin(), rest.end(), nums[i]);
        lower[i] = distance(it, rest.end());
        higher[i] = distance(rest.begin(), it); 
    }

    int max_low = n;
    int min_high = 0;
    for (int i = 0; i < n; i++) {
        max_low = min(max_low, i + lower[i]);
        min_high = max(min_high, i - higher[i] + 1);
    }

    vector<int> ok(n + 1);
    vector<int> ok2(n + 1);
    int ans = 0;
    for (int i = 0; i <= max_low; i++) {
        ok[i] = true;
    }
    for (int i = min_high; i <= n; i++) {
        ok2[i] = true;
    }
    for (int i = 0; i <= n; i++) {
        if (ok[i] && ok2[i]) ans++;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

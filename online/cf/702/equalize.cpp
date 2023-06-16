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
    vector<int> nums(n);

    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        cnt[nums[i]]++;
    }

    map<int, int> cnt_cnt;

    for (auto p : cnt) {
        cnt_cnt[p.second]++;
    }

    int above_sec = cnt.size();
    int ans = n;

    for (auto p : cnt_cnt) {
        int cost = n - above_sec * p.first;
        ans = min(ans, cost);
        above_sec -= p.second;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

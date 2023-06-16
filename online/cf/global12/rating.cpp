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

int cnt[MAXN];

bool chk(int n) {
    for (int i = 1; i <= n; i++) {
        if (cnt[i] != 1) return false;
    }
    return true;
}

bool check(vector<int> &nums, int n, int k) {
    vector<int> res;
    deque<pair<int, int>> cur;

    for (int i = 0; i <= n; i++) {
        cnt[i] = 0;
    }

    for (int i = 0; i < k; i++) {
        while (!cur.empty() && nums[i] < cur.back().second) cur.pop_back();
        cur.push_back({i, nums[i]});
    }

    cnt[cur[0].second]++;

    for (int i = 1; i < n - k + 1; i++) {
        while (!cur.empty() && cur[0].first < i) cur.pop_front();
        while (!cur.empty() && nums[i] < cur.back().second) cur.pop_back();
        cur.push_back({i, nums[i]});
        cnt[cur[0].second]++;
    }

    return chk(n - k + 1);
}

void solve() {
    int n; cin >> n;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    cout << check(nums, n, 1);

    int l = 2;
    int r = n;
    int ans = n + 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(nums, n, m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    for (int i = 2; i < ans; i++) {
        cout << 0;
    }

    for (int i = ans; i <= n; i++) {
        cout << 1;
    }
    
    cout << '\n';
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

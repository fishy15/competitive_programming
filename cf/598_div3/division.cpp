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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200000

using namespace std;

int n;
pair<ll, int> dp[MAXN + 10];
pair<ll, int> nums[MAXN + 10];
int ans[MAXN + 10];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i].first;
        nums[i].second = i;
    }

    sort(nums, nums + n);

    if (n < 6) {
        cout << nums[n - 1].first - nums[0].first << ' ' << 1 << '\n';
        for (int i = 0; i < n; i++) {
            cout << 1 << ' ';
        } cout << '\n';
        return 0;
    }

    for (int i = 1; i < n; i++) {
        // upper limit doesn't matter tbh, just has to be constant
        for (int d = 3; d <= 10; d++) {
            if (i - d >= 0) dp[i] = max(dp[i], {dp[i - d].first
                    + nums[i].first - nums[i - 1].first, d});
        }
    }

    pair<ll, int> m = {0, 0};
    int pos = 0;
    for (int i = 1; i < n - 2; i++) {
        if (m < dp[i]) {
            m = dp[i];
            pos = i;
        }
    }

    vector<int> cur;
    while (pos > 0 && dp[pos].second > 0) {
        cur.push_back(pos);
        pos -= dp[pos].second;
    }

    int prev = 0;
    reverse(cur.begin(), cur.end());
    int cnt = 1;
    for (int i : cur) {
        for (int j = prev; j < i; j++) {
            ans[nums[j].second] = cnt;
        }
        cnt++;
        prev = i;
    }
    
    for (int i = *cur.rbegin(); i < n; i++) {
        ans[nums[i].second] = cnt;
    }

    cout << nums[n - 1].first - nums[0].first - m.first << ' ' << cnt << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    } cout << '\n';

    return 0;
}

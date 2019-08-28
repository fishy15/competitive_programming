// :pray: :fishy:

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <assert.h>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 2000

using namespace std;

int n;
int nums[MAXN];
int sec_last[MAXN];
int last[MAXN];
int sec[MAXN];
int first[MAXN];
pair<int, int> dp[MAXN][2];

map<int, int> pos;
map<int, int> cnt;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (cnt.count(nums[i])) {
            cnt[nums[i]]++;
        } else {
            cnt[nums[i]] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        last[i] = -1;
        sec_last[i] = -1;
        first[i] = -1;
        sec[i] = -1;
        for (int j = i + 1; j < n; j++) {
            if (nums[i] == nums[j]) {
                sec_last[i] = last[i];
                last[i] = j;
            }
        }

        for (int j = i - 1; j >= 0; j--) {
            if (nums[i] == nums[j]) {
                sec[i] = first[i];
                first[i] = j;
            }
        }
    }

    vector<vector<vector<int>>> seq(n);
    set<int> top_done;
    set<int> bottom_done;
    for (int i = 0; i < n; i++) {
        if (cnt[nums[i]] > 1 && !top_done.count(nums[i])) {
            top_done.insert(nums[i]);
            int p = (int)(pos.size());
            pos[nums[i]] = p;
            seq[pos[nums[i]]] = {{-1, -1, -1}, {INF, INF, INF}};
            if (sec_last[i] == -1) {
                seq[pos[nums[i]]][0] = {nums[i], i, i};
            } else {
                seq[pos[nums[i]]][0] = {nums[i], i, sec_last[i]};
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (cnt[nums[i]] > 1 && !bottom_done.count(nums[i])) {
            bottom_done.insert(nums[i]);
            //assert(pos[nums[i]] < pos.size());
            if (sec[i] == -1) {
                seq[pos[nums[i]]][1] = {nums[i], i, i};
            } else {
                seq[pos[nums[i]]][1] = {nums[i], sec[i], i};
            }
        }
    }

    if (pos.size() == 0) {
        cout << 0 << n;
        return 0;
    }

    dp[0][0] = {seq[0][0][1], seq[0][0][2]};
    dp[0][1] = {seq[0][1][1], seq[0][1][2]};

    int p = (int)(pos.size());
    for (int i = 1; i < p; i++) {
        for (int j = 0; j < 2; j++) {
            int l1 = min(dp[i - 1][0].first, seq[i][j][1]);
            int l2 = min(dp[i - 1][1].first, seq[i][j][1]);
            int r1 = max(dp[i - 1][0].second, seq[i][j][2]);
            int r2 = max(dp[i - 1][1].second, seq[i][j][2]);
            if (r2 - l2 > r1 - l1) {
                dp[i][j] = {l1, r1};
            } else {
                dp[i][j] = {l2, r2};
            }
        }
        //cout << dp[i][1].first <<   << dp[i][1].second << n;
    }

    if (dp[p - 1][0].second - dp[p - 1][0].first < dp[p - 1][1].second - dp[p - 1][1].first) {
        cout << dp[p - 1][0].second - dp[p - 1][0].first + 1 << n;
    } else {
        cout << dp[p - 1][1].second - dp[p - 1][1].first + 1 << n;
    }

    return 0;
}


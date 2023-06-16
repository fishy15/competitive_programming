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
#define MAXN 160

using namespace std;

int n;
int nxt[MAXN];
bool vis[MAXN];
vector<int> start[MAXN];
int cnt[MAXN];
pair<int, int> nums[MAXN];
int diff[MAXN][MAXN];
ll dp[5000000];
int rem[5000000];
ll sum;
int ans[MAXN];

// how to make and get state
int sz;
int vals[MAXN];
int d[MAXN];
int m[MAXN];

int conv(const vector<int> &nums) {
    int res = 0;
    for (int i = 0; i < sz; i++) {
        res += nums[i] * d[i];
    }
    return res;
}

void dfs(int pos, int &len) {
    if (!vis[pos]) {
        vis[pos] = true;
        len++;
        dfs(nxt[pos], len);
    }
}

void dfs2(int pos, int idx, int st, int len) {
    if (!vis[pos]) {
        int m = (len - 1) / 2;
        if (idx <= m) {
            ans[pos] = nums[st + 2 * idx].first;
        } else {
            ans[pos] = nums[st + len - 2 * (idx - m) + (len % 2 == 0)].first;
        }
        vis[pos] = true;
        dfs2(nxt[pos], idx + 1, st, len);
    }
}

int solve(vector<int> &cur, int len, int c) {
    if (len == 0) return 0;
    if (dp[c] < INFLL) return dp[c];

    for (int i = 0; i < sz; i++) {
        if (cur[i]) {
            cur[i]--;
            ll res = max(solve(cur, len - vals[i], c - d[i]), diff[len - vals[i]][len - 1]);
            cur[i]++;
            if (res < dp[c]) {
                dp[c] = res;
                rem[c] = i;
            }
        }
    }
    return dp[c];
}

void calc(vector<int> &cur, int len, int c) {
    if (len > 0) {
        int taken = rem[c];
        dfs2(start[vals[taken]].back(), 0, len - vals[taken], vals[taken]);
        start[vals[taken]].pop_back();
        cur[taken]--;
        calc(cur, len - vals[taken], c - d[taken]);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nxt[i];
        nxt[i]--;
    }

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        nums[i] = {x, i};
    }

    sort(nums, nums + n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            diff[i][j] = max(diff[i][j], nums[i + 1].first - nums[i].first);
            diff[i][j] = max(diff[i][j], nums[j].first - nums[j - 1].first);
            for (int k = i; k <= j - 2; k++) {
                diff[i][j] = max(diff[i][j], nums[k + 2].first - nums[k].first);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int len = 0;
            dfs(i, len);
            start[len].push_back(i);
            cnt[len]++;
        }
    }

    ll p = 1;
    for (int i = 0; i <= 150; i++) {
        if (cnt[i]) {
            vals[sz] = i;
            d[sz] = p;
            p *= cnt[i] + 1;
            m[sz] = p;
            sz++;
        }
    }

    vector<int> cur;
    for (int i = 0; i < sz; i++) {
        cur.push_back(cnt[vals[i]]);
    }

    memset(dp, 0x3f, sizeof dp);
    memset(vis, 0, sizeof vis);
    int c = conv(cur);
    cout << solve(cur, n, c) << '\n';
    calc(cur, n, c);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}

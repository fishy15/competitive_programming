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
#define MAXN 200010

using namespace std;

int n, m;
int ans;
int left_cnt, right_cnt;
int nums[MAXN];
bool vis[MAXN];

void dfs(int cur, int len, int left, int right) {
    if (vis[cur]) {
        if (len > 1) {
            if (!right) left_cnt++;
            if (!left) right_cnt++;
            ans += len - 1;
        }
    } else {
        vis[cur] = true;
        int nxt = nums[cur];
        dfs(nxt, len + 1, left || nxt < n, right || nxt >= n);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n + m; i++) {
        cin >> nums[i];
        nums[i]--;
    }

    for (int i = 0; i < n + m; i++) {
        if (!vis[i]) {
            dfs(i, 0, i < n, i >= n);
        }
    }

    ans += 2 * max(left_cnt, right_cnt);
    cout << ans << '\n';

    return 0;
}

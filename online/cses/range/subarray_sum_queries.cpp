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
#define MAXN 200010

using namespace std;

int n, m;
int nums[MAXN];
ll sum[4 * MAXN];
ll pre[4 * MAXN];
ll suf[4 * MAXN];
ll ans[4 * MAXN];

ll ckmax(ll &a, ll b) {
    return a = max(a, b);
}

void build(int v, int l, int r) {
    if (l == r) {
        sum[v] = nums[l];
        ckmax(pre[v], nums[l]);
        ckmax(suf[v], nums[l]);
        ckmax(ans[v], nums[l]);
    } else {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        sum[v] = sum[2 * v] + sum[2 * v + 1];
        pre[v] = max(pre[2 * v], sum[2 * v] + pre[2 * v + 1]);
        suf[v] = max(suf[2 * v] + sum[2 * v + 1], suf[2 * v + 1]);
        ans[v] = max(ans[2 * v], ans[2 * v + 1]);
        ckmax(ans[v], suf[2 * v] + pre[2 * v + 1]);
    }
}

void upd(int v, int l, int r, int x, int y) {
    if (l == r) {
        nums[x] = y;
        sum[v] = nums[x];
        pre[v] = max(0, nums[x]);
        suf[v] = max(0, nums[x]);
        ans[v] = max(0, nums[x]);
    } else {
        int m = (l + r) / 2;
        if (x <= m) upd(2 * v, l, m, x, y);
        else upd(2 * v + 1, m + 1, r, x, y);
        sum[v] = sum[2 * v] + sum[2 * v + 1];
        pre[v] = max(pre[2 * v], sum[2 * v] + pre[2 * v + 1]);
        suf[v] = max(suf[2 * v] + sum[2 * v + 1], suf[2 * v + 1]);
        ans[v] = max(ans[2 * v], ans[2 * v + 1]);
        ckmax(ans[v], suf[2 * v] + pre[2 * v + 1]);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    build(1, 0, n - 1);

    for (int i = 0; i < m; i++) {
        int k, x; cin >> k >> x;
        k--;
        upd(1, 0, n - 1, k, x);
        cout << ans[1] << '\n';
    }

    return 0;
}

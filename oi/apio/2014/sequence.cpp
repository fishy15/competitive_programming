#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <stack>
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
#define MAXN 100010

using namespace std;

int n, k;
int nums[MAXN];
int psum[MAXN];
ll dp_prev[MAXN];
ll dp_cur[MAXN];
int p[210][MAXN];
int arr[210];

void solve(int i, int l, int r, int opt_l, int opt_r) {
    if (l > r) return;
    int m = (l + r) / 2;
    ll max_prod = 0;
    int pos = opt_l;

    for (int j = opt_l; j <= min(m - 1, opt_r); j++) {
        ll before = psum[j + 1];
        ll after = psum[m + 1] - psum[j + 1];
        ll prod = before * after + dp_prev[j];
        if (prod >= max_prod) {
            max_prod = prod;
            pos = j;
        }
    }

    dp_cur[m] = max_prod;
    p[i][m] = pos;
    solve(i, l, m - 1, opt_l, pos);
    solve(i, m + 1, r, pos, opt_r);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 1; i <= n; i++) {
        psum[i] = psum[i - 1] + nums[i - 1];
    }

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < n; j++) {
            dp_cur[j] = 0;
        }
        solve(i, 0, n - 1, 0, n - 1);
        for (int j = 0; j < n; j++) {
            dp_prev[j] = dp_cur[j];
        }
    }

    pair<ll, int> ans = {0, 0};
    for (int i = k; i < n; i++) {
        ans = max(ans, {dp_cur[i], p[k][i]});
    }
    
    cout << ans.first << '\n';
    int cur = ans.second;
    for (int i = k - 1; i >= 0; i--) {
        arr[k - i - 1] = cur + 1;
        cur = p[i][cur];
    }

    for (int i = k - 1; i >= 0; i--) {
        cout << arr[i] << ' ';
    }
    cout << '\n';

    return 0;
}

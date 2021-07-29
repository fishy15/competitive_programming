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

int n;
int a[MAXN];
int b[MAXN];
int logs[MAXN];

int st1[MAXN][20];
int st2[MAXN][20];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    logs[1] = 0;
    for (int i = 2; i < MAXN; i++) {
        logs[i] = logs[i / 2] + 1;
    }

    for (int p = 0; p <= logs[n]; p++) {
        int cur = 1 << p;
        for (int i = 0; i + cur <= n; i++) {
            if (cur == 1) {
                st1[i][0] = a[i];
                st2[i][0] = b[i];
            } else {
                st1[i][p] = max(st1[i][p - 1], st1[i + cur / 2][p - 1]);
                st2[i][p] = min(st2[i][p - 1], st2[i + cur / 2][p - 1]);
            }
        }
    }

    ll ans = 0;

    for (int i = 0; i < n; i++) {
        // lower bound
        int l = i;
        int r = n - 1;
        int ans1 = -1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            int p = logs[m - i + 1];
            int pow = 1 << p;
            int m1 = max(st1[i][p], st1[m - pow + 1][p]);
            int m2 = min(st2[i][p], st2[m - pow + 1][p]);
            if (m1 == m2) {
                ans1 = m;
                r = m - 1;
            } else if (m1 > m2) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        if (ans1 == -1) continue;

        // upper bound
        l = i;
        r = n - 1;
        int ans2 = -1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            int p = logs[m - i + 1];
            int pow = 1 << p;
            int m1 = max(st1[i][p], st1[m - pow + 1][p]);
            int m2 = min(st2[i][p], st2[m - pow + 1][p]);
            if (m1 == m2) {
                ans2 = m;
                l = m + 1;
            } else if (m1 > m2) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        ans += ans2 - ans1 + 1;
    }

    cout << ans << '\n';

    return 0;
}

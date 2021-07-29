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

int n, k;
int nums[MAXN];
int pre[MAXN];
int calc[MAXN];

bool check(int m) {
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        if (nums[i - 1] >= m) {
            pre[i]++;
        }
    }
    for (int i = 0; i <= n; i++) {
        calc[i] = i - 2 * pre[i];
    }
    int maxi = calc[0];
    for (int i = k; i <= n; i++) {
        maxi = max(maxi, calc[i - k]);
        if (maxi > calc[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int l = 1;
    int r = n;
    int ans = 0;

    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    cout << ans << '\n';

    return 0;
}

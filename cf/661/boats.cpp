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
    array<int, 110> cnt;
    for (int i = 0; i < 110; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    pair<int, int> ans = {0, 0};
    for (int i = 2; i <= 100; i++) {
        int cur = 0;
        for (int j = 1; j <= i / 2; j++) {
            if (j == i - j) {
                cur += cnt[j] / 2;
                /* if (i < 10 && j < 10) cout << j << ' ' << cnt[j] / 2 << '\n'; */
            } else {
                cur += min(cnt[j], cnt[i - j]);
                /* if (i < 10 && j < 10) cout << j << ' ' << i - j << ' ' << min(cnt[j], cnt[i - j]) << '\n'; */
            }
        }
        ans = max(ans, {cur, i});
    }
    cout << ans.first << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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
#include <functional>
#include <numeric>

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
    int n, k, d, w;
    cin >> n >> k >> d >> w;

    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    sort(t.begin(), t.end());

    int ans = 0;
    int r = 0;

    while (r < n) {
        ans++;

        int cur_end = t[r] + w;
        bool quit_early = false;
        for (int i = 1; i < k; i++) {
            if (r + i >= n || t[r + i] > cur_end + d) {
                r = r + i;
                quit_early = true;
                break;
            }
        }

        if (!quit_early) {
            r += k;
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

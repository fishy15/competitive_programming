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

int below_msb(int x) {
    int res = 0;
    for (int i = 0; i < 30; i++) {
        if (x >> (i + 1)) {
            res ^= 1 << i;
        }
    }
    return res;
}

void solve() {
    int n;
    cin >> n;

    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    pair<int, int> best;
    for (auto [v, c] : cnt) {
        if (c > best.second) {
            best = {v, c};
        }
    }

    int ans = best.second;
    for (auto [v, c] : cnt) {
        if (v != best.first) {
            int cur = best.second | c | below_msb(best.second & c);
            ans = max(ans, cur);
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

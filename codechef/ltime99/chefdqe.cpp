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
    int n, m; cin >> n >> m;

    vector<ll> psum(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> psum[i + 1];
        psum[i + 1] += psum[i];
        psum[i + 1] %= m;
    }

    if (psum[n] == 0) {
        cout << 0 << '\n';
        return;
    }

    int ans = INF;
    vector<int> bit_cnt(n);
    for (int i = 1; i < n; i++) {
        bit_cnt[i] = bit_cnt[i >> 1] + (i & 1);
        for (int s = i;; s = (s - 1) & i) {
            if (i + s >= n) continue;

            if (psum[s] == psum[n - i]) {
                ans = min(ans, bit_cnt[i]);
            }

            if (s == 0) break;
        }
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

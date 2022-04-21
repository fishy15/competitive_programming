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
    int n, k; cin >> n >> k;
    array<int, 31> cnt{};

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        for (int j = 0; j < 31; j++) {
            if (x & (1 << j)) {
                cnt[j]++;
            }
        }
    }

    int ans = 0;
    for (int i = 30; i >= 0; i--) {
        if (k >= n - cnt[i]) {
            k -= n - cnt[i];
            ans += 1 << i;
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

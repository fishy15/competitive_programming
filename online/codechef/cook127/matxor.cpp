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
    ll n, m, k; cin >> n >> m >> k;
    ll ans = 0;

    if (n < m) swap(n, m);

    int cnt = 0;
    for (int i = 2; i <= n + m; i++) {
        if (i <= m + 1) cnt++;
        else if (i > n + 1) cnt--;
        if (cnt % 2 == 1) {
            ans ^= k + i;
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

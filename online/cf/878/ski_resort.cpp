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

ll combo(ll len, ll k) {
    len -= k - 1;
    if (len >= 0) {
        return len * (len + 1) / 2;
    } else {
        return 0;
    }
}

void solve() {
    int n, k, q;
    cin >> n >> k >> q;

    vector<bool> ok(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        ok[i] = (a <= q);
    }

    int cur = 0;
    ll ans = 0;
    for (auto b : ok) {
        if (b) {
            cur++;
        } else {
            ans += combo(cur, k);
            cur = 0;
        }
    }

    ans += combo(cur, k);
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

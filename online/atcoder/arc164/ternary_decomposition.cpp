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

int sz_ternary(ll n) {
    ll cur_p = 1;
    while (3 * cur_p <= n) cur_p *= 3;

    int cnt = 0;
    while (n > 0) {
        if (cur_p <= n) {
            n -= cur_p;
            cnt++;
        } else {
            cur_p /= 3;
        }
    }

    return cnt;
}

void solve() {
    ll n, k;
    cin >> n >> k;

    auto sz = sz_ternary(n);
    if (sz <= k && k <= n && sz % 2 == k % 2) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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

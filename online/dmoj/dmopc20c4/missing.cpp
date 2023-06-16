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
    ll n, k; cin >> n >> k;
    ll rem = n * (n + 1) / 2 - k;
    if (rem <= n + 1) {
        cout << (rem - 1) / 2 << '\n';
    } else if (rem <= 2 * n) {
        ll min_need = rem - n;
        ll ans = n - min_need + 1;
        if (rem % 2 == 0) ans--;
        cout << ans / 2 << '\n';
    } else {
        cout << "0\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

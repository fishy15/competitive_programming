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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    ll sum = 0;
    ll xx = 0;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        sum += x;
        xx ^= x;
    }

    int l = 0;
    ll s = sum;
    while (sum > 0) {
        l++;
        sum /= 2;
    }

    cout << 3 << '\n';
    ll v = (1 << l) ^ xx;
    ll res = (1 << (l + 1));
    cout << v << ' ' << (res - v - s) / 2 << ' ' << (res - v - s) / 2 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

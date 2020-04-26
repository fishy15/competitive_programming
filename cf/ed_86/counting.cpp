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

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

void solve() {
    ll a, b, q; cin >> a >> b >> q;
    ll lcm = a * b / gcd(a, b);
    if (a > b) swap(a, b);
    for (int i = 0; i < q; i++) {
        ll l, r; cin >> l >> r;
        ll below = (l / lcm * lcm);
        ll miss = 0;
        if (l - below - 1 < b) {
            miss += (l - below - 1) + 1;
        } else {
            miss += b;
        }
        below = ((r + 1) / lcm * lcm);
        if ((r + 1) - below < b) {
            miss += b - (r - below + 1);
        }
        ll ans = ((r + 1) / lcm - l / lcm + 1) * b - miss;
        cout << (r - l + 1) - ans << ' ';
    } cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

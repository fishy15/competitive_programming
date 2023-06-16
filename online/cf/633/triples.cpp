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

ll mov[4][3] = {
    {0, 0, 0},
    {1, 2, 3},
    {2, 3, 1},
    {3, 1, 2}
};

void solve() {
    ll n; cin >> n;
    if (n <= 3) {
        cout << n << '\n';
        return;
    }

    ll pos = (n + 2) % 3;
    ll cur = 0;
    ll pow = 0;
    ll grp = (n - 1) / 3;
    while (cur <= grp) {
        cur += (1LL << (2 * pow));
        pow++;
    };

    pow--;
    cur -= (1LL << (2 * pow));
    ll loc = grp - cur + (1LL << (2 * pow));
    ll ans = 0;
    for (int i = 0; i <= pow; i++) {
        ans += mov[(loc >> (2 * i)) & 3][pos] << (2 * i);
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

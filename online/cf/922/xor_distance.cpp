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

int bit(ll x, int i) {
    return (x >> i) & 1;
}

void solve() {
    ll a, b, r;
    cin >> a >> b >> r;

    if (a == b) {
        cout << "0\n";
        return;
    }

    if (a < b) swap(a, b);

    bool reached_first = 0;
    ll ans = 0;
    ll cur_r = 0;
    for (int i = 60; i >= 0; i--) {
        if (bit(a, i) != bit(b, i)) {
            if (!reached_first) {
                // this is the first one
                reached_first = true;
                ans = 1LL << i;
            } else {
                if (bit(a, i) == 1) {
                    if (cur_r + (1LL << i) <= r) {
                        cur_r += 1LL << i;
                        ans -= 1LL << i;
                    } else {
                        ans += 1LL << i;
                    }
                } else {
                    // keeping it the same subtracts from the difference
                    ans -= 1LL << i;
                }
            }
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

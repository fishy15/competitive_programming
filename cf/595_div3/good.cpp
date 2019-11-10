// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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
    ll n; cin >> n;

    ll l = 0;
    ll r = (1LL << 39);
    ll ans = -1;

    while (l <= r) {
        ll mid = l + (r - l) / 2;
        ll num = 0;
        ll cur = 1;
        ll chk = 1;

        for (int i = 0; i <= 39; i++) {
            if (mid & chk) {
                num += cur;
            }

            cur *= 3;
            chk *= 2;
        }

        //cout << num << '\n';

        if (num >= n) {
            ans = num;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;

    while (q--) {
        solve();
    }

    return 0;
}

// :pray: :steph:
// :pray: :bakekaga:

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, k, m, d; cin >> n >> k >> m >> d;

    ll ans2 = 0;
    for (int i = 1; i <= d; i++) {
        ll l = 1;
        ll r = m;
        ll ans = -1;

        while (l <= r) {
            ll x = l + (r - l) / 2;
            double go_around = n / x;
            ll give = ceil(go_around / k);
            if (give < i) {
                r = x - 1;
            } else if (give > i) {
                l = x + 1;
            } else if (give == i) {
                l = x + 1;
                ans = x;
            }
        }

        if (ans != -1) {
            double go_around = n / ans;
            ll give = ceil(go_around / k);
            /* cout << ans << ' ' << give * ans << '\n'; */
            ans2 = max(ans2, give * ans);
        }
    }

    cout << ans2 << '\n';

    return 0;
}

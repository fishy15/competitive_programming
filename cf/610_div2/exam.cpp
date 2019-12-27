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

void solve() {
    ll n, t, a, b; cin >> n >> t >> a >> b;
    vector<ll> diff;
    ll easy = 0, hard = 0;
    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        diff.push_back(x);
        if (x) {
            hard++;
        } else {
            easy++;
        }
    }

    vector<pair<ll, ll>> tt;
    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        tt.push_back({x, i});
    }

    sort(tt.begin(), tt.end());
    ll cur = 0;
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        if (cur < tt[i].first) {
            ll remain = tt[i].first - cur - 1;
            ll ea_poss = remain / a;
            ll qq = 0;
            if (ea_poss > easy) {
                remain -= easy * a;
                qq = easy;
            } else {
                remain -= ea_poss * a;
                qq = ea_poss;
            }

            if (remain > 0) {
                ll h_poss = remain / b;
                if (h_poss > hard) {
                    qq += hard;
                } else {
                    qq += h_poss;
                }
            }

            ans = max(ans, i + qq);
        }
        cur += diff[tt[i].second] ? b : a;
        if (diff[tt[i].second]) {
            hard--;
        } else {
            easy--;
        }
    }
    if (cur <= t) {
        ans = n;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll t; cin >> t;
    while (t --> 0) {
        solve();
    }

    return 0;
}

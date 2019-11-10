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

ll n, k;
vector<ll> purchase;
vector<ll> coins;
vector<ll> pre;
ll dp[1 << 16];

int main() {
    ifstream fin("nochange.in");
    ofstream fout("nochange.out");

    fin >> k >> n;

    for (ll i = 0; i < k; i++) {
        ll x; fin >> x;
        coins.push_back(x);
    }

    for (ll i = 0; i < n; i++) {
        ll x; fin >> x;
        purchase.push_back(x);
    }

    pre.push_back(0);

    for (ll i = 0; i < n; i++) {
        pre.push_back(pre[i] + purchase[i]);
    }

    for (ll i = 0; i < (1 << k); i++) {
        for (ll j = 0; j < k; j++) {
            if (i & (1 << j)) {
                ll pos = i - (1 << j);
                ll l = dp[pos]; 
                ll r = n;
                ll ans = -1;

                while (l <= r) {
                    ll mid = l + (r - l) / 2;
                    ll diff = pre[mid] - pre[dp[pos]];
                    if (diff <= coins[j]) {
                        ans = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }

                //cout << "adding " << (1 << j) << " to " << pos << " gives " << ans - dp[pos] << " + " << dp[pos] << '\n';

                dp[i] = max(dp[i], ans);
            }
        }
    }

    ll ans = 0;
    for (ll i = 0; i < (1 << k); i++) {
        //cout << dp[i] << '\n';
        if (dp[i] == n) {
            ll cost = 0;
            for (ll j = 0; j < k; j++) {
                if ((i & (1 << j)) == 0) {
                    cost += coins[j];
                }
            }

            ans = max(ans, cost);
        }
    }

    if (ans == 0) {
        fout << -1 << '\n';
    } else {
        fout << ans << '\n';
    }

    return 0;
}

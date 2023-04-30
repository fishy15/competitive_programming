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
#define MAXN 1000010

using namespace std;

ll n, m;
ll cnt[MAXN];
vector<ll> change[MAXN];
ll needed[MAXN];
ll sum;
pair<ll, ll> ans;
ll cur;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        ll a; cin >> a;
        cnt[a]++;
        sum += a;
    }
    
    for (ll i = 1; i < MAXN; i++) {
        if (cnt[i] > 0) {
            needed[i] = 1;
            cur += cnt[i];

            for (ll j = 1; j * j <= i; j++) {
                change[j].push_back(i);
                if (i % j == 0) {
                    change[i / j - 1].push_back(i);
                } else {
                    change[i / j].push_back(i);
                }
            }
        }
    }

    if (m < n) {
        cout << "-1\n";
        return 0;
    }

    ll cur_v = 1000000;
    ans = {cur_v * cur - sum, cur_v};

    for (ll i = 1000000 - 1; i > 0; i--) {
        for (ll x : change[i]) {
            ll old_n = needed[x];
            ll new_n = (i + x - 1) / i;
            needed[x] = new_n;

            cur -= old_n * cnt[x];
            cur += new_n * cnt[x];
        }

        if (cur <= m) {
            ans = min(ans, {i * cur - sum, i});
        }
    }

    cout << ans.second << '\n';

    return 0;
}

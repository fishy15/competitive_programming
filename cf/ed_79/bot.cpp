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
#define MOD 998244353 

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    ll x1, y1;
    ll g = egcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;

    return g;
}

ll inv(ll a) {
    ll x, y;
    ll g = egcd(a, MOD, x, y);
    return (x + MOD) % MOD;
}

int n;
vector<vector<int>> ppl;
int cnt[MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        vector<int> res;
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            res.push_back(x);
            cnt[x]++;
        }
        ppl.push_back(res);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int p : ppl[i]) {
            ll p1 = inv(ppl[i].size());
            ll p2 = inv(n) * cnt[p] % MOD;
            ll p3 = inv(n);
            ans += (p1 * p2 % MOD) * p3 % MOD;
            if (ans > MOD) ans -= MOD;
        }
    }

    cout << ans << '\n';

    return 0;
}

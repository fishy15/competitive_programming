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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

ll n;
ll ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    ll sq = sqrt(n);
    ans += sq; // diff = 0
    for (ll diff = 1; diff <= sq; diff++) {
        ll max_range = (n / diff + diff) / 2;
        ans += max(0LL, min(n, max_range) - diff);
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans << '\n';

    return 0;
}

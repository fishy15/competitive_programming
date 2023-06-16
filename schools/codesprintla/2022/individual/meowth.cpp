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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, p, x, y; cin >> n >> p >> x >> y;
    ll ans = 0;

    while (p > 0) {
        ll cnt = min(p, n - 1);
        ans += cnt * x;
        p -= cnt;

        if (cnt == n - 1) ans += y;
    }

    cout << ans << '\n';

    return 0;
}

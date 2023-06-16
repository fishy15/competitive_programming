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

ll solve(ll n, ll r) {
    ll ans = 0;

    for (int i = 0; i <= 60; i++) {
        if ((r >> i) == 0) break;
        if ((n >> i) & 1) {
            ll low = 1LL << i;
            ll high = min(1LL << (i + 1), r);
            ans += high - low;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, l, r; cin >> n >> l >> r;

    cout << solve(n, r + 1) - solve(n, l) << '\n';

    return 0;
}

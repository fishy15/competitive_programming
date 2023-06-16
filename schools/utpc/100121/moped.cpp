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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

ll r;
ll ans;

ll sq(ll x) {
    return x * x;
}

bool per(ll x) {
    ll s = sqrt(x);
    return s * s == x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> r;

    for (ll a = 0; a <= r; a++) {
        for (ll b = 0; b <= r; b++) {
            if (sq(a) + sq(b) > sq(r)) break;
            ll c = sq(r) - sq(a) - sq(b);
            if (per(c)) {
                ll add = 1;
                if (a > 0) add *= 2;
                if (b > 0) add *= 2;
                if (c > 0) add *= 2;
                ans += add;
            }
        }
    }

    // idk
    cout << ans << '\n';

    return 0;
}

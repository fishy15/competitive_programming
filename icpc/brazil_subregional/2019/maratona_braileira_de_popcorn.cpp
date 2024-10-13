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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, c, t;
    cin >> n >> c >> t;

    vector<ll> popcorn(n);
    rep(i, 0, n) {
        cin >> popcorn[i];
    }

    auto check = [&](ll m) {
        int l = 0;
        int r = 0;
        int people = 0;
        while (l < n) {
            ll cur = 0;
            while (r < n && (cur + popcorn[r] + t - 1) / t <= m) {
                cur += popcorn[r];
                r++;
            }
            l = r;
            people++;
        }
        return people <= c;
    };

    auto biggest = *max_element(all(popcorn));
    ll lo = (biggest + t - 1) / t;
    ll hi = accumulate(all(popcorn), 0LL);
    ll ans = -1;

    while (lo <= hi) {
        auto m = lo + (hi - lo) / 2;
        if (check(m)) {
            ans = m;
            hi = m - 1;
        } else {
            lo = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}

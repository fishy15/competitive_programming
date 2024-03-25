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

    ll n, k, p;
    cin >> n >> k >> p;

    set<ll> ans;

    auto check = [&](ll x) {
        if (x <= k && n / x <= p) {
            ans.insert(x);
        }
    };

    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            check(i);
            if (i * i != n) check(n / i);
        }
    }

    cout << ans.size() << '\n';
    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}

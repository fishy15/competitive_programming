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

vector<pair<ll, int>> factor(ll n) {
    vector<pair<ll, int>> res;

    if (n % 2 == 0) {
        res.push_back({2, 0});
        while (n % 2 == 0) {
            res.back().second += 1;
            n /= 2;
        }
    }

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            res.push_back({i, 0});
            while (n % i == 0) {
                res.back().second += 1;
                n /= i;
            }
        }
    }

    if (n > 1) {
        res.push_back({n, 1});
    }

    return res;
}

void solve() {
    ll n;
    cin >> n;

    auto factors = factor(n);
    sort(factors.begin(), factors.end(), [](auto p1, auto p2) {
        return p1.second > p2.second;
    });
    
    ll ans = 0;
    while (!factors.empty()) {
        ll tot = 1;
        ll e = factors.back().second;

        for (auto &[p, ee] : factors) {
            tot *= p;
            ee -= e;
        }

        while (!factors.empty() && factors.back().second == 0) {
            factors.pop_back();
        }

        ans += tot * e;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

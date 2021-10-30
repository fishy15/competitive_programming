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

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

ll ceil(ll x, ll y) {
    return (x + y - 1) / y;
}

void solve() {
    ll n; cin >> n;
    vector<ll> nums(n);
    vector<ll> x(n, 1);

    for (ll i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    mi ans = 0;
    mi cur_sum = 0;
    for (ll i = 0; i < n; i++) {
        ll cur_min = nums[i];

        ll j = i - 1;
        while (j >= 0 && ceil(nums[j], x[j]) > cur_min) {
            cur_sum -= (x[j] - 1) * (j + 1);
            x[j] = ceil(nums[j], cur_min);
            cur_sum += (x[j] - 1) * (j + 1);
            cur_min = nums[j] / x[j];
            j--;
        }

        ans += cur_sum;
    }
    
    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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

ll a1, a2;
ll b1, b2;
ll k;

vector<ll> nums;

void gen(ll x) {
    if (10 * x < 10000000000LL) {
        nums.push_back(10 * x + 3);
        gen(10 * x + 3);

        nums.push_back(10 * x + 8);
        gen(10 * x + 8);
    }
}

mi inter(ll x1, ll x2, ll y1, ll y2) {
    ll l = max(x1, y1);
    ll h = min(x2, y2);
    return max(0LL, h - l + 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> a1 >> a2;
    cin >> b1 >> b2;
    cin >> k;

    gen(0);

    sort(nums.begin(), nums.end());

    ll prev = 0;
    mi ans;
    for (ll i = 0; i + k < (int) nums.size(); i++) {
        // include the one at i, don't include the one at i + k
        ll low1 = prev + 1;
        ll low2 = nums[i];

        ll high1 = nums[i + k - 1];
        ll high2 = nums[i + k] - 1;

        ans += inter(low1, low2, a1, a2) * inter(high1, high2, b1, b2);
        ans += inter(low1, low2, b1, b2) * inter(high1, high2, a1, a2);

        prev = nums[i];
    }

    ans /= a2 - a1 + 1;
    ans /= b2 - b1 + 1;

    cout << ans.v << '\n';

    return 0;
}

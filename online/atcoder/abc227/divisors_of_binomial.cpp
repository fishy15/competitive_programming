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
#define MAXN 1000010

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

ll n, k;
ll low;
bool p[MAXN];
ll high[MAXN];
ll cnt[MAXN];

void factor(ll x) {
    ll st = (low + x - 1) / x * x;
    for (ll i = st - low; i < k; i += x) {
        while (high[i] % x == 0) {
            high[i] /= x;
            cnt[x]++;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    low = n - k + 1;
    for (int i = 0; i < k; i++) {
        high[i] = low + i;
    }

    for (ll i = 2; i < 1e6; i++) {
        if (p[i] == 0) {
            factor(i);

            for (ll j = i; j <= k; j += i) {
                p[j] = 1;

                ll x = j;
                while (x % i == 0) {
                    x /= i;
                    cnt[i]--;
                }
            }
        }
    }

    mi ans = 1;
    for (int i = 0; i < k; i++) {
        if (high[i] > 1) {
            ans *= 2;
        }
    }

    for (ll x : cnt) {
        ans *= x + 1;
    }

    cout << ans.v << '\n';

    return 0;
}

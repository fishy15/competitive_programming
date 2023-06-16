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
#define MAXN 200010

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

mi f[MAXN];
mi inv_f[MAXN];

mi c(int n, int k) {
    return f[n] * inv_f[k] * inv_f[n - k];
}

void precomp() {
    f[0] = 1;
    inv_f[0] = 1;

    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[MAXN - 1] = f[MAXN - 1].inv();
    for (int i = MAXN - 2; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

mi sum(int n, int p) {
    mi ans;
    if (p == 0) p = 1;
    else p = 2;
    for (int j = p; j <= n; j += p) {
        ans += c(n, j); 
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int n; cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<int> cnt(30);
    for (int x : nums) {
        int p = 0;
        while (p < 30 && (x % (1 << p)) == 0) p++;
        cnt[p - 1]++;
    }

    mi ans;
    int left = n;
    for (int i = 0; i < 30; i++) {
        left -= cnt[i];
        mi pair_odd = sum(cnt[i], i);
        ans += pair_odd * mi(2).pow(left);
        if (left == 0) break;
    }

    cout << ans.v << '\n';
    return 0;
}

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

int n, p;
int nums[MAXN];
set<int> done;
mi f[MAXN];

void precalc() {
    f[1] = 1;
    f[2] = 1;

    for (int i = 3; i < MAXN; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }

    for (int i = 2; i < MAXN; i++) {
        f[i] += f[i - 1];
    }
}

bool ok(int x) {
    while (x > 0) {
        if (done.count(x)) return false;

        if ((x & 1) == 1) {
            x >>= 1;
        } else if ((x & 3) == 0) {
            x >>= 2;
        } else {
            return true;
        }
    }

    return true;
}

int get_highest_bit(int x) {
    int p = 31;
    while ((x & (1 << p)) == 0) p--;
    return p;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    cin >> n >> p;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums, nums + n);

    mi ans;
    for (int i = 0; i < n; i++) {
        if (ok(nums[i])) {
            done.insert(nums[i]);
            int hb = get_highest_bit(nums[i]);
            if (hb < p) {
                ans += f[p - hb];
            }
        }
    }

    cout << ans.v << '\n';

    return 0;
}

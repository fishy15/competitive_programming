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
#define MAXN 200000

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

mi f[MAXN+1];
mi inv_f[MAXN+1];

void precomp() {
    f[0] = inv_f[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        f[i] = f[i-1] * i;
        inv_f[i] = f[i].inv();
    }
}

mi nPk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return f[n] * inv_f[n - k];
}

mi nCk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return nPk(n, k) * inv_f[k];
}

mi trans(int l_idx, int l_cnt, int r_idx, int r_cnt) {
    int init_unassigned = l_idx - l_cnt;

    int diff = r_cnt - l_cnt;
    int diff_idx = r_idx - l_idx;

    mi ans = 0;

    for (int i = 0; i <= init_unassigned && i <= diff_idx; i++) {
        int rem_diff = diff - i;
        int rem_opts = init_unassigned + diff_idx - i;
        if (rem_diff < 0 || rem_diff > diff_idx) {
            continue;
        }

        mi pick_earlier = nPk(init_unassigned, i) * nCk(diff_idx, i);
        mi pick_later = nPk(diff_idx, rem_diff) * nCk(rem_opts, rem_diff);
        ans += pick_earlier * pick_later;
    }

    return ans; 
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    if (nums[n-1] == -1) {
        nums[n-1] = n;
    } else if (nums[n-1] != n) {
        cout << "0\n";
        return;
    }

    mi ans = 1;
    int last_idx = 0;
    int last_val = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] != -1) {
            ans *= trans(last_idx, last_val, i+1, nums[i]);
            last_idx = i+1;
            last_val = nums[i];
        }
    }

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

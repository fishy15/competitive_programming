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

constexpr int MAXN = 5e5;
mi f[MAXN+1];
mi inv_f[MAXN+1];
mi dp[MAXN+1];

void precomp() {
    f[0] = inv_f[0] = 1;
    rep(i, 1, MAXN+1) {
        f[i] = f[i-1] * i;
    }
    inv_f[MAXN] = f[MAXN].inv();
    for (int i = MAXN - 1; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }

    dp[0] = 1;
    rep(i, 1, MAXN+1) {
        // pair with itself
        mi res = dp[i-1];

        // pair with something else
        if (i > 1) {
            res += dp[i-2] * (i - 1);
        }

        dp[i] = res;
    }
}

mi c(int n, int k) {
    if (k > n || k < 0) return 0;
    return f[n] * inv_f[k] * inv_f[n - k];
}

mi solve(vector<int> nums) {
    int n = sz(nums) - 1;
    rep(i, 0, n+1) {
        if (nums[i] > n) {
            return 0;
        }

        if (nums[i] != -1) { 
            if (nums[i] != 0) {
                if (nums[nums[i]] != -1 && nums[nums[i]] != i) {
                    return 0;
                }
            }
            nums[nums[i]] = i;
        }
    }

    auto empty = count(all(nums), -1);
    if (nums[0] == -1) {
        empty--;
    }

    // now, 0 can increase to be whatever it wants
    // everything besides n empty can map to zero
    auto could_zero = empty;
    mi ans = 0;
    rep(pair_within, 0, could_zero+1) {
        auto pick_pair = c(could_zero, pair_within);
        auto how_to_pair = dp[pair_within];
        ans += pick_pair * how_to_pair;
    }

    return ans;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n+1);
    rep(i, 0, n+1) {
        cin >> nums[i];
    }

    auto ans = solve(nums);
    nums[n] = 0;
    auto to_rem = solve(nums);
    ans -= to_rem;

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

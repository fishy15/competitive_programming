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

void precomp() {
    f[0] = 1;
    rep(i, 1, MAXN+1) {
        f[i] = f[i-1] * i;
    }
    inv_f[MAXN] = f[MAXN].inv();
    for (int i = MAXN-1; i >= 0; i--) {
        inv_f[i] = inv_f[i+1] * (i + 1);
    }
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    rep(i, 1, n) {
        if (nums[i-1] < nums[i]) {
            cout << "0\n";
            return;
        }
    }

    rep(i, 0, n) {
        if (!(n - i - 1 <= nums[i] && nums[i] <= n)) {
            cout << "0\n";
            return;
        }
    }

    set<int> s(all(nums));
    set<int> comp;
    rep(i, 0, n) {
        if (!s.count(i)) {
            comp.insert(i);
        }
    }

    mi ans = 1;
    int cur = 0;
    while (cur < n) {
        if (nums[cur] != n - cur) {
            ans *= n - nums[cur];
            cur++;
        } else {
            break;
        }
    }

    if (cur == n) {
        cout << ans.v << '\n';
        return;
    }

    int last = nums[cur];
    int spots = 0;
    while (cur < n) {
        if (nums[cur] != last) {
            // in the remaining spots, we need to have placed (nums[cur], last)
            for (int i = nums[cur] + 1; i < last; i++) {
                ans *= spots;
                spots--;
            }
            // for the current index, we can place any duplicate value
            ans *= cur + 1;
            last = nums[cur];
        } else {
            spots++;
        }
        cur++;
    }

    ans *= f[spots];

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    precomp();

    while (t--) {
        solve();
    }

    return 0;
}

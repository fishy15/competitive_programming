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

void solve() {
    int n;
    cin >> n;

    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    int q;
    cin >> q;
    vector<ll> xq(q), yq(q);
    for (int i = 0; i < q; i++) {
        cin >> xq[i] >> yq[i];
    }
    
    mi ans;

    sort(x.begin(), x.end());
    sort(xq.begin(), xq.end());
    sort(y.begin(), y.end());
    sort(yq.begin(), yq.end());

    // adds cubic sum of prior section
    auto process = [&ans](vector<ll> &x, vector<ll> xq, bool leq) {
        auto it = x.begin();

        mi lin_sum = 0;
        mi sq_sum = 0;
        mi cnt = 0;

        for (auto cur_x : xq) {
            while (it != x.end() && (*it <= cur_x) == leq) {
                lin_sum += mi(*it);
                sq_sum += mi(*it * *it);
                cnt += 1;
                it++;
            }

            /* cout << cnt.v << ' ' << lin_sum.v << ' ' << sq_sum.v << '\n'; */

            ans += cnt * cur_x * cur_x - lin_sum * cur_x * 2 + sq_sum;
        }
    };

    process(x, xq, true);
    process(y, yq, true);

    reverse(x.begin(), x.end());
    reverse(xq.begin(), xq.end());
    reverse(y.begin(), y.end());
    reverse(yq.begin(), yq.end());

    process(x, xq, false);
    process(y, yq, false);

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

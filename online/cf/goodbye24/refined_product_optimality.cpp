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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 998244353

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

struct sorted_idx {
    map<int, pair<int, int>> ints;
    // assume given a sorted one
    sorted_idx(const vector<int> &v) {
        rep(i, 0, sz(v)) {
            if (ints.count(v[i])) {
                ints[v[i]].second = i;
            } else {
                ints[v[i]] = {i, i};
            }
        }
    }

    int inc_value(int val) {
        assert(ints.count(val));

        auto [l, r] = ints[val];
        if (r - l + 1 == 1) {
            ints.erase(val);
        } else {
            ints[val] = {l, r-1};
        }

        if (ints.count(val+1)) {
            ints[val+1].first--;
        } else {
            ints[val+1] = {r, r};
        }

        return r;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n), b(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, n) {
        cin >> b[i];
    }

    auto asort = a;
    auto bsort = b;
    sort(all(asort));
    sort(all(bsort));

    mi P = 1;
    rep(i, 0, n) {
        P *= mi(min(asort[i], bsort[i]));
    }

    auto a_ord = sorted_idx(asort);
    auto b_ord = sorted_idx(bsort);

    cout << P.v << ' ';
    while (q--) {
        int o, x;
        cin >> o >> x;
        x--;
        if (o == 1) {
            int pos = a_ord.inc_value(a[x]);
            a[x]++;

            P /= min(asort[pos], bsort[pos]);
            asort[pos]++;
            P *= min(asort[pos], bsort[pos]);
        } else {
            int pos = b_ord.inc_value(b[x]);
            b[x]++;

            P /= min(asort[pos], bsort[pos]);
            bsort[pos]++;
            P *= min(asort[pos], bsort[pos]);
        }

        cout << P.v << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

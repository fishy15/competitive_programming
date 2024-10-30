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

struct segment {
    int base;
    int num_twos;
    mi total;
};

segment factor(int x) {
    mi orig = x;
    int cnt = 0;
    while (x % 2 == 0) {
        x /= 2;
        cnt++;
    }
    return {x, cnt, orig};
}

array<ll, 30> pows2{};

void precalc() {
    pows2[0] = 1;
    rep(i, 1, 30) {
        pows2[i] = pows2[i - 1] * 2;
    }
}

bool should_join(segment first, segment second) {
    // b1 <= b2 * 2^(twos2)
    if (second.num_twos >= 30) {
        return true;
    } else {
        auto base2 = second.base * pows2[second.num_twos];
        return first.base <= base2;
    }
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    mi base_sum;
    mi ans;
    vector<segment> st;
    for (auto x : nums) {
        auto cur = factor(x);
        base_sum += cur.base;
        while (!st.empty() && should_join(st.back(), cur)) {
            cur.num_twos += st.back().num_twos;
            ans -= st.back().total;
            st.pop_back();
        }
        cur.total = (mi(2).pow(cur.num_twos) - 1) * cur.base;
        ans += cur.total;
        st.push_back(cur);
        cout << (base_sum + ans).v << ' ';
        /*for (auto x : st) {*/
        /*    cout << x.base << ' ' << x.num_twos << " | ";*/
        /*}*/
        /*cout << '\n';*/
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

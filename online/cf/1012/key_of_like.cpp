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

constexpr int MAXN = 5000;
mi inv[MAXN+1];
vector<mi> at_step[MAXN+1];

void precomp() {
    for (int i = 1; i <= MAXN; i++) {
        inv[i] = mi(i).inv();
    }

    auto helper = [](int left) {
        vector<mi> ans;
        mi prob = 1;
        for (int i = 1; i <= left; i++) {
            auto cur = prob * inv[left - i + 1];
            ans.push_back(cur);
            prob -= cur;
        }
        return ans;
    };

    for (int i = 1; i <= MAXN; i++) {
        at_step[i] = helper(i);
    }
}

vector<mi> wrap(const vector<mi> &base, int size) {
    vector<mi> res(size);
    rep(i, 0, sz(base)) {
        res[i % size] += base[i];
    }
    return res;
}

void add(vector<mi> &a, mi scale, const vector<mi> &b) {
    rep(i, 0, sz(a)) {
        a[i] += scale * b[i];
    }
}

void solve() {
    int n, l, k;
    cin >> n >> l >> k;

    // if current person to move is 0, expected value
    vector if_start(n, mi(0));
    for (int left = 1; left <= l; left++) {
        auto probs = wrap(at_step[left], n);
        vector nxt = probs;
        rep(i, 0, n) {
            rotate(begin(if_start), end(if_start) - 1, end(if_start));
            add(nxt, probs[i], if_start);
        }
        if_start = nxt;
    }

    rep(i, 0, n) {
        cout << if_start[i].v << ' ';
    }
    cout << '\n';
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

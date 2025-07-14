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

struct node {
    int max_value;
    node *left, *right;
    node(int x) : max_value{x}, left{nullptr}, right{nullptr} {}
    node(node *l, node *r) : max_value{max(l->max_value, r->max_value)}, left{l}, right{r} {}

    template<typename F>
    void in_order(F f) {
        if (left == nullptr && right == nullptr) {
            f(max_value);
        } else {
            left->in_order(f);
            right->in_order(f);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> l(q), r(q);
    rep(i, 0, q) {
        cin >> l[i];
        l[i]--;
    }
    rep(i, 0, q) {
        cin >> r[i];
        r[i]--;
    }

    vector<node *> trees(n);
    rep(i, 0, n) {
        trees[i] = new node(i);
    }

    for (int i = q-1; i >= 0; i--) {
        auto mx = max(l[i], r[i]);
        auto mn = min(l[i], r[i]);
        trees[mx] = new node(trees[l[i]], trees[r[i]]);
        trees[mn] = nullptr;
    }

    vector<int> ord;
    trees[n-1]->in_order([&ord](int x) { ord.push_back(x); });

    vector<int> gaps;
    rep(i, 0, sz(ord)+1) {
        int max_side = 0;
        if (i > 0) {
            max_side = max(max_side, ord[i-1]);
        }
        if (i < sz(ord)) {
            max_side = max(max_side, ord[i]);
        }
        gaps.push_back(max_side);
    }

    sort(all(gaps));

    // if trees is not nullptr and not at the max, then it was untouched
    int unseen = 0;
    mi ans = 1;
    for (int i = n-2; i >= 0; i--) {
        if (trees[i] != nullptr) {
            auto it = lower_bound(all(gaps), i);
            auto works = (int) (end(gaps) - it);
            works += unseen;
            ans *= works;
            unseen++;
        }
    }

    cout << ans.v << '\n';

    return 0;
}

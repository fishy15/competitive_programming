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
#define MAXN 1000000

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : v(_v % MOD) {}

    mi operator+(const mi &other) const { return mi(v + other.v); }
    mi operator-(const mi &other) const { return mi(v - other.v); }
    mi operator*(const mi &other) const { return mi((ll) v * other.v); }

#define OP(op) \
    mi &operator op##=(const mi &other) { return *this = *this op other; }

    OP(+); OP(-); OP(*);

    mi pow(ll e) const {
        mi res = 1;
        mi cur = *this;
        while (e) {
            if (e & 1) res *= cur;
            cur *= cur;
            e >>= 1;
        }
        return res;
    }

    mi inv() const { return pow(MOD - 2); }
};

struct mi_cnt_zero {
    mi prod = 1;
    int cnt = 0;

    mi_cnt_zero(mi v) {
        if (v.v == 0) {
            cnt++;
        } else {
            prod = v;
        }
    }

    mi_cnt_zero(mi v, int c) : prod(v), cnt(c) {}

    mi_cnt_zero operator*(const mi_cnt_zero &other) const {
        return {prod * other.prod, cnt + other.cnt};
    }

    mi_cnt_zero operator/(const mi_cnt_zero &other) const {
        return {prod * other.prod.inv(), cnt - other.cnt};
    }

    mi extract() const {
        return cnt > 0 ? 0 : prod;
    }
};

struct block {
    set<int> locs_in_cc;
    set<int> present;
    map<int, int> chain_left, chain_right;
    mi prob_gone = mi(0);

    mi insert(int x) {
        auto [it, _] = present.insert(x);
        bool left_direct = false;
        bool right_direct = false;
        if (it != present.begin()) {
            chain_left[x] = chain_left[*prev(it)] + 1;

            // if direct previous thing has been added
            left_direct = (*prev(it) == *prev(locs_in_cc.find(x)));
        } else {
            chain_left[x] = 0;
            left_direct = (locs_in_cc.find(x) == locs_in_cc.begin());
        }

        if (next(it) != present.end()) {
            chain_right[x] = chain_right[*next(it)] + 1;

            // if direct next thing has been added
            right_direct = (*next(it) == *next(locs_in_cc.find(x)));
        } else {
            chain_right[x] = 0;
            right_direct = (next(locs_in_cc.find(x)) == locs_in_cc.end());
        }

        auto prob_side = mi(2).pow(chain_left[x] + chain_right[x] + 1).inv();
        mi res;
        if (left_direct) {
            res += prob_side;
        }
        if (right_direct) {
            res += prob_side;
        }

        prob_gone += res;
        return res;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, h;
    cin >> n >> h;

    vector<int> loc(n);
    vector<pair<int, int>> loc_sorted(n);
    for (int i = 0; i < n; i++) {
        cin >> loc[i];
        loc_sorted[i] = {loc[i], i};
    }

    sort(loc_sorted.begin(), loc_sorted.end());

    int num_cc = 0;
    vector<pair<int, int>> cc;
    vector<int> to_cc(n);
    vector<block> blocks;

    auto process_cc = [&] {
        block b;
        for (auto [v, i] : cc) {
            to_cc[i] = num_cc;
            b.locs_in_cc.insert(v);
        }

        blocks.push_back(b);
        num_cc++;
        cc.clear();
    };

    for (auto [x, i] : loc_sorted) {
        if (!cc.empty() && x - cc.back().first > h) {
            process_cc();
        }

        cc.push_back({x, i});
    }

    process_cc();

    vector<mi> ans(n);

    mi_cnt_zero prob_all_gone = mi(1);
    for (auto &b : blocks) {
        prob_all_gone = prob_all_gone * b.prob_gone;
    }

    for (int i = 0; i < n; i++) {
        auto &b = blocks[to_cc[i]];
        auto tmp_all_gone = prob_all_gone / b.prob_gone;

        ans[i] = b.insert(loc[i]) * tmp_all_gone.extract();

        prob_all_gone = tmp_all_gone * b.prob_gone;
    }

    mi total_prod = mi(2).pow(n);
    for (auto &x : ans) {
        cout << (x * total_prod).v << ' ';
    }
    cout << '\n';


    return 0;
}

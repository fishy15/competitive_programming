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
#define MOD 1000000009

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct mi {
    int v;
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : v(_v % MOD) {}

    mi operator+(const mi other) const { return mi(v + other.v); }
    mi operator-(const mi other) const { return mi(v - other.v); }
    mi operator*(const mi other) const { return mi((ll) v * other.v); }
    mi operator/(const mi other) const { return *this * other.inv(); }

    mi pow(ll e) const {
        mi ans = 1;
        mi b = *this;
        for (; e; b = b * b, e /= 2) 
            if (e & 1) ans = ans * b;
        return ans;
    }
    mi inv() const { return pow(MOD - 2); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m, k;
    cin >> m >> k;

    auto tot_nodes = [&](int i) {
        return mi((ll) m * i + 1);
    };

    auto tot_leaves = [&](int i) {
        return tot_nodes(i) - i;
    };

    mi sum_depths = 0;
    mi sum_leaf_depths = 0;
    for (int i = 1; i <= k; i++) {
        mi avg_leaf_depths = sum_leaf_depths / tot_leaves(i - 1);
        mi exp_new_leaf_depths = (avg_leaf_depths + 1) * m;
        sum_leaf_depths = (sum_leaf_depths - avg_leaf_depths) + exp_new_leaf_depths;
        sum_depths = sum_depths + exp_new_leaf_depths;
    }

    cout << sum_depths.v << '\n';

    return 0;
}

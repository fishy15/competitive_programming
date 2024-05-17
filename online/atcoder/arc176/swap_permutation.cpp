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

    mi operator+(const mi other) const { return mi(v + other.v); }
    mi operator-(const mi other) const { return mi(v - other.v); }
    mi operator*(const mi other) const { return mi((ll) v * other.v); }
    mi operator/(const mi other) const { return *this * other.inv(); }

#define OP(op) \
    mi &operator op##= (const mi other) { return *this = *this op other; }
    OP(+); OP(-); OP(*); OP(/);
#undef OP

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

struct M {
    const static int n = 3;
    mi mat[n][n];
    M operator*(const M &m2) const {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res[i][j] += mat[i][k] * m2[k][j];
                }
            }
        }
        return res;
    }
    mi *operator[](const int x) { return mat[x]; }
    const mi *operator[](const int x) const { return mat[x]; }
    M pow(ll e) const {
        M res = I();
        M cur = *this;
        while (e) {
            if (e & 1) res = res * cur;
            cur = cur * cur;
            e >>= 1;
        }
        return res;
    }
    static M I() {
        M m;
        for (int i = 0; i < n; i++) {
            m[i][i] = 1;
        }
        return m;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return p[i] < p[j];
    });

    array<int, 3> cnts = {0, 0, n-1};

    vector<int> zero_one(n, 1);
    mi inv2 = mi(2).inv();
    mi ans;
    for (int i = 0; i < n-1; i++) {
        auto idx = ord[i];

        if (idx > 0) {
            int prev_val = zero_one[idx-1] + zero_one[idx];
            cnts[prev_val]--;
            cnts[prev_val-1]++;
        }

        if (idx < n-1) {
            int nxt_val = zero_one[idx] + zero_one[idx+1];
            cnts[nxt_val]--;
            cnts[nxt_val-1]++;
        }

        zero_one[idx] = 0;

        // process this config
        int zeros = i+1;
        int ones = n - zeros;

        mi outside_combo = n > 3 ? mi(n - 2) * (n - 3) * inv2 : 0;
        auto mz = [](int x) { return max(x, 0); };

        M trans;

        // internal swap, internal zero swaps with external zero, external swap
        trans[0][0] = mi(1) + 2 * mz(zeros - 2) + outside_combo;
        // internal zero swaps with external one
        trans[0][1] = 2 * ones;
        // impossible
        trans[0][2] = 0;

        // internal one swaps with external zero
        trans[1][0] = mz(zeros - 1);
        // internal swap, zero swaps with zero or one swaps with one, external swap
        trans[1][1] = mi(1) + (mz(zeros - 1) + mz(ones - 1)) + outside_combo;
        // internal zero swaps with external one
        trans[1][2] = mz(ones - 1);

        // impossible
        trans[2][0] = 0;
        // internal one swaps with external zero
        trans[2][1] = 2 * zeros;
        // internal swap, internal one swaps with external one, external swap
        trans[2][2] = mi(1) + 2 * mz(ones - 2) + outside_combo;

        M init;
        init[0][0] = cnts[0];
        init[0][1] = cnts[1];
        init[0][2] = cnts[2];

        auto res = init * trans.pow(m);
        ans += res[0][1]; // different positions
    }

    cout << ans.v << '\n';

    return 0;
}

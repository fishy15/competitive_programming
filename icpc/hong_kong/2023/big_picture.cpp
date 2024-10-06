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

    mi operator+(mi other) const { return mi(v + other.v); }
    mi operator-(mi other) const { return mi(v - other.v); }
    mi operator*(mi other) const { return mi((ll) v * other.v); }

#define OP(op) \
    mi &operator op##= (mi other) { return *this = *this op other; }

    OP(+); OP(-); OP(*);
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector p(n, vector<mi>(m));
    vector q(n, vector<mi>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            p[i][j] = x;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            q[i][j] = x;
        }
    }

    vector ssum_right_p(n, vector<mi>(m+1));
    vector ssum_down_q(n+1, vector<mi>(m));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            ssum_right_p[i][j] = p[i][j] + ssum_right_p[i][j + 1];
            ssum_down_q[i][j]  = q[i][j] + ssum_down_q[i + 1][j];
        }
    }

    mi ans = 2;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            auto is_covered = ssum_right_p[i][j - 1] * ssum_down_q[i - 1][j];
            auto diag_not_covered = 
                (mi(1) - ssum_right_p[i - 1][j - 1]) * (mi(1) - ssum_down_q[i - 1][j - 1]);
            ans += is_covered * diag_not_covered;
        }
    }

    cout << ans.v << '\n';

    return 0;
}

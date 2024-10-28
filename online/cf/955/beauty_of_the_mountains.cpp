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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector a(n, vector<int>(m));
    for (auto &row : a) {
        for (auto &x : row) {
            cin >> x;
        }
    }

    vector<string> typ(n);
    for (auto &row : typ) {
        cin >> row;
    }

    ll cur_d = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (typ[i][j] == '1') {
                cur_d += a[i][j];
            } else {
                cur_d -= a[i][j];
            }
        }
    }

    cur_d = abs(cur_d);

    vector psum(n+1, vector<int>(m+1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            psum[i+1][j+1] = psum[i][j+1] + psum[i+1][j] - psum[i][j] + (typ[i][j] == '1' ? 1 : -1);
        }
    }

    int best = 0;
    for (int i = 0; i + k <= n; i++) {
        for (int j = 0; j + k <= m; j++) {
            int in_range = abs(psum[i+k][j+k] - psum[i][j+k] - psum[i+k][j] + psum[i][j]);
            best = gcd(best, in_range);
        }
    }

    if (cur_d == 0 || (best != 0 && cur_d % best == 0)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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

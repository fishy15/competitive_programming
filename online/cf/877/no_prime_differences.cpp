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
#define MAXN 1000

using namespace std;

bool p[MAXN + 1];

void precalc() {
    fill(begin(p), end(p), true);

    for (int i = 2; i <= MAXN; i++) {
        if (p[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                p[j] = false;
            }
        }
    }
}

// sequentially down each column
vector<vector<int>> get_normal(int n, int m, int rep) {
    vector ans(n, vector<int>(m));
    int cur = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[i][j] = cur + j;
        }

        cur += rep;
        if (cur >= n * m) {
            cur -= n * m;
        }
    }

    return ans;
}

vector<vector<int>> transpose(const vector<vector<int>> &v) {
    int n = v.size();
    int m = v[0].size();

    vector ans(m, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[j][i] = v[i][j];
        }
    }

    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> ans;
    if (!p[m]) {
        ans = get_normal(n, m, m);
    } else if (!p[n]) {
        ans = transpose(get_normal(m, n, n));
    } else {
        ans = get_normal(n, m, 2 * m);
    }

    for (auto &v : ans) {
        for (auto x : v) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
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

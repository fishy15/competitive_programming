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

bool eq(pair<int, int> a, pair<int, int> b) {
    return a == b;
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    rep(i, 2, n+1) {
        cin >> a[i];
    }

    vector<int> p(n + 1);
    rep(i, 1, n+1) {
        cin >> p[i];
    }

    int k = 0;
    while (((1 << k) - 1) != n) {
        k++;
    }

    vector<int> lg(n + 1);
    rep(i, 1, n+1) {
        if (2 * i <= n) lg[2 * i] = lg[i] + 1;
        if (2 * i + 1 <= n) lg[2 * i + 1] = lg[i] + 1;
    }

    vector<int> pre_p(n + 1);
    vector<int> d(n + 1);
    vector<array<int, 2>> pre_child(n + 1, {-1, -1});
    rep(i, 1, n+1) {
        if (d[i] < k - 1) {
            int child_size = (1 << (k - d[i] - 1)) - 1;
            pre_p[i + 1] = i;
            d[i + 1] = d[i] + 1;
            pre_p[i + 1 + child_size] = i;
            d[i + 1 + child_size] = d[i] + 1;
            pre_child[i] = {i + 1, i + 1 + child_size};
        }
    }

    vector<bool> ok(n);
    auto comp = [&](int idx) {
        if (d[idx] == k - 1) {
            // if we are a leaf, ok if our value is a leaf
            ok[idx] = lg[p[idx]] == k - 1;
        } else {
            int child_size = (1 << (k - d[idx] - 1)) - 1;
            auto lci = idx + 1;
            auto rci = lci + child_size;

            ok[idx] = false;
            if (lg[p[idx]] == d[idx] && ok[lci] && ok[rci]) {
                if (eq(minmax(p[lci], p[rci]), pair{2 * p[idx], 2 * p[idx] + 1})) {
                    ok[idx] = true;
                }
            }
        }
    };

    auto comp2 = [&](int idx) {
        while (idx > 0) {
            comp(idx);
            idx = pre_p[idx];
        }
    };

    for(int i = n; i >= 1; i--) {
        comp(i);
    }

    while (q--) {
        int x, y;
        cin >> x >> y;

        if (d[x] < d[y]) swap(x, y);

        swap(p[x], p[y]);
        comp2(x);
        comp2(y);

        /* cout << "cur state\n"; */
        /* for (int i = 1; i <= n; i++) cout << p[i] << ' '; */
        /* cout << '\n'; */
        /* for (int i = 1; i <= n; i++) cout << ok[i] << ' '; */
        /* cout << '\n'; */

        if (ok[1]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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

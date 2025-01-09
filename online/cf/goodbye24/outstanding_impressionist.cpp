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

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> ints(n);
    vector<int> forced(2*n+1);
    map<int, vector<int>> forcedm;
    rep(i, 0, n) {
        int l, r;
        cin >> l >> r;
        l--;
        ints[i] = {l, r};
        if (r - l == 1) {
            forced[r] = 1;
            forcedm[r].push_back(i);
        }
    }

    vector<bool> ans(n, true);
    for (const auto &[_, v] : forcedm) {
        if (sz(v) > 1) {
            for (auto x : v) {
                ans[x] = false;
            }
        }
    }

    auto psum = vector<int>(2*n+1);
    rep(i, 1, 2*n+1) {
        psum[i] = psum[i-1] + forced[i];
    }

    rep(i, 0, n) {
        auto [l, r] = ints[i];
        if (r - l > 1) {
            ans[i] = (r - l) != (psum[r] - psum[l]);
        }
    }

    for (auto x : ans) cout << x;
    cout << '\n';
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

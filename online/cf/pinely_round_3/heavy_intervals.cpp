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
    int n;
    cin >> n;

    vector<int> l(n), r(n), c(n);
    for (auto &x : l) {
        cin >> x;
    }
    for (auto &x : r) {
        cin >> x;
    }
    for (auto &x : c) {
        cin >> x;
    }

    vector<pair<int, int>> ops;
    for (auto x : l) {
        ops.push_back({x, 0});
    }
    for (auto x : r) {
        ops.push_back({x, 1});
    }

    sort(ops.begin(), ops.end());
    vector<int> lst;
    vector<int> szs;
    for (auto [x, t] : ops) {
        if (t == 0) {
            lst.push_back(x);
        } else {
            szs.push_back(x - lst.back());
            lst.pop_back();
        }
    }

    sort(szs.begin(), szs.end());
    sort(c.begin(), c.end(), greater<>());
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (ll) szs[i] * c[i];
    }
    cout << ans << '\n';
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

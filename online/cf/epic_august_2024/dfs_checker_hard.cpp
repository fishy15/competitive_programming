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
#include <chrono>
#include <random>
#include <cassert>

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
    int n, q;
    cin >> n >> q;

    vector<int> par(n);
    par[0] = -1;
    rep(i, 1, n) {
        cin >> par[i];
        par[i]--;
    }

    vector<int> p(n);
    vector<int> loc(n);
    rep(i, 0, n) {
        cin >> p[i];
        p[i]--;
        loc[p[i]] = i;
    }

    vector<set<int>> child_locs(n);
    vector<int> ssz(n, 1);
    for (int i = n-1; i >= 1; i--) {
        child_locs[par[i]].insert(loc[i]);
        ssz[par[i]] += ssz[i];
    }

    auto valid = [&](int x) {
        if (child_locs[x].empty()) {
            return 1;
        } else {
            auto first = *child_locs[x].begin();
            auto last = *child_locs[x].rbegin();
            auto res = loc[x] < first && last + ssz[p[last]] <= loc[x] + ssz[x];
            return res ? 1 : 0;
        }
    };

    int cnt_valid = 0;
    rep(i, 0, n) {
        if (valid(i)) {
            cnt_valid++;
        }
    }

    while (q--) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        auto a = p[x];
        auto b = p[y];

        set<int> to_check = {a, b, par[a], par[b]};

        for (auto x : to_check) {
            if (x != -1) {
                cnt_valid -= valid(x);
            }
        }
        if (par[a] != -1) child_locs[par[a]].erase(loc[a]);
        if (par[b] != -1) child_locs[par[b]].erase(loc[b]);

        swap(p[x], p[y]);
        swap(loc[a], loc[b]);

        if (par[a] != -1) child_locs[par[a]].insert(loc[a]);
        if (par[b] != -1) child_locs[par[b]].insert(loc[b]);
        for (auto x : to_check) {
            if (x != -1) {
                cnt_valid += valid(x);
            }
        }

        if (cnt_valid == n) {
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

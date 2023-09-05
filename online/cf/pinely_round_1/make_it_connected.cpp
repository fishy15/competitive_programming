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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) : dsu(n), sz(n) {
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
};

void check(int n, const vector<string> &grid, const vector<int> &ans) {
    vector<bool> flip(n);
    for (auto x : ans) {
        flip[x] = true;
    }

    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if ((grid[i][j] == '1') ^ flip[i] ^ flip[j]) {
                    dsu.join(i, j);
                }
            }
        }
    }

    assert(dsu.sz[dsu.find(0)] == n);
}

void solve() {
    int n;
    cin >> n;

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    DSU dsu(n);
    vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1') {
                deg[i]++;
                dsu.join(i, j);
            }
        }
    }

    vector<int> ans;
    goto skip;

ans_l:
    cout << ans.size() << '\n';
    if (!ans.empty()) {
        for (auto x : ans) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }

    return;

ans_lc:
    cout << ans.size() << '\n';
    if (!ans.empty()) {
        for (auto x : ans) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }

    check(n, grid, ans);
    return;

skip:
    // connected
    if (dsu.sz[dsu.find(0)] == n) {
        ans = {};
        goto ans_l;
    }

    map<int, int> head_to_sz;
    map<int, int> min_deg_cc;
    for (int i = 0; i < n; i++) {
        int cc = dsu.find(i);
        int cc_sz = dsu.sz[cc];
        head_to_sz[cc] = cc_sz;

        if (!min_deg_cc.count(cc)) {
            min_deg_cc[cc] = INF;
        }
        min_deg_cc[cc] = min(min_deg_cc[cc], deg[i]);

        // if cc is not complete, output that node
        // also if degree of node is 0 (singleton)
        if (deg[i] == 0) {
            ans = {i};
            goto ans_l;
        }

    }

    for (int i = 0; i < n; i++) {
        int cc = dsu.find(i);
        int cc_sz = dsu.sz[cc];
        if (deg[i] < cc_sz - 1 && deg[i] == min_deg_cc[cc]) {
            ans = {i};
            goto ans_lc;
        }
    }

    // if here, then every cc complete, no singletons
    if ((int) head_to_sz.size() == 2) {
        auto [cc1, sz1] = *head_to_sz.begin();
        auto [cc2, sz2] = *next(head_to_sz.begin());

        int min_cc = sz1 < sz2 ? cc1 : cc2;

        for (int i = 0; i < n; i++) {
            if (dsu.find(i) == min_cc) {
                ans.push_back(i);
            }
        }
        goto ans_l;
    } else {
        auto cc1 = head_to_sz.begin()->first;
        auto cc2 = next(head_to_sz.begin())->first;
        ans = {cc1, cc2};
        goto ans_l;
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

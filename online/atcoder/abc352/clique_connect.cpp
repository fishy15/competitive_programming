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

    bool join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
            return true;
        }
        return false;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, vector<int>>> ops;
    for (int i = 0; i < m; i++) {
        int k, c;
        cin >> k >> c;

        ops.push_back({c, {}});
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            x--;
            ops.back().second.push_back(x);
        }
    }

    sort(ops.begin(), ops.end(), [](const auto &a, const auto &b) {
        return a.first < b.first;
    });

    DSU dsu(n);

    ll ans = 0;
    for (auto &[c, vals] : ops) {
        int sz = vals.size();
        for (int i = 0; i < sz - 1; i++) {
            if (dsu.join(vals[i], vals[i + 1])) {
                ans += c;
            }
        }
    }

    for (int i = 1; i < n; i++) {
        if (dsu.find(i) != dsu.find(0)) {
            cout << "-1\n";
            return 0;
        }
    }
    
    cout << ans << '\n';

    return 0;
}

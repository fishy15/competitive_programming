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

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
};

int ask(int u) {
    cout << "? " << u + 1 << endl;

    int x;
    cin >> x;
    return x - 1;
}

void answer(vector<int> res) {
    cout << "! ";
    for (int x : res) {
        cout << x + 1 << ' ';
    }
    cout << endl;
}

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i].first;
        d[i].second = i;
    }

    DSU dsu(n);
    sort(d.begin(), d.end(), greater<>());
    vector<bool> vis(n);

    for (int i = 0; i < n; i++) {
        auto [dd, u] = d[i];
        if (!vis[u]) {
            vis[u] = true;
            for (int j = 0; j < dd; j++) {
                int v = ask(u);
                dsu.join(u, v);

                if (vis[v]) {
                    break;
                } else {
                    vis[v] = true;
                }
            }
        }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = dsu.find(i);
    }

    answer(ans);
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

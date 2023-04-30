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
#define MAXN 100010

using namespace std;

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) {
        dsu.resize(n);
        sz.resize(n);
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    n++;

    DSU dsu(n);
    vector<int> deg(n);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if (dsu.find(a) == dsu.find(b)) {
            cout << "NO\n";
            return 0;
        }
        dsu.join(a, b);
        deg[a]++;
        deg[b]++;

        if (deg[a] > 2 || deg[b] > 2) {
            cout << "NO\n";
            return 0;
        }
    }

    int k; cin >> k;
    multiset<int> blocks;

    for (int i = 0; i < k; i++) {
        int l, r; cin >> l >> r;
        blocks.insert(r - l + 1);
    }

    vector<int> szs;
    for (int i = 0; i < n; i++) {
        if (i == dsu.find(i)) {
            szs.push_back(dsu.sz[i]);
        }
    }

    sort(szs.begin(), szs.end(), greater<>());

    for (int x : szs) {
        auto it = blocks.lower_bound(x);
        if (it == blocks.end()) {
            cout << "NO\n";
            return 0;
        } else {
            blocks.erase(it);
        }
    }

    cout << "YES\n";

    return 0;
}

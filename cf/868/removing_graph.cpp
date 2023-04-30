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

struct mex_tracker {
    map<int, int> cnt;
    set<int> not_in;

    mex_tracker(int n) {
        for (int i = 0; i <= n + 1; i++) {
            not_in.insert(i);
        }
    }

    void add(int x) {
        if (cnt[x] == 0) {
            not_in.erase(x);
        }

        cnt[x]++;
    }

    void remove(int x) {
        cnt[x]--;

        if (cnt[x] == 0) {
            not_in.insert(x);
        }
    }

    int get_mex() const {
        return *not_in.begin();
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, l, r;
    cin >> n >> l >> r;

    DSU dsu(n);

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        dsu.join(a, b); 
    }

    vector<int> nimber(n + 1);
    mex_tracker cur(n);

    for (int i = 1; i <= n; i++) {
        if (i >= l) {
            cur.add(nimber[i]);
        }

        if (i >= r + 1) {
            cur.remove(nimber[i - r]);
        }

        nimber[i] = cur.get_mex();
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (i == dsu.find(i)) {
            res ^= nimber[dsu.sz[i]];
        }
    }

    if (res == 0) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
    }

    return 0;
}

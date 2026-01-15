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

struct DSU {
    vector<int> dsu, size, used;
    DSU(int n) : dsu(n), size(n, 1), used(n) {
        iota(all(dsu), 0);
    }
    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }
    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (size[x] < size[y]) swap(x, y);
            dsu[y] = x;
            size[x] += size[y];
            used[x] += used[y];
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<array<int, 3>> princess(m);
    for (auto &[c, a, b] : princess) {
        cin >> a >> b >> c;
        a--;
        b--;
    }

    sort(all(princess), greater<>{});

    DSU dsu(n);
    ll ans = 0;
    for (auto [c, a, b] : princess) {
        dsu.join(a, b);
        int p = dsu.find(a);
        if (dsu.used[p] < dsu.size[p]) {
            ans += c;
            dsu.used[p]++;
        }
    }

    cout << ans << '\n';

    return 0;
}

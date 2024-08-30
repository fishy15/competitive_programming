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
    vector<int> dsu, size;

    DSU(int n) : dsu(n), size(n, 1) {
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
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n);
    vector<pair<int, int>> ord;
    rep(i, 0, n) {
        cin >> nums[i];
        ord.push_back({nums[i], i});
    }

    sort(all(ord), greater<>{});

    DSU dsu(n);
    ll ans = 0;

    for (auto [h, i] : ord) {
        if (i > 0 && nums[i - 1] >= nums[i]) {
            dsu.join(i - 1, i);
        }

        if (i < n - 1 && nums[i + 1] >= nums[i]) {
            dsu.join(i, i + 1);
        }

        auto s = dsu.size[dsu.find(i)];
        ans = max(ans, (ll) s * h);
    }

    cout << ans << '\n';

    return 0;
}

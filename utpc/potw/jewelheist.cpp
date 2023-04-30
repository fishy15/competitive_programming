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

struct BIT {
    int n;
    vector<int> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void upd(int x, int v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    int qry(int x) {
        int ans = 0;
        while (x > 0) {
            ans += bit[x];
            x -= x & -x;
        }

        return ans;
    }

    // [l, r)
    int qry(int l, int r) {
        if (r <= l) return 0;
        return qry(r) - qry(l);
    }
};

void solve() {
    int n, k;
    cin >> n >> k;

    vector<array<int, 3>> pts(n);
    vector<int> xs;
    for (int i = 0; i < n; i++) {
        cin >> pts[i][0] >> pts[i][1] >> pts[i][2];
        pts[i][2]--;
        xs.push_back(pts[i][0]);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    auto get_x = [&](int x) { return lower_bound(xs.begin(), xs.end(), x) - xs.begin(); };

    map<int, vector<int>> at_y;
    for (int i = 0; i < n; i++) {
        pts[i][0] = get_x(pts[i][0]);
        at_y[pts[i][1]].push_back(i);
    }

    BIT below(xs.size());
    vector<set<int>> below_color_x(k);
    vector<bool> is_bad(n);

    int ans = 0;
    for (auto &[_, v] : at_y) {
        // add to below set
        for (auto cur : v) {
            auto [x, y, c] = pts[cur];
            if (below_color_x[c].count(x)) {
                is_bad[cur] = true;
            } else {
                below_color_x[c].insert(x);
            }
        }

        for (auto cur : v) {
            if (is_bad[cur]) continue;

            auto [x, y, c] = pts[cur];
            auto it = below_color_x[c].find(x);

            int l, r;
            if (it != below_color_x[c].begin()) {
                l = *prev(it) + 1;
            } else {
                l = 0;
            }

            if (next(it) != below_color_x[c].end()) {
                r = *next(it);
            } else {
                r = xs.size();
            }

            ans = max(ans, below.qry(l, r));
        }

        for (auto cur : v) {
            auto [x, y, c] = pts[cur];
            below.upd(x, 1);
        }
    }
    
    // above everything
    for (auto &v : below_color_x) {
        if (!v.empty()) {
            int sz = v.size();
            vector<int> vv(v.begin(), v.end());
            for (int i = 0; i < sz - 1; i++) {
                int l = vv[i] + 1;
                int r = vv[i + 1];
                ans = max(ans, below.qry(l, r));
            }

            // before
            ans = max(ans, below.qry(0, *v.begin()));
            // after
            ans = max(ans, below.qry(*v.rbegin() + 1, xs.size()));
        }
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

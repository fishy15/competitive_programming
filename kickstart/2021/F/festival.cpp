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
    vector<pair<ll, ll>> bit;
    BIT(int n) : n(n), bit(n + 1) {}

    ll bsearch(int k) {
        int idx = 0;
        pair<ll, ll> cur;
        for (int i = (1 << 20); i > 0; i >>= 1) {
            if (idx + i > n) continue;
            if (cur.second + bit[idx + i].second <= k) {
                cur.first += bit[idx + i].first;
                cur.second += bit[idx + i].second;
                idx += i;
            }
        }

        return cur.first;
    }

    void upd(int x, int h, int y) {
        x++;
        while (x <= n) {
            bit[x].first += h * y;
            bit[x].second += y;
            x += x & -x; 
        }
    }
};

void solve() {
    int d, n, k; cin >> d >> n >> k;
    vector<vector<array<int, 3>>> events(d + 2);
    vector<pair<int, int>> happy;

    for (int i = 0; i < n; i++) {
        int h, s, e; cin >> h >> s >> e;
        events[s].push_back({1, h, i});
        events[e + 1].push_back({-1, h, i});
        happy.push_back({h, i});
    }

    sort(happy.rbegin(), happy.rend());
    auto lb = [&](auto p) { 
        return lower_bound(happy.begin(), happy.end(), p, greater<>()) - happy.begin();
    };

    BIT bit(n);

    ll ans = 0;
    for (const auto &v : events) {
        for (auto e : v) {
            pair<int, int> p = {e[1], e[2]};
            int idx = lb(p);
            bit.upd(idx, e[1], e[0]);
        }

        ans = max(ans, bit.bsearch(k));
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

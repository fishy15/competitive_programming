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
    vector<ll> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void upd(int x, ll v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    ll qry(int x) {
        x++;
        ll ans = 0;
        while (x > 0) {
            ans += bit[x];
            x -= x & -x;
        }

        return ans;
    }

    // [l, r]
    ll qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }
};


void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> nums(n);
    array<BIT, 3> bits{BIT(n), BIT(n), BIT(n)};

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        bits[nums[i] - 1].upd(i, 1);
    }

    ll ans = 0;
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        x--;

        bits[nums[x] - 1].upd(x, -1);
        nums[x] = y;
        bits[nums[x] - 1].upd(x, 1);

        array<int, 3> first, second;
        for (int i = 0; i < 3; i++) {
            first[i] = bits[i].qry(0, z - 1);
            second[i] = bits[i].qry(z, n - 1);
        }

        auto cost = [](auto x) {
            return x[0] + 2 * x[1] + 3 * x[2];
        };

        auto fc = cost(first);
        auto sc = cost(second);

        auto &smaller = fc < sc ? first : second;
        auto &larger = fc < sc ? second : first;
        int diff = abs(fc - sc);

        int tot_swaps = 0;
        for (auto [a, b] : vector<array<int, 2>>{{0, 2}, {0, 1}, {1, 2}}) {
            int swaps = min({smaller[a], larger[b], diff / (2 * (b - a))});
            smaller[a] -= swaps;
            smaller[b] += swaps;
            larger[a] += swaps;
            larger[b] -= swaps;
            tot_swaps += swaps;
            diff -= 2 * (b - a) * swaps;
        }

        if (diff == 0) {
            ans += tot_swaps;
        } else{
            ans--;
        }
    }
    
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

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
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    BIT sum(n), one_cnt(n), two_cnt(n), one_pos(n), two_pos(n);

    for (int i = 0; i < n; i++) {
        sum.upd(i, nums[i]);

        if (nums[i] == 1) {
            one_cnt.upd(i, 1);
            one_pos.upd(i, i);
        } else {
            two_cnt.upd(i, 1);
            two_pos.upd(i, i);
        }
    }

    auto bsearch_left = [&](int t, int bound, int goal) {
        int l = 0;
        int r = bound;

        auto &cnt = t == 1 ? one_cnt : two_cnt;

        while (l <= r) {
            int m = (l + r) / 2;
            auto sum = cnt.qry(m, bound);

            if (sum < goal) {
                r = m - 1;
            } else if (sum == goal) {
                return m;
            } else {
                l = m + 1;
            }
        }
        
        return -1;
    };

    auto bsearch_right = [&](int t, int bound, int goal) {
        int l = bound;
        int r = n - 1;

        auto &cnt = t == 1 ? one_cnt : two_cnt;

        while (l <= r) {
            int m = (l + r) / 2;
            auto sum = cnt.qry(bound, m);

            if (sum < goal) {
                l = m + 1;
            } else if (sum == goal) {
                return m;
            } else {
                r = m - 1;
            }
        }
        
        return -1;
    };

    // move "total" of "t" to right of [l, r]
    auto move_left = [&](int t, int l, int r, int total) {
        auto &pos = t == 1 ? one_pos : two_pos;

        ll move_to_r = (ll) r * total - pos.qry(l, r);
        ll move_back = (ll) total * (total - 1)/ 2;
        return move_to_r - move_back;
    };

    // move "total" of "t" to left of [l, r]
    auto move_right = [&](int t, int l, int r, int total) {
        auto &pos = t == 1 ? one_pos : two_pos;

        ll move_to_l = pos.qry(l, r) - (ll) l * total;
        ll move_back = (ll) total * (total - 1)/ 2;
        return move_to_l - move_back;
    };

    ll ans = 0;
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        x--;

        if (nums[x] != y) {
            sum.upd(x, y - nums[x]);

            if (y == 1) {
                one_cnt.upd(x, 1);
                one_pos.upd(x, x);
                two_cnt.upd(x, -1);
                two_pos.upd(x, -x);
            } else {
                one_cnt.upd(x, -1);
                one_pos.upd(x, -x);
                two_cnt.upd(x, 1);
                two_pos.upd(x, x);
            }
        }

        nums[x] = y;

        auto first = sum.qry(0, z - 1);
        auto second = sum.qry(z, n - 1);

        int diff = abs(first - second);
        int t1 = first > second ? 2 : 1;
        int t2 = 3 - t1;

        if (diff == 0) {
            continue;
        } else if (diff % 2 != 0) {
            ans--;
            continue;
        } else {
            diff /= 2;
        }

        auto idx1 = bsearch_left(t1, z - 1, diff);
        auto idx2 = bsearch_right(t2, z, diff);

        if (idx1 == -1 || idx2 == -1) {
            ans--;
            continue;
        }

        auto cost1 = move_left(t1, idx1, z - 1, diff);
        auto cost2 = move_right(t2, z, idx2, diff);
        ans += (ll) cost1 + cost2 + (ll) diff * diff;
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

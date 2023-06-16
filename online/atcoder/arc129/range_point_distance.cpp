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
#define MAXN 200010

using namespace std;

int n;
array<int, 2> range[MAXN];

struct BIT {
    int n;
    vector<ll> bit;

    BIT(int n) : n(n), bit(n) {}

    void upd(int x, ll q) {
        x++;
        while (x <= n) {
            bit[x - 1] += q;
            x += x & -x;
        }
    }

    ll qry(int x) {
        ll res = 0;
        while (x > 0) {
            res += bit[x - 1];
            x -= x & -x;
        }
        return res;
    }

    ll qry(int x, int y) {
        return qry(y) - qry(x);
    }

    int bsearch(ll r) {
        int cur = 0;
        ll sum = 0;
        for (int i = (1 << 20); i > 0; i /= 2) {
            if (cur + i <= n && sum + bit[cur + i - 1] <= r) {
                cur += i;
                sum += bit[cur - 1];
            }
        }
        return cur;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    vector<int> both;

    for (int i = 0; i < n; i++) {
        cin >> range[i][0] >> range[i][1];
        range[i][0]--;

        both.push_back(range[i][0]);
        both.push_back(range[i][1]);
    }

    sort(both.begin(), both.end());
    both.erase(unique(both.begin(), both.end()), both.end());

    auto find_both = [&](int x) { return lower_bound(both.begin(), both.end(), x) - both.begin(); };

    BIT bit_l(both.size()), bit_r(both.size());
    /* BIT bit_lr(both.size()), bit_rl(both.size()); */
    BIT bit_both(both.size());

    BIT cnt_l(both.size()), cnt_r(both.size());

    for (int x : both) {
        cout << x << ' ';
    }
    cout << '\n';

    for (int i = 0; i < n; i++) {
        int a = find_both(range[i][0]);
        int b = find_both(range[i][1]);

        bit_l.upd(a, range[i][0]);
        cnt_l.upd(a, 1);

        bit_r.upd(b, range[i][1]);
        cnt_r.upd(b, 1);

        /* bit_lr.upd(a, range[i][1]); */
        /* bit_rl.upd(b, range[i][0]); */

        bit_both.upd(find_both(range[i][0]), 1);
        bit_both.upd(find_both(range[i][1]), 1);

        int bd = bit_both.bsearch(i + 1);
        ll x = both[bd];

        ll ans = 0;

        ans += cnt_r.qry(0, bd) * x - bit_r.qry(0, bd);
        cout << '\t' << cnt_r.qry(0, bd) * x << ' ' << bit_r.qry(0, bd) << '\n';
        /* ans -= cnt_l.qry(0, bd) * x - bit_lr.qry(0, bd); */

        ans += bit_l.qry(bd, both.size()) - cnt_l.qry(bd, both.size()) * x;
        cout << '\t' << bit_l.qry(bd, both.size()) << ' ' << cnt_l.qry(bd, both.size()) * x << '\n';
        /* ans -= bit_rl.qry(bd, both.size()) - cnt_r.qry(bd, both.size()) * x; */

        cout << x << '\n';
        cout << "bd: " << bd << ' ' << bit_r.qry(bd + 1, both.size()) << ' ' << bit_l.qry(0, bd) << '\n';
        for (int i = 0; i < (int) both.size(); i++) {
            cout << bit_l.qry(i, i + 1) << ' ';
        }
        cout << '\n';

        for (int i = 0; i < (int) both.size(); i++) {
            cout << bit_r.qry(i, i + 1) << ' ';
        }
        cout << '\n';

        for (int i = 0; i < (int) both.size(); i++) {
            cout << cnt_l.qry(i, i + 1) << ' ';
        }
        cout << '\n';

        for (int i = 0; i < (int) both.size(); i++) {
            cout << cnt_r.qry(i, i + 1) << ' ';
        }
        cout << '\n';

        cout << 'a' << ans << '\n';
    }

    return 0;
}

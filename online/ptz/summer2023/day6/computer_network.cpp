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

#define ll unsigned long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFULL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int get(ll num, int idx) {
    return (num >> idx) & 1;
}

ll best(ll low, ll high) {
    int cnt = 0;
    for (int i = 62; i >= 0; i--) {
        if (get(low, i) == get(high, i)) {
            if (get(low, i)) cnt++;
        } else {
            if ((low & ((1ULL << i) - 1)) == 0) {
                return cnt;
            } else {
                return cnt+1;
            }
        }
    }
    return cnt;
}

int highbit(ll x) {
    int ans = 0;
    while (x >> (ans + 1)) ans++;
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> a(n), b(n);
    for (auto &x : a) {
        cin >> x;
    }
    for (auto &x : b) {
        cin >> x;
    }

    vector<pair<ll, ll>> cur_b(n);
    for (int i = 0; i < n; i++) {
        cur_b[i] = {b[i], b[i]};
    }

    auto count_adds = [&] {
        ll min_needed = 0;
        ll max_needed = INFULL;

        for (int i = 0; i < n; i++) {
            auto [lo, hi] = cur_b[i];
            ll min_add = lo - a[i];
            ll max_add = hi - a[i];
            min_needed = max(min_add, min_needed);
            max_needed = min(max_add, max_needed);
        }

        if (min_needed > max_needed) {
            return pair{-1ULL, -1ULL};
        } else {
            return pair{min_needed, max_needed};
        }
    };

    // assume top num_divs bits are the same
    auto comp = [&](int mask, ll lo, ll hi) {
        ll base = lo >> mask;
        ll lo_base = lo & ((1ULL << mask) - 1);
        ll hi_base = hi & ((1ULL << mask) - 1);
        return base + best(lo_base, hi_base);
    };

    ll ans = INFULL;

    for (int num_divs = 0; num_divs <= 31; num_divs++) {
        auto add_ops = count_adds();
        if (add_ops.first != -1) {
            if (add_ops.first == 0) ans = min(ans, (ll) num_divs);
            else {
                auto [lo, hi] = add_ops;
                int mask = num_divs;

                ll nxt_up = (lo + (1ULL << mask)) & (~((1ULL << mask) - 1));
                ll two_up = nxt_up + (1ULL << mask);

                ll case1_hi = min(nxt_up - 1, add_ops.second);
                ans = min(ans, comp(mask, lo, case1_hi) + num_divs);

                if (nxt_up <= add_ops.second) {
                    ans = min(ans, comp(mask, nxt_up, min(two_up-1, add_ops.second)) + num_divs);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            cur_b[i].first *= 2;
            cur_b[i].second *= 2;
            cur_b[i].second++;
        }
    }

    if (ans == INFULL) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}

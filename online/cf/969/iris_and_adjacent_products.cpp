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

constexpr int B = 500;

int root(int x) {
    auto sq = (int) sqrt(x) - 1;
    while ((sq + 1) * (sq + 1) <= x) sq++;
    return sq;
}

struct query {
    int l, r, idx;
};

struct state {
    // if lower than sq then put into small
    // otherwise put k/x into big
    int k, sq;
    int total = 0;
    vector<int> small, big;
    state(int k) : k(k) {
        sq = root(k);
        small.resize(sq + 1);
        big.resize(sq + 1); 
    }

    void add(int x) {
        if (x <= sq) {
            small[x]++;
        } else {
            big[k / x]++;
        }
        total++;
    }

    void rem(int x) {
        if (x <= sq) {
            small[x]--;
        } else {
            big[k / x]--;
        }
        total--;
    }

    int check() const {
        int leftover_small = 0;
        int needed = 0;

        auto last_nonzero = sq;
        while (last_nonzero >= 0 && small[last_nonzero] == 0 && big[last_nonzero] == 0) {
            last_nonzero--;
        }

        auto total_big = accumulate(all(big), 0);

        rep(i, 1, sq+1) {
            leftover_small += small[i];
            leftover_small -= big[i];

            if (i == last_nonzero && total % 2 == 1 && 2 * (total_big - needed) > total && leftover_small % 2 == -1) {
                // extra thing for it to pair against
                leftover_small++;
            }

            if (leftover_small < 0) {
                auto conv = (-leftover_small + 1) / 2;
                needed += conv;
                leftover_small += 2 * conv;
            }
        }

        return needed;
    }
};

void solve() {
    int n, q, k;
    cin >> n >> q >> k;

    vector<int> b(n);
    rep(i, 0, n) {
        cin >> b[i];
    }

    vector<int> ans(q);
    vector<vector<query>> buckets((n + B - 1) / B);
    rep(i, 0, q) {
        int l, r;
        cin >> l >> r;
        l--;
        buckets[l / B].push_back({l, r, i});
    }

    rep(i, 0, sz(buckets)) {
        sort(all(buckets[i]), [](auto &q1, auto &q2) {
            return q1.r < q2.r;
        });
        state st(k);
        int cur_l = i * B;
        int cur_r = i * B;
        for (auto [l, r, idx] : buckets[i]) {
            while (cur_r < r) {
                st.add(b[cur_r]);
                cur_r++;
            }

            while (cur_l < l) {
                st.rem(b[cur_l]);
                cur_l++;
            }

            while (cur_l > l) {
                cur_l--;
                st.add(b[cur_l]);
            }

            ans[idx] = st.check();
        }
    }

    for (int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
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

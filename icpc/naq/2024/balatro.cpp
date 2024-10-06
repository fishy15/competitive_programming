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
#include <cassert>

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

// b is convex
// no such guarantee on a
vector<ll> conv(const vector<ll> a, const vector<ll> b) {
    vector<ll> ans(sz(a) + sz(b) - 1);

    // what offset do we start at and wh
    auto eval = [&](int a_idx, int loc) -> ll {
        if (loc < a_idx) {
            return -INF;
        }

        auto start_h = a[a_idx];
        auto pos = min(sz(b) - 1, loc - a_idx);
        return start_h + b[pos];
    };

    // when is the fn for j >= fn for i
    auto inter = [&](int i, int j) -> int {
        assert(i < j);

        int lo = j;
        int hi = j + sz(b);
        int ans = j + sz(b);
        while (lo <= hi) {
            int m = lo + (hi - lo) / 2;
            if (eval(i, m) <= eval(j, m)) {
                ans = m;
                hi = m - 1;
            } else {
                lo = m + 1;
            }
        }

        return ans;
    };

    // set up cht structure
    deque<int> dq;
    rep(sum, 0, sz(ans)) {
        if (sum < sz(a)) {
            int i = sum;
            while (sz(dq) >= 2 && inter(end(dq)[-1], i) <= inter(end(dq)[-2], end(dq)[-1])) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        /*
        for (auto x : dq) {
            cout << "(" << x << ", " << eval(x, sum) << ") ";
        }
        cout << endl;
        */
        while (sz(dq) >= 2 && eval(dq[0], sum) <= eval(dq[1], sum)) {
            dq.pop_front();
        }
        ans[sum] = eval(dq[0], sum);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    // is mult, value
    vector<pair<bool, ll>> cards;
    int num_mults = 0;
    rep(i, 0, n) {
        char typ;
        int x;
        cin >> typ >> x;
        if (!(typ == 'm' && x == 1)) {
            // ignore mult by 1 pretend they dont exist
            cards.push_back({typ == 'm', x});
            if (typ == 'm') num_mults++;
        }
    }

    k = min(k, num_mults);

    vector<vector<ll>> ans(k+1);
    ans[0] = {0};

    vector<ll> cur_add;

    auto perform_conv = [&] {
        sort(all(cur_add), greater<>{});

        vector<ll> b(sz(cur_add) + 1);
        rep(i, 0, sz(cur_add)) {
            b[i+1] = b[i] + cur_add[i];
        }

        for (auto &row : ans) {
            if (!row.empty()) {
                row = conv(row, b);
            }
        }

        /*
        cout << "conv" << endl;
        for (auto &row : ans) {
            for (auto x : row) cout << x << ' ';
            cout << endl;
        }
        cout << "done" << endl;
        */

        cur_add.clear();
    };

    auto perform_mult = [&](ll v) {
        for (int i = k-1; i >= 0; i--) {
            auto &cur = ans[i];
            auto &nxt = ans[i+1];
            rep(j, 0, sz(cur)) {
                while (sz(nxt) <= j+1) nxt.push_back(0);
                if (nxt[j+1] < v * cur[j]) {
                    nxt[j+1] = v * cur[j];
                }
            }
        }

        /*
        cout << "mult" << endl;
        for (auto &row : ans) {
            for (auto x : row) cout << x << ' ';
            cout << endl;
        }
        cout << "done" << endl;
        */
    };

    rep(i, 0, sz(cards)) {
        if (cards[i].first) {
            perform_conv();
            perform_mult(cards[i].second);
        } else {
            cur_add.push_back(cards[i].second);
        }
    }

    if (!cur_add.empty()) {
        perform_conv();
    }

    vector<ll> combans(n+1);
    rep(i, 0, k+1) {
        rep(j, 0, sz(ans[i])) {
            combans[j] = max(combans[j], ans[i][j]);
        }
    }

    rep(i, 1, n+1) {
        combans[i] = max(combans[i], combans[i-1]);
    }

    rep(i, 1, n+1) {
        cout << combans[i] << '\n';
    }

    return 0;
}

#include <iostream>
#include <map>
#include <vector>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;

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
    int qry(int r) {
        int res = 0;
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    map<int, vector<int>> at_val;
    rep(i, 0, n) {
        cin >> a[i];
        at_val[a[i]].push_back(i);
    }

    BIT bit(n);
    rep(i, 0, n) {
        bit.upd(i, 1);
    }

    int cur_size = n;
    ll ans = 0;
    for (auto it = at_val.rbegin(); it != at_val.rend(); it++) {
        vector<int> idxs;
        idxs.reserve(sz(it->second));
        for (auto x : it->second) {
            idxs.push_back(bit.qry(x));
        }

        ll cur_cost = 0;
        // cost of moving everything to the front
        rep(i, 0, sz(idxs)) {
            cur_cost += idxs[i] - i;
        }

        ll best_cost = cur_cost;
        for (int i = sz(idxs) - 1; i >= 0; i--) {
            auto back_idx = sz(idxs) - 1 - i;
            // flip to moving to the back
            cur_cost -= idxs[i] - i;
            cur_cost += (cur_size - 1 - back_idx) - idxs[i];
            best_cost = min(cur_cost, best_cost);
        }

        ans += best_cost;

        for (auto x : it->second) {
            bit.upd(x, -1);
        }
        cur_size -= sz(it->second);
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

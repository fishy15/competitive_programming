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

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) : dsu(n), sz(n, 1) {
        iota(dsu.begin(), dsu.end(), 0);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
};

bool check(const vector<pair<int, int>> &config, int n, int k) {
    int sz = n / k;

    int tot = 1;
    for (auto [_, c] : config) {
        tot *= c + 1;
    }

    int m = config.size();
    int cur_sum = 0;
    vector<int> cur_state(m);

    auto to_int = [&]() {
        int ff = 1;
        int res = 0;
        for (int i = 0; i < m; i++) {
            res += ff * cur_state[i];
            ff *= config[i].second + 1;
        }
        return res;
    };

    auto to_vec = [&](int x) {
        cur_sum = 0;
        for (int i = 0; i < m; i++) {
            cur_state[i] = x % (config[i].second + 1);
            x /= (config[i].second + 1);
            cur_sum += cur_state[i] * config[i].first;
        }
    };

    vector<bool> ok(tot);
    ok[0] = true;
    for (int i = 0; i < tot; i++) {
        if (ok[i]) {
            to_vec(i);
            auto psum = cur_sum;
            for (int j = 0; j < m; j++) {
                if (cur_state[j] < config[j].second) {
                    cur_state[j]++;
                    cur_sum += config[j].first;

                    int dd = cur_sum / sz - psum / sz;
                    if (dd == 0 || (dd == 1 && cur_sum % sz == 0)) {
                        ok[to_int()] = true;
                    }

                    cur_state[j]--;
                    cur_sum -= config[j].first;
                }
            }
        }
    }

    return ok.back();
}

void solve() {
    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        dsu.join(a, b);
    }

    array<int, 101> cnt{};
    for (int i = 0; i < n; i++) {
        if (i == dsu.find(i)) {
            cnt[dsu.sz[i]]++;
        }
    }

    vector<pair<int, int>> config;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] > 0) {
            config.push_back({i, cnt[i]});
        }
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            if (check(config, n, i)) {
                ans.push_back(i);
            }
        }
    }

    int sz = ans.size();
    for (int i = 0; i < sz; i++) {
        cout << ans[i];
        if (i < sz - 1) {
            cout << ' ';
        } else {
            cout << '\n';
        }
    }
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

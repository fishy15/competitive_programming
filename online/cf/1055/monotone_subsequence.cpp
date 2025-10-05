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

vector<int> nums;

vector<int> query(const vector<int> &idx) {
    cout << "? " << sz(idx) << ' ';
    for (auto x : idx) cout << x+1 << ' ';
    cout << endl;

#ifdef LOCAL
    int mx = -1;
    vector<int> res;
    for (auto x : idx) {
        if (nums[x] > mx) {
            res.push_back(x);
            mx = nums[x];
        }
    }
    return res;
#else
    int c;
    cin >> c;
    vector<int> res(c);
    rep(i, 0, c) {
        cin >> res[i];
        res[i]--;
    }
    return res;
#endif
}

void answer(const vector<int> &idx) {
    cout << "! ";
    for (auto x : idx) cout << x+1 << ' ';
    cout << endl;

#ifdef LOCAL
    if (sz(idx) > 1) {
        bool want = (nums[idx[0]] < nums[idx[1]]);
        rep(i, 1, sz(idx)-1) {
            bool have = (nums[idx[i]] < nums[idx[i+1]]);
            if (want != have) {
                cout << "BAD" << endl;
                return;
            }
        }
    }
    cout << "OK" << endl;
#endif
}

vector<int> get_path(int n, const vector<vector<int>> &adj) {
    vector<pair<int, int>> dp(sz(adj), {1, -1});
    rep(i, 0, sz(adj)) {
        for (auto x : adj[i]) {
            if (i < x) {
                dp[x] = max(dp[x], pair{dp[i].first + 1, i});
            }
        }
    }

    auto mx = max_element(all(dp));
    if (mx->first >= n) {
        int cur = mx - begin(dp);
        vector<int> idx = {};
        while (sz(idx) < n) {
            idx.push_back(cur);
            cur = dp[cur].second;
        }
        reverse(all(idx));
        return idx;
    }

    // no path found
    return {};
}

void solve() {
    int n;
    cin >> n;

#ifdef LOCAL
    nums.resize(n*n + 1);
    rep(i, 0, n*n+1) {
        cin >> nums[i];
        cout << nums[i] << ' ';
    }
    cout << endl;
#endif

    set<int> cur;
    rep(i, 0, n*n+1) {
        cur.insert(i);
    }

    vector adj(n*n+1, vector<int>{});
    vector radj(n*n+1, vector<int>{});

    auto add_edge = [&](int x, int y) {
#ifdef LOCAL
        cout << x+1 << " to " << y+1 << endl;
#endif
        adj[x].push_back(y);
        radj[y].push_back(x);
    };

    rep(i, 0, n) {
        if (cur.empty()) {
            break;
        }

        vector<int> left(all(cur));
        auto res = query(left);
        rep(i, 0, sz(res)) {
            rep(j, i+1, sz(res)) {
                add_edge(res[i], res[j]);
            }
            int end = (i < sz(res) - 1) ? res[i+1] : n*n+1;
            auto start_it = cur.upper_bound(res[i]);
            auto end_it = cur.lower_bound(end);
            for (auto it = start_it; it != end_it; it++) {
                add_edge(*it, res[i]);
            }
        }

        for (auto x : res) {
            cur.erase(x);
        }
        for (auto x : res) {
            for (auto y : cur) {
                if (y < x) {
                    add_edge(y, x);
                }
            }
        }
    }

    auto ans = get_path(n+1, adj);
    if (ans.empty()) {
        ans = get_path(n+1, radj);
    }

    answer(ans);
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

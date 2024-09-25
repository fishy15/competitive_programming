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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    rep(i, 0, n) {
        cin >> x[i];
    }

    vector<ll> psum(n + 1);
    partial_sum(all(x), psum.begin() + 1);

    vector cost(n+1, vector(n+1, INFLL));
    rep(i, 0, n) {
        int split = i;
        ll sum_up = 0;
        ll sum_down = 0;
        ll tot_up = 0;
        ll tot_down = 0;
        rep(j, i+1, n+1) {
            sum_down += (ll) (j-1) * x[j-1];
            tot_down += x[j-1];

            while (tot_up < tot_down) {
                sum_down -= (ll) split * x[split];
                sum_up += (ll) split * x[split];
                tot_down -= x[split];
                tot_up += x[split];
                split++;
            }

            auto cost_up = (ll) (split-1) * tot_up - sum_up;
            auto cost_down = sum_down - (ll) (split-1) * tot_down;
            cost[i][j] = cost_up + cost_down;
        }
    }

    vector cur_dp(n + 1, INFLL);
    vector nxt_dp(n + 1, INFLL);
    cur_dp[0] = 0;

    auto proc = [&](auto &&self, int l, int r, int x, int y) -> void {
        if (l < r && x < y) {
            auto m = l + (r - l) / 2;
            pair<ll, int> opt = {INFLL, m};
            rep(i, x, min(y, m)) {
                ckmin(opt, {cur_dp[i] + cost[i][m], i});
            }
            nxt_dp[m] = opt.first;
            self(self, l, m, x, opt.second+1);
            self(self, m+1, r, opt.second, y);
        }
    };

    rep(i, 0, k) {
        proc(proc, 0, n+1, 0, n);
        swap(cur_dp, nxt_dp);
    }

    cout << cur_dp[n] << '\n';

    return 0;
}

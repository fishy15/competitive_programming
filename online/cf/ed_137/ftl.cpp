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

    int p1; ll t1;
    cin >> p1 >> t1;

    int p2; ll t2;
    cin >> p2 >> t2;

    int h, s;
    cin >> h >> s;

    vector<ll> dp(h+1, INFLL);
    dp[0] = 0;

    auto process_iter = [&](int i, ll time) {
        if (time >= max(t1, t2)) {
            auto cnt1 = (time - t1) / t1;
            auto cnt2 = (time - t2) / t2;
            auto damage = cnt1 * (p1 - s) + cnt2 * (p2 - s) + (p1 + p2 - s);
            int nxt = (int) min<ll>(h, damage + i);
            ckmin(dp[nxt], dp[i] + time);
        }
    };

    // never do 2 at the same time again
    auto process_direct = [&](int i) {
        auto check = [&](ll t) {
            auto cnt1 = t / t1;
            auto cnt2 = t / t2;
            return cnt1 * (p1 - s) + cnt2 * (p2 - s) >= h-i;
        };

        ll l = 0;
        ll r = h * min(t1, t2);
        ll ans = -1;
        while (l <= r) {
            auto m = (l + r) / 2;
            if (check(m)) {
                r = m - 1;
                ans = m;
            } else {
                l = m + 1;
            }
        }
        ckmin(dp[h], dp[i] + ans);
    };

    rep(i, 0, h) {
        rep(iters, 1, h+1) {
            process_iter(i, iters*t1);
            process_iter(i, iters*t2);
        }
        process_direct(i);
    }

    cout << dp[h] << '\n';

    return 0;
}

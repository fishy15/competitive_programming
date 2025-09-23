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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> pts(n);
    for (auto &[x, y] : pts) {
        cin >> x >> y;
    }

    vector dist(n, vector(n, 0));
    rep(i, 0, n) {
        rep(j, 0, n) {
            dist[i][j] = abs(pts[i].first - pts[j].first) + abs(pts[i].second - pts[j].second);
        }
    }

    vector<int> min_dist(n, INF);
    rep(i, 0, n) {
        rep(j, 0, n) {
            if (i != j) {
                min_dist[i] = min(min_dist[i], dist[i][j]);
            }
        }
    }

    vector<set<int>> reachable(n);
    rep(i, 0, n) {
        set<int> cur;
        queue<int> q;
        q.push(i);
        cur.insert(i);

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            
            rep(v, 0, n) {
                if (dist[u][v] == min_dist[u] && !cur.count(v)) {
                    cur.insert(v);
                    q.push(v);
                }
            }
        }

        reachable[i] = cur;
    }

    vector<pair<int, bool>> groups;
    vector<bool> vis(n);
    rep(i, 0, n) {
        if (!vis[i]) {
            bool valid = true;
            for (auto x : reachable[i]) {
                if (reachable[x] != reachable[i]) {
                    valid = false;
                    goto end;
                }
            }

            for (auto x : reachable[i]) {
                for (auto y : reachable[i]) {
                    if (x != y && dist[x][y] != min_dist[x]) {
                        valid = false;
                        goto end;
                    }
                }
            }

end:
            if (valid) {
                groups.push_back({sz(reachable[i]), true});
                for (auto x : reachable[i]) {
                    vis[x] = true;
                }
            } else {
                groups.push_back({1, false});
                vis[i] = true;
            }
        }
    }

    int invalid = 0;
    vector<int> valid_grps;
    for (auto [x, valid] : groups) {
        if (valid) {
            valid_grps.push_back(x);
        } else {
            invalid += x;
        }
    }

    mi ans = 1;
    rep(i, 0, invalid) {
        ans *= n - i;
    }

    auto colors_left = n - invalid;
    vector dp(sz(valid_grps) + 1, vector<mi>(colors_left + 1));
    dp[0][colors_left] = ans;
    rep(i, 0, sz(valid_grps)) {
        auto x = valid_grps[i];
        rep(cl, 1, colors_left + 1) {
            if (cl >= x && x > 1) {
                mi prod = 1;
                rep(i, 0, x) prod *= cl - i;
                dp[i+1][cl - x] += dp[i][cl] * prod;
            }
            dp[i+1][cl - 1] += dp[i][cl] * cl;
        }
    }

    cout << accumulate(all(dp.back()), mi(0)).v << '\n';

    return 0;
}

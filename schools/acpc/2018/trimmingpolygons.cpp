#include <bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;

ll shoelace(const vector<pair<ll ,ll>> &pts) {
    int n = pts.size();
    auto nxt = [n](int x) {
        if (x + 1 == n) return 0;
        return x + 1;
    };

    ll area2 = 0;
    for (int i = 0; i < n; i++) {
        area2 += pts[nxt(i)].second * pts[i].first - pts[i].second * pts[nxt(i)].first;
    }
    
    return area2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<ll, ll>> pts(n);
    vector<ll> value(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].first >> pts[i].second >> value[i];
    }

    ll total_area = shoelace(pts);

    // if we delete between i -> j (keep i, j), ccw
    vector cost(n, vector<ll>(n));

    auto nxt = [n](int x) {
        if (x + 1 == n) return 0;
        return x + 1;
    };

    for (int l = 0; l < n; l++) {
        vector<pair<ll, ll>> curp = {pts[l], pts[nxt(l)]};

        ll sum_gain = value[nxt(l)];
        for (int r = nxt(nxt(l)); r != l; r = nxt(r)) {
            curp.push_back(pts[r]);

            auto area2 = shoelace(curp);
            cost[l][r] = sum_gain - area2;

            // for next
            sum_gain += value[r];
        }
    }

    // keep everything or keep nothing
    ll ans = max(total_area, accumulate(value.begin(), value.end(), 0LL));

    // start = a point we keep
    // end = last point that we kept
    for (int start = 0; start < n; start++) {
        vector<ll> dp(n, -INFLL);
        dp[start] = 0;
        ll prev = dp[start];
        for (int r = nxt(start); r != start; r = nxt(r)) {
            dp[r] = prev; // directly connect w/ previous kept so no harm
            for (int p = start; p != r; p = nxt(p)) {
                dp[r] = max(dp[r], dp[p] + cost[p][r]);
            }

            // suppose r is the last point
            ans = max(ans, total_area + (dp[r] + cost[r][start]));
            prev = dp[r];
        }

        ans = max(ans, *max_element(dp.begin(), dp.end()) + total_area);
    }

    cout << ans << '\n';

    return 0;
}

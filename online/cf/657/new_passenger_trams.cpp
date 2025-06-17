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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, h, m, k;
    cin >> n >> h >> m >> k;

    vector<ll> leave(n);
    rep(i, 0, n) {
        ll hi, mi;
        cin >> hi >> mi;
        auto t = hi * m + mi;
        leave[i] = t % (m / 2);
    }

    vector<pair<ll, int>> events;
    for (auto t : leave) {
        events.push_back({t+1 - (m/2), 1});
        events.push_back({t+1, 1});

        events.push_back({t+k - (m/2), -1});
        events.push_back({t+k, -1});
    }

    // check boundaries as well
    events.push_back({0, 0});
    events.push_back({m/2-1, 0});

    sort(all(events));
    int cnt = 0;
    pair<int, int> best = {INF, -1};
    rep(i, 0, sz(events)) {
        auto [t, typ] = events[i];
        cnt += typ;

        if (i == sz(events) - 1 || events[i+1].first != t) {
            if (0 <= t && t < (m / 2)) {
                best = min(best, {cnt, t});
            }
        }
    }

    auto overlap = [&](ll t, ll x) {
        t -= k;
        return t < x && x < (t + k);
    };

    auto t = best.second;
    vector<int> rem;
    rep(i, 0, n) {
        if (overlap(t - (m/2), leave[i]) || overlap(t, leave[i]) || overlap(t + (m/2), leave[i])) {
            rem.push_back(i);
        }
    }

    cout << sz(rem) << ' ' << t << '\n';
    for (auto x : rem) {
        cout << x+1 << ' ';
    }
    cout << '\n';

    return 0;
}

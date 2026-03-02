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
#include <optional>

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

ll fdiv(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
}

ll cdiv(ll a, ll b) {
    auto res = fdiv(a, b);
    if (a % b != 0) {
        res++;
    }
    return res;
}

ll isqrt(ll x) {
    ll res = sqrt(x);
    while (res*res > x) res--;
    while ((res+1)*(res+1) <= x) res++;
    return res;
}

ll get_count(ll cx, ll cy, ll r, array<ll, 8> &pts) {
    for (ll i = 0; i < 8; i += 2) {
        pts[i] -= cx;
    }
    for (ll i = 1; i < 8; i += 2) {
        pts[i] -= cy;
    }

    auto [x1, y1, x2, y2, x3, y3, x4, y4] = pts;

    auto get_dim = [&](ll y) {
        if (y > y1 || y < y3) {
            return optional<pair<ll, ll>>{};
        } else {
            auto dx = x1 - x3;
            auto dy = y1 - y3;
            auto from_bottom = y - y3;
            
            // we shift over by dx * from_bottom / dy
            auto left = x3 + cdiv(dx * from_bottom, dy);
            auto right = x4 + fdiv(dx * from_bottom, dy);
            if (left > right) {
                return optional<pair<ll, ll>>{};
            } else {
                return optional{pair{left, right}};
            }
        }
    };

    ll ans = 0;
    for (ll y = y3; y <= y1; y++) {
        if (abs(y) > r) continue;
        auto cur_r = isqrt(r*r - y*y);
        auto cur_l = -cur_r;

        auto range = get_dim(y);
        if (range) {
            auto l = max(cur_l, range->first);
            auto r = min(cur_r, range->second);
            if (l <= r) {
                ans += r - l + 1;
            }
        }
    }

    return ans;
}

void solve() {
    ll x, y, r;
    cin >> x >> y >> r;

    array<ll, 8> pts1, pts2;
    for (auto &a : pts1) {
        cin >> a;
    }
    for (auto &a : pts2) {
        cin >> a;
    }

    auto cnt1 = get_count(x, y, r, pts1);
    auto cnt2 = get_count(x, y, r, pts2);
    if (cnt1 > cnt2) {
        cout << "1\n";
    } else if (cnt1 < cnt2) {
        cout << "2\n";
    } else {
        cout << "3\n";
    }
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

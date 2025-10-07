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

ll ccw(pair<ll, ll> &a, pair<ll, ll> &b, pair<ll, ll> &c) {
    auto ab = pair{b.first - a.first, b.second - a.second};
    auto bc = pair{c.first - b.first, c.second - b.second};
    auto cross = ab.first * bc.second - ab.second * bc.first;
    return cross > 0;
}

vector<pair<ll, ll>> hull(const vector<ll> &y) {
    int n = sz(y);
    vector<pair<ll, ll>> st;
    rep(i, 0, n) {
        auto cur = pair{(ll) i, y[i]};
        while (sz(st) >= 2 && !ccw(end(st)[-2], end(st)[-1], cur)) {
            st.pop_back();
        }
        st.push_back(cur);
    }
    return st;
}

bool less_slope(pair<ll, ll> &a, pair<ll, ll> &b) {
    return a.first * b.second < b.first * a.second;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int r, c;
    cin >> r >> c;

    vector<ll> l(r), d(c);
    rep(i, 0, r) {
        cin >> l[i];
    }
    rep(i, 0, c) {
        cin >> d[i];
    }

    auto l_hull = hull(l);
    auto d_hull = hull(d);

    int lptr = 0;
    int dptr = 0;

    string ans;
    while (lptr < sz(l_hull) - 1 || dptr < sz(d_hull) - 1) {
        if (lptr == sz(l_hull) - 1) {
            ans += string((r + c - 2) - sz(ans), 'E');
            dptr = sz(d_hull) - 1;
        } else if (dptr == sz(d_hull) - 1) {
            ans += string((r + c - 2) - sz(ans), 'N');
            lptr = sz(l_hull) - 1;
        } else {
            auto l_slope = pair{
                l_hull[lptr+1].second - l_hull[lptr].second,
                l_hull[lptr+1].first - l_hull[lptr].first,
            };
            auto d_slope = pair{
                d_hull[dptr+1].second - d_hull[dptr].second,
                d_hull[dptr+1].first - d_hull[dptr].first,
            };

            if (less_slope(l_slope, d_slope)) {
                ans += string(l_slope.second, 'N');
                lptr++;
            } else {
                ans += string(d_slope.second, 'E');
                dptr++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}

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

struct fountain {
    ll x, y, idx;
};

struct state {
    pair<ll, ll> last;
    ll below;
};

// this implementation swapped the dimensions
// to account for it, the dimensions are swapped
void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    vector<fountain> fs(k);
    rep(i, 0, k) {
        cin >> fs[i].x >> fs[i].y;
        fs[i].x--;
        fs[i].y--;
        swap(fs[i].x, fs[i].y);
        fs[i].idx = i;
    }

    sort(all(fs), [](const auto &a, const auto &b) {
        return tie(a.x, a.y, a.idx) < tie(b.x, b.y, b.idx);
    });

    // do forward pass
    ll below = 0;
    pair<ll, ll> cur_end = {0, -1};
    vector<state> forw_info;
    forw_info.push_back({{0, -1}, 0});
    for (auto [x, y, _] : fs) {
        if (y >= cur_end.second) {
            ll h = n - cur_end.second - 1;
            ll d = x - cur_end.first;
            below += d * h;
            cur_end = {x, y};
        }
        forw_info.push_back({cur_end, below});
    }

    ll alpha = below + (m - cur_end.first) * (n - cur_end.second - 1);

    // backward pass
    deque<state> tail;
    vector<ll> ans(k);
    for (int i = k-1; i >= 0; i--) {
        auto [fx, fy] = forw_info[i].last;
        auto cur_below = forw_info[i].below;
        auto it = upper_bound(all(tail), forw_info[i], [](const auto &s1, const auto &s2) {
            return s1.last.second < s2.last.second;
        });
        if (it == end(tail)) {
            cur_below += (m - fx) * (n - fy - 1);
        } else {
            cur_below += (it->last.first - fx) * (n - fy - 1);
            cur_below += it->below;
        }

        auto [x, y, idx] = fs[i];
        ans[idx] = cur_below;

        // update deque
        while (!tail.empty() && y > tail.front().last.second) {
            tail.pop_front();
        }

        ll new_below;
        if (tail.empty()) {
            new_below = (m - x) * (n - y - 1);
        } else {
            new_below = (tail.front().last.first - x) * (n - y - 1) + tail.front().below;
        }
        tail.push_front({{x, y}, new_below});
    }

    cout << alpha << '\n';
    rep(i, 0, k) {
        cout << ans[i] - alpha << ' ';
    }
    cout << '\n';
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

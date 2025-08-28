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

ll move(char d, int k) {
    cout << "? " << d << ' ' << k << endl;
    ll res;
    cin >> res;
    if (res == -1) {
        exit(0);
    }
    return res;
}

void answer(int x, int y) {
    cout << "! " << x << ' ' << y << endl;
}

void solve() {
    int n;
    cin >> n;

    vector<pair<ll, ll>> pts(n);
    for (auto &[x, y] : pts) {
        cin >> x >> y;
    }

    constexpr ll K = 1'000'000'000;
    move('U', K);
    move('U', K);
    move('R', K);
    auto d1 = move('R', K);
    move('D', K);
    move('D', K);
    move('D', K);
    auto d2 = move('D', K);

    // check which point minimizes distance to (K, K)
    ll best_d1 = INFLL;
    pair<ll, ll> best_p1;
    for (auto p : pts) {
        auto dist = abs(p.first - K) + abs(p.second - K);
        if (dist < best_d1) {
            best_d1 = dist;
            best_p1 = p;
        }
    }

    // check which point minimizes distance to (K, -K)
    ll best_d2 = INFLL;
    pair<ll, ll> best_p2;
    for (auto p : pts) {
        auto dist = abs(p.first - K) + abs(p.second + K);
        if (dist < best_d2) {
            best_d2 = dist;
            best_p2 = p;
        }
    }

    // we know that (x + 2K) + (y + 2K) - p1.first - p1.second = d1
    auto xy_sum = d1 + best_p1.first + best_p1.second - 4 * K;

    // we know that (x + 2K) - (y - 2K) - p2.first + p2.second = d2
    auto xy_diff = d2 + best_p2.first - best_p2.second - 4 * K;

    auto x = (xy_sum + xy_diff) / 2;
    auto y = xy_sum - x;

    answer(x, y);
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

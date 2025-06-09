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
#include <ranges>

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
namespace R = std::ranges;
namespace V = std::ranges::views;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

template<R::range T>
vector<pair<int, int>> get_edges(const T &h) {
    vector<pair<int, int>> res;
    // numbers that are the max of the suffix ending at them so far
    vector<pair<int, int>> suff_max;
    for (auto [i, x] : V::enumerate(h)) {
        while (!suff_max.empty() && suff_max.back().first < x) {
            suff_max.pop_back();
        }

        if (!suff_max.empty()) {
            res.push_back({suff_max.back().second, i});
        }

        while (!suff_max.empty() && suff_max.back().first == x) {
            suff_max.pop_back();
        }

        suff_max.push_back({x, i});
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> h(n);
    rep(i, 0, n) {
        cin >> h[i];
    }

    auto negate_h = h | V::transform(negate<>{});

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        adj[i].push_back(i+1);
    }
    for (auto [x, y] : get_edges(h)) {
        adj[x].push_back(y);
    }
    for (auto [x, y] : get_edges(V::reverse(h))) {
        adj[n-y-1].push_back(n-x-1);
    }
    for (auto [x, y] : get_edges(negate_h)) {
        adj[x].push_back(y);
    }
    for (auto [x, y] : get_edges(V::reverse(negate_h))) {
        adj[n-y-1].push_back(n-x-1);
    }

    vector<int> dist(n, INF);
    dist[0] = 0;
    rep(i, 0, n) {
        for (auto nxt : adj[i]) {
            ckmin(dist[nxt], dist[i] + 1);
        }
    }

    cout << dist[n-1] << '\n';

    return 0;
}

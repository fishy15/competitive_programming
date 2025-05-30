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

using vi = vector<int>;
using pii = pair<int, int>;

vector<pair<int, int>> eulerWalk(vector<vector<pii>>& gr, int nedges, int src=0) {
    int n = sz(gr);
    vi D(n), its(n), eu(nedges);
    vector<pair<int, int>> ret, s = {{src, -1}};
    D[src]++; // to allow Euler paths, not just cycles
    while (!s.empty()) {
        auto x = s.back();
        int y, e, &it = its[x.first], end = sz(gr[x.first]);
        if (it == end){ ret.push_back(x); s.pop_back(); continue; }
        tie(y, e) = gr[x.first][it++];
        if (!eu[e]) {
            D[x.first]--, D[y]++;
            eu[e] = 1; s.push_back({y, e});
        }}
    for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
    return {ret.rbegin(), ret.rend()};
}

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> notes(n);
    vector<int> xs, ys;
    for (auto &[x, y] : notes) {
        cin >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
    }

    sort(all(xs));
    xs.erase(unique(all(xs)), end(xs));
    sort(all(ys));
    ys.erase(unique(all(ys)), end(ys));

    auto get_x = [&](int x) { return lower_bound(all(xs), x) - begin(xs); };
    auto get_y = [&](int y) { return lower_bound(all(ys), y) - begin(ys); };

    vector<vector<pair<int, int>>> adj(sz(xs) + sz(ys));
    rep(i, 0, n) {
        int x = get_x(notes[i].first);
        int y = get_y(notes[i].second) + sz(xs);
        adj[x].push_back({y, i});
        adj[y].push_back({x, i});
    }

    int src = 0;
    rep(i, 0, sz(adj)) {
        if (sz(adj[i]) % 2 == 1) {
            src = i;
            break;
        }
    }

    auto path = eulerWalk(adj, n, src);
    if (path.empty()) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        rep(i, 1, sz(path)) {
            cout << path[i].second+1 << ' ';
        }
        cout << '\n';
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

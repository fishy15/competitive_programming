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

optional<vector<bool>> find_two_coloring(const vector<vector<int>> &adj) {
    int n = sz(adj);

    queue<int> q;
    vector<bool> vis(n);
    vector<bool> color(n);

    q.push(0);
    vis[0] = true;

    while (!q.empty()) {
        auto u = q.front();
        q.pop();

        for (auto v : adj[u]) {
            if (vis[v]) {
                if (color[u] == color[v]) {
                    return optional<vector<bool>>{};
                }
            } else {
                vis[v] = true;
                color[v] = !color[u];
                q.push(v);
            }
        }
    }

    return color;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector adj(n, vector<int>());
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto two_color = find_two_coloring(adj);
    if (two_color) {
        auto tc = *two_color;
        queue<int> left, right;
        rep(i, 0, n) {
            if (tc[i]) {
                left.push(i);
            } else {
                right.push(i);
            }
        }

        cout << "Bob" << endl;

        rep(j, 0, n) {
            int a, b;
            cin >> a >> b;
            if (a > b) swap(a, b);
            if (!left.empty() && !right.empty()) {
                if (a == 1) {
                    auto lv = left.front();
                    left.pop();
                    cout << lv + 1 << ' ' << 1 << endl;
                } else {
                    auto rv = right.front();
                    right.pop();
                    cout << rv + 1 << ' ' << 2 << endl;
                }
            } else if (left.empty()) {
                auto non_one = a == 1 ? b : a;
                auto rv = right.front();
                right.pop();
                cout << rv + 1 << ' ' << non_one << endl;
            } else {
                auto non_two = a == 2 ? b : a;
                auto lv = left.front();
                left.pop();
                cout << lv + 1 << ' ' << non_two << endl;
            }
        }
    } else {
        cout << "Alice" << endl;
        rep(j, 0, n) {
            cout << "1 2" << endl;
            int i, c;
            cin >> i >> c; // ignore
        }
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

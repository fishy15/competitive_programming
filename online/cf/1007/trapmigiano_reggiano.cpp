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

void solve() {
    int n, st, en;
    cin >> n >> st >> en;
    st--;
    en--;

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> ord;

    vector<bool> vis(n);
    queue<int> q;
    vis[en] = true;
    q.push(en);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        ord.push_back(v);
        for (auto e : adj[v]) {
            if (!vis[e]) {
                vis[e] = true;
                q.push(e);
            }
        }
    }

    reverse(all(ord));
    for (auto x : ord) {
        cout << x+1 << ' ';
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

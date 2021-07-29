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
#include <stack>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 500010

using namespace std;

int n;
pair<int, int> part[MAXN];

bool solve(int pow) {
    vector<vector<array<int, 3>>> adj(1 << pow);
    vector<int> deg(1 << pow);
    vector<bool> vis(n);
    int start = -1;
    for (int i = 0; i < n; i++) {
        int a = part[i].first & ((1 << pow) - 1);
        int b = part[i].second & ((1 << pow) - 1);
        adj[a].push_back({b, i, 0});
        adj[b].push_back({a, i, 1});
        if (i == 0) start = a;
        deg[a]++;
        deg[b]++;
    }

    for (int i = 0; i < (1 << pow); i++) {
        if (deg[i] % 2 != 0) return false;
    }

    stack<array<int, 3>> st;
    st.push({start, -1});
    vector<pair<int, int>> path;
    while (!st.empty()) {
        auto [v, e, dir] = st.top();
        while (deg[v] && vis[adj[v][deg[v] - 1][1]]) {
            deg[v]--;
            adj[v].pop_back();
        }
        if (deg[v] == 0) {
            if (e >= 0) path.push_back({e, dir});
            st.pop();
        } else {
            auto [u, e2, d2] = adj[v][deg[v] - 1];
            vis[e2] = true;
            st.push({u, e2, d2});
        }
    }

    if (path.size() != n) return false;

    cout << pow << '\n';
    for (auto [e, dir] : path) {
        if (dir) {
            cout << 2 * e + 1 << ' ' << 2 * e + 2 << ' ';
        } else {
            cout << 2 * e + 2 << ' ' << 2 * e + 1 << ' ';
        }
    }
    cout << '\n';

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> part[i].first >> part[i].second;
    }

    int ans = 20;
    while (ans >= 0) {
        bool res = solve(ans);
        if (res) break;
        ans--;
    }

    return 0;
}

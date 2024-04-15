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

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    swap(n, m);

    vector<vector<pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        adj[l].push_back({r, x});
        adj[r].push_back({l, -x});
    }

    vector<bool> vis(n + 1);
    vector<ll> psum(n + 1);

    queue<int> q;
    int needed = 0;
    for (int i = 0; i <= n; i++) {
        if (vis[i]) continue;

        needed++;
        q.push(i);
        vis[i] = true;

        while (!q.empty()) {
            auto u = q.front();
            q.pop();

            for (auto [v, w] : adj[u]) {
                if (vis[v]) {
                    if (psum[u] + w != psum[v]) {
                        cout << "we bad at math too\n";
                        return 0;
                    }
                } else {
                    psum[v] = psum[u] + w;
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }

    if (needed == 1) {
        for (int i = 0; i < n; i++) {
            cout << psum[i + 1] - psum[i] << ' ';
        }
        cout << '\n';
    } else {
        cout << "at least we can do math\n";
    }

    return 0;
}

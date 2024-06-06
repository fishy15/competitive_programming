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

// change if necessary
#define MAXN 300000

using namespace std;

int p[MAXN+1];

void precomp() {
    for (int i = 2; i <= MAXN; i++) {
        if (p[i] == 0) {
            p[i] = i;
            for (ll j = (ll) i * i; j <= MAXN; j += i) {
                p[j] = i;
            }
        }
    }
}

vector<int> pf(int x) {
    vector<int> factors;
    while (x > 1) {
        factors.push_back(p[x]);
        x /= p[x];
    }

    sort(factors.begin(), factors.end());
    factors.erase(unique(factors.begin(), factors.end()), factors.end());
    return factors;
}

optional<vector<int>> shortest_path(int s, int t, const vector<vector<int>> &adj) {
    int n = adj.size();

    vector<int> par(n, -1);
    vector<bool> vis(n);

    queue<int> q;
    q.push(s);
    vis[s] = true;

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto e : adj[v]) {
            if (!vis[e]) {
                vis[e] = true;
                par[e] = v;
                q.push(e);
            }
        }
    }

    if (!vis[t]) {
        return optional<vector<int>>{};
    } else {
        vector<int> path;
        int cur = t;
        while (cur != -1) {
            path.push_back(cur);
            cur = par[cur];
        }

        reverse(path.begin(), path.end());
        return path;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    int s, t;
    cin >> s >> t;
    s--;
    t--;

    vector<int> factors;
    for (auto x : a) {
        auto f = pf(x);
        factors.insert(factors.end(), f.begin(), f.end());
    }

    sort(factors.begin(), factors.end());
    factors.erase(unique(factors.begin(), factors.end()), factors.end());

    auto get_f = [&](int x) { 
        auto idx = lower_bound(factors.begin(), factors.end(), x) - factors.begin();
        return idx + n;
    };

    vector<vector<int>> adj(n + factors.size());
    for (int i = 0; i < n; i++) {
        auto x = a[i];
        auto f = pf(x);
        for (auto p : f) {
            auto loc = get_f(p);
            adj[i].push_back(loc);
            adj[loc].push_back(i);
        }
    }

    auto path = shortest_path(s, t, adj);
    
    if (path) {
        vector<int> ans;
        for (auto x : *path) {
            if (x < n) {
                ans.push_back(x + 1);
            }
        }

        cout << ans.size() << '\n';
        for (auto x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}

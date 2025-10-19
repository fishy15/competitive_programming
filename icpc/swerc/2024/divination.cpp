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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n), radj(n);
    vector<int> deg(n);
    rep(i, 0, n) {
        int k;
        cin >> k;
        rep(_, 0, k) {
            int x;
            cin >> x;
            x--;
            adj[x].push_back(i);
            radj[i].push_back(x);
            deg[x]++;
        }
    }

    queue<int> q;
    rep(v, 0, n) {
        if (deg[v] == 0) {
            q.push(v);
        }
    }

    vector<int> ord;
    ord.reserve(n);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        ord.push_back(v);

        for (auto pr : radj[v]) {
            deg[pr]--;
            if (deg[pr] == 0) {
                q.push(pr);
            }
        }
    }


    reverse(all(ord));
    vector<int> dp(n, 1);
    rep(i, 0, n) {
        auto v = ord[i];
        for (auto x : adj[v]) {
            dp[x] = max(dp[x], dp[v] + 1);
        }
    }

    if (*max_element(all(dp)) == n) {
        cout << "1\n";
    } else {
        cout << "0\n";
    }
 
    return 0;
}

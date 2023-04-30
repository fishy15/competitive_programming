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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<int> deg(n);

    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int x; cin >> x;
            adj[x - 1].push_back(i);
            deg[i]++;
        }
    }

    priority_queue<int, vector<int>, greater<>> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    vector<int> ord;
    vector<int> nxt;
    while (!q.empty()) {
        int t = q.top();
        q.pop();
        ord.push_back(t);

        for (int e : adj[t]) {
            deg[e]--;
            if (deg[e] == 0) {
                if (t < e) {
                    q.push(e);
                } else {
                    nxt.push_back(e);
                }
            }
        }

        if (q.empty()) {
            for (int i : nxt) {
                q.push(i);
            }
            nxt.clear();
        }
    }

    if ((int) ord.size() != n) {
        cout << "-1\n";
    } else {
        int ans = 1;
        for (int i = 1; i < n; i++) {
            if (ord[i - 1] > ord[i]) {
                ans++;
            }
        }
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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
    int m = n;

    if (n % 2 == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (j - i < n / 2) {
                    cout << "1 ";
                } else if (j - i == n / 2) {
                    cout << "0 ";
                } else {
                    cout << "-1 ";
                }
            }
        }
        cout << '\n';
        return;
    }

    vector<set<int>> adj(m);
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i != j) {
                adj[i].insert(j);
            }
        }
    }

    deque<int> ord;
    function<void(int,int)> dfs = [&](int v, int p) {
        while (!adj[v].empty()) {
            int i = *adj[v].begin();
            adj[v].erase(i);
            adj[i].erase(v);
            dfs(i, v);
        }
        ord.push_front(v);
    };

    dfs(0, -1);

    for (int i = 0; i < (int)(ord.size()) - 1; i++) {
        int a = ord[i];
        int b = ord[i + 1];
        ans[a][b] = 1;
        ans[b][a] = -1;
    }

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (n % 2 == 0 && (i + j) == m) cout << "0 ";
            cout << ans[i][j] << ' ';
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}


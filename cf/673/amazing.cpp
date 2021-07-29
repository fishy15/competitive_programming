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
    vector<vector<int>> idx(n + 10);
    vector<int> val(n + 10);
    vector<int> app(n + 10, INF);

    for (int i = 1; i <= n; i++) {
        idx[i].push_back(-1);
        idx[i].push_back(n);
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        idx[x].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        sort(idx[i].begin(), idx[i].end());
        int sz = (int)(idx[i].size());
        int gap = 0;
        for (int j = 0; j < sz - 1; j++) {
            gap = max(gap, idx[i][j + 1] - idx[i][j]);
        }
        app[gap] = min(app[gap], i);
    }

    int ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = min(app[i], ans);
        if (ans == INF) {
            cout << "-1 ";
        } else {
            cout << ans << ' ';
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

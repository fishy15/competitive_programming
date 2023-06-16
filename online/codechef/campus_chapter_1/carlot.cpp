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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int m, n; cin >> m >> n;
    vector<int> l(m, INF);
    vector<int> r(m, 0);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == 'P') {
                l[i] = min(l[i], j);
                r[i] = max(r[i], j);
            }
        }
    }

    int cur = 0;
    int ans = 0;
    int prev = -1;
    
    while (cur < n) {
        while (l[cur] != INF) cur++;
        if (cur == n) {
            cout << ans << '\n';
            return;
        }

        if (prev != -1) {
            `
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

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

void solve() {
    int n, m, d;
    cin >> n >> m >> d;

    vector<int> p_inv(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        p_inv[x] = i;
    }

    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        a[i]--;
    }

    int ans = INF;
    for (int i = 0; i < m - 1; i++) {
        if (p_inv[a[i]] >= p_inv[a[i + 1]] || p_inv[a[i + 1]] > p_inv[a[i]] + d) {
            ans = 0;
            break;
        } else {
            int dist = p_inv[a[i + 1]] - p_inv[a[i]];
            int move_away = p_inv[a[i]] + (n - 1 - p_inv[a[i + 1]]);

            ans = min(ans, dist);
            if (move_away >= d - dist + 1) {
                ans = min(ans, d - dist + 1);
            }
        }
    }

    cout << ans << '\n';
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

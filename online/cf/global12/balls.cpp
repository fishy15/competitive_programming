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
    int n, k; cin >> n >> k;
    vector<pair<ll, ll>> pts;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pts.push_back({x, y});
    }

    for (int i = 0; i < n; i++) {
        ll max_d = 0;
        for (int j = 0; j < n; j++) {
            max_d = max(max_d, abs(pts[i].first - pts[j].first) + abs(pts[i].second - pts[j].second));
        }
        if (max_d <= k) {
            cout << "1\n";
            return;
        }
    }

    cout << -1 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

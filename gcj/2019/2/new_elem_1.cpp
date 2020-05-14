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

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> pts;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pts.push_back({x, y});
    }

    set<pair<int, int>> ans;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll dx = pts[i].first - pts[j].first;
            ll dy = pts[i].second - pts[j].second;

            if (dx != 0 && dy != 0 && (dx > 0) != (dy > 0)) {
                dx = abs(dx);
                dy = abs(dy);
                ll g = gcd(dx, dy);
                ans.insert({dx/g, dy/g});
            }
        }
    }

    cout << ans.size() + 1 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

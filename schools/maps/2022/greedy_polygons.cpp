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

    int n, d, g;
    cin >> n >> d >> g;

    vector<pair<int, int>> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].first >> pts[i].second;
    }

    auto leftmost = *min_element(pts.begin(), pts.end());
    sort(pts.begin(), pts.end(), [leftmost](auto a, auto b) {
        if (a == leftmost) return true;
        if (b == leftmost) return false;

        auto theta1 = atan2(a.second - leftmost.second, a.first - leftmost.first);
        auto theta2 = atan2(b.second - leftmost.second, b.first - leftmost.first);

        return theta1 < theta2;
    });

    // area of the shape
    ld ans = 0;
    
    for (int i = 0; i < n; i++) {
        int nxt = i + 1 == n ? 0 : i + 1;
        ans += pts[i].first * pts[nxt].second;
    }

    for (int i = 0; i < n; i++) {
        int nxt = i + 1 == n ? 0 : i + 1;
        ans -= pts[i].second * pts[nxt].first;
    }

    ans = fabs(ans) / 2.0;

    // perimeter
    ld p = 0;
    for (int i = 0; i < n; i++) {
        int nxt = i + 1 == n ? 0 : i + 1;
        p += hypot((ld) pts[i].first - pts[nxt].first, (ld) pts[i].second - pts[nxt].second);
    }

    ans += p * g * d;

    // circle
    ans += M_PI * (g * d) * (g * d);

    cout << fixed << setprecision(12) << ans << '\n';

    return 0;
}

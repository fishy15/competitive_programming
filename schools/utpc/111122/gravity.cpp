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

    int n;
    cin >> n;

    vector<pair<ll, ll>> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].first >> pts[i].second;
    }

    sort(pts.begin(), pts.end());

    auto gravity = [&](ld x) {
        ld g = 0;
        for (auto [l, m] : pts) {
            auto r = fabs(l - x);
            if (l < x) {
                g -= m / r / r;
            } else {
                g += m / r / r;
            }
        }
        return g;
    };

    cout << fixed << setprecision(12);
    for (int i = 0; i < n - 1; i++) {
        auto l = (ld) pts[i].first;
        auto r = (ld) pts[i + 1].first;

        for (int j = 0; j < 100; j++) {
            auto m = (l + r) / 2;
            auto g = gravity(m);
            if (g < 0) {
                l = m;
            } else {
                r = m;
            }
        }

        cout << l << '\n';
    }

    return 0;
}

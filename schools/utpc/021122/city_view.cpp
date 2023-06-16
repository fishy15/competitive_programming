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

#define PI 3.14159265358979323846

// change if necessary
#define MAXN 100010

using namespace std;

int n;
ld deg[MAXN];

ld calc(ld x, ld y) {
    ld d = y - x;
    while (d >= 360) d -= 360;
    while (d < 0) d += 360;
    return d;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        deg[i] = atan2(y, x) * 180 / PI;
        if (deg[i] < 0) deg[i] += 360;
    }

    sort(deg, deg + n);
    ld max_d = calc(deg[n - 1], deg[0]);

    for (int i = 0; i < n - 1; i++) {
        max_d = max(max_d, calc(deg[i], deg[i + 1]));
    }

    if (fabs(max_d) <= eps) {
        cout << "0\n";
    } else {
        cout << fixed << setprecision(12) << 360 - max_d << '\n';
    }

    return 0;
}

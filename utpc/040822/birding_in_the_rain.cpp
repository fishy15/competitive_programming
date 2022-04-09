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

ld rho, d;
ld rx, ry, rz;
ld vx, vy, vz;
ld x, y, z;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> rho >> d;
    cin >> rx >> ry >> rz;
    cin >> vx >> vy >> vz;
    cin >> x >> y >> z;

    ld t = d / hypot(hypot(vx, vy), vz);

    vx -= rx;
    vy -= ry;
    vz -= rz;

    ld vol = (fabs(x * y * vz) + fabs(x * vy * z) + fabs(vx * y * z)) * t;
    cout << fixed << setprecision(12) << vol * rho << '\n';

    return 0;
}

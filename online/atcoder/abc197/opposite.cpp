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

int n;
ld x, y;
ld op_x, op_y;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    cin >> x >> y;
    cin >> op_x >> op_y;

    ld cx = (x + op_x) / 2;
    ld cy = (y + op_y) / 2;

    x -= cx;
    y -= cy;

    ld ang = 2 * M_PI / n;
    ld nx = x * cos(ang) - y * sin(ang);
    ld ny = x * sin(ang) + y * cos(ang);

    nx += cx;
    ny += cy;

    cout << fixed << setprecision(12);
    cout << nx << ' ' << ny << '\n';

    return 0;
}

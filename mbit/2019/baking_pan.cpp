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

int n;
ll minx = INFLL, maxx = -INFLL;
ll miny = INFLL, maxy = -INFLL;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        ll a, b, c; cin >> a >> b >> c;
        minx = min(minx, a - c);
        maxx = max(maxx, a + c);
        miny = min(miny, b - c);
        maxy = max(maxy, b + c);
    }

    cout << (maxx - minx) * (maxy - miny) << '\n';

    return 0;
}

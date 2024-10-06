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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    ld last = INF;

    rep(i, 0, n) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        int ydiff = y2 - y1;
        int xdiff = x2 - x1;

        if (x1 < 0 && x2 > 0) {
            auto frac = (ld) -x1 / xdiff;
            auto up = frac * ydiff;
            auto y_inter = y1 + up;
            if (y_inter > 0) {
                last = min(last, y_inter);
            }
        }
    }

    if (last == INF) {
        cout << "-1.0\n";
    } else {
        cout << fixed << setprecision(10);
        cout << last << endl;
    }

    return 0;
}

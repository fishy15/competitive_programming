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

struct frac {
    ll x, y;
    void trip() {
        x *= 3;
    }
    bool mid() const {
        return x > y && x < 2 * y;
    }
    void norm() {
        while (x > y) x -= y;
    }
};

frac read() {
    int x, y;
    cin >> x >> y;
    return frac{x, y};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int L;
    frac x, y, z;

    cin >> L;
    x = read();
    y = read();
    z = read();

    rep(i, 0, L) {
        x.trip();
        y.trip();
        z.trip();
        int mid_count = 0;
        mid_count += x.mid();
        mid_count += y.mid();
        mid_count += z.mid();

        if (mid_count >= 2) {
            cout << "0\n";
            return 0;
        }

        x.norm();
        y.norm();
        z.norm();
    }

    cout << "1\n";

    return 0;
}

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
#include <optional>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

namespace quad {
    optional<pair<ld, ld>> intersect(ld a, ld b, ld c, ld y) {
        c -= y;

        auto discrim = b * b - 4 * a * c;
        if (discrim < 0) return {};

        discrim = sqrt(discrim);
        return minmax({(-b - discrim) / (2 * a), (-b + discrim) / (2 * a)});
    }

    ld integrate(ld a, ld b, ld c, ld x1, ld x2) {
        auto f = [a, b, c](ld x) {
            return a / 3 * x * x * x + b / 2 * x * x + c * x;
        };

        return f(x2) - f(x1);
    }

    ld below(ld a2, ld a1, ld a0, ld x1, ld x2, ld y) {
        a0 -= y;
        auto inter = intersect(a2, a1, a0, 0);
        if (inter) {
            auto low = max(x1, inter->first);
            auto high = min(x2, inter->second);
            if (low >= high) return 0;
            auto res = integrate(a2, a1, a0, low, high);
            return res;
        } else {
            return 0;
        }
    }

    ld in_box(ld a2, ld a1, ld a0, ld x1, ld y1, ld x2, ld y2) {
        return below(a2, a1, a0, x1, x2, y1) - below(a2, a1, a0, x1, x2, y2);
    }

    ld curve_area(ld a2, ld a1, ld a0, ld x1, ld y1, ld x2, ld y2, ld k) {
        if (a1 > 0) {
            a2 *= -1;
            a1 *= -1;
            a0 *= -1;

            y1 *= -1;
            y2 *= -1;
            swap(y1, y2);
        }

        return in_box(a2, a1, a0 + k, x1, y1, x2, y2) - in_box(a2, a1, a0 - k, x1, y1, x2, y2);
    }
}

namespace line {
    ld in_box(ld m, ld k, ld x1, ld y1, ld x2, ld y2) {
        if (fabs(m) <= eps) {
            ld aup = m + k;
    ld adown = m - k;
    if(adown > max(y1, y2) || aup < min(y1, y2)){
        return 0;
    }
    return (x2-x1)*(min(max(y1, y2),aup) - max(min(y1, y2), adown));
        }

        auto inter_left = max(x1, (-k + y1) / m);
        auto inter_right = min(x2, (-k + y2) / m);

        if (y1 <= m * x1 + k && m * x1 + k <= y2) {
            ll x = 1 / 0;
            return x;
        }
    }

    ld curve_area(ld m, ld k, ld x1, ld y1, ld x2, ld y2, ld kk) {
        if (m > 0) {
            m *= -1;
            k *= -1;

            y1 *= -1;
            y2 *= -1;
            swap(y1, y2);
        }

        return in_box(m, k + kk, x1, y1, x2, y2) - in_box(m, k - kk, x1, y1, x2, y2);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll a2, a1, a0;
    cin >> a2 >> a1 >> a0;

    ll k;
    cin >> k;

    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    ld area = (x2 - x1) * (y2 - y1);
    if (a2 != 0) {
        area -= quad::curve_area(a2, a1, a0, x1, y1, x2, y2, k);
    } else if (a1 != 0) {
        area -= line::curve_area(a1, a0, x1, y1, x2, y2, k);
    }

    cout << fixed << setprecision(10) << area << '\n';

    return 0;
}

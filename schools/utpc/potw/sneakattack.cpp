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
#include <sstream>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct point {
    ld x, y;
    point operator+(const point &p2) const {
        return {x + p2.x, y + p2.y};
    }
    point operator-(const point &p2) const {
        return {x - p2.x, y - p2.y};
    }
    point operator*(ld d) const {
        return {x * d, y * d};
    }
    bool operator==(const point &p2) const {
        return x == p2.x && y == p2.y;
    }
    bool operator<(const point &p2) const {
        if (x == p2.x) return y < p2.y;
        return x < p2.x;
    }
    ld norm() const {
        return sqrt(x * x + y * y);
    }
    point normalize() const {
        ld sz = norm();
        return {x / sz, y / sz};
    }
};

ld dot(const point &a, const point &b) {
    return a.x * b.x + a.y * b.y;
}

point refl(const point &d, const point &n) {
    if (dot(d, n) == 0) {
        return d * -1;
    } else {
        return d - n * (2 * dot(d, n));
    }
}

void solve(ld mx1, ld my1, ld mx2, ld my2, ld x, ld y) {
    // flip mirror to positive side
    if (mx1 < 0) {
        mx1 *= -1;
        mx2 *= -1;
        x *= -1;
    }

    point m1 = {mx1, my1};
    point m2 = {mx2, my2};

    point m_vec = m1 - m2;
    point m_norm = point{m_vec.y, -m_vec.x}.normalize();

    point start = {x, y};

    point refl1 = refl((m1 - start).normalize(), m_norm);
    point refl2 = refl((m2 - start).normalize(), m_norm);

    auto inf = numeric_limits<ld>::infinity();
    auto is_inf = [inf](ld x) { return x == inf || x == -inf; };

    auto calc = [&](point m, point r) {
        if (r.x > -eps) {
            ld sign = r.y == 0 ? 1 : r.y / fabs(r.y);
            return sign * inf;
        } else {
            return m.x / -r.x * r.y + m.y;
        }
    };

    auto pr = [inf](ld x) {
        if (x == inf) {
            cout << "positive-infinity";
        } else if (x == -inf) {
            cout << "negative-infinity";
        } else {
            cout << x;
        }
    };

    ld res1 = calc(m1, refl1);
    ld res2 = calc(m2, refl2);
    if (res1 > res2) swap(res1, res2);

    if (is_inf(res1) && is_inf(res2)) {
        cout << "can't hit the wall\n";
    } else {
        pr(res1);
        cout << ' ';
        pr(res2);
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cout << fixed << setprecision(10);

    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        ld x1, y1, x2, y2, x3, y3;
        ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        solve(x1, y1, x2, y2, x3, y3);
    }

    return 0;
}

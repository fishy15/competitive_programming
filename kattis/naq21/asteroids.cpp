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
#define eps 1e-6
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

// comparison operators
inline bool ge(ld a, ld b) {
    return a - b > eps;
}

inline bool eq(ld a, ld b) {
    return fabs(a - b) <= eps;
}

inline bool geq(ld a, ld b) {
    return ge(a, b) || eq(a, b);
}

struct V {
    ld x, y, z;
    V() : V(0, 0, 0) {}
    V(ld x, ld y, ld z) : x(x), y(y), z(z) {}

    V operator+(const V &v2) const {
        return {x + v2.x, y + v2.y, z + v2.z};
    }

    V operator-(const V &v2) const {
        return {x - v2.x, y - v2.y, z - v2.z};
    }

    V operator*(ld r) const {
        return {x * r, y * r, z * r};
    }

    V operator/(ld r) const {
        return {x / r, y / r, z / r};
    }

    ld dot(const V &v2) const {
        return x * v2.x + y * v2.y + z * v2.z;
    }

    V cross(const V &v2) const {
        return {
            y * v2.z - v2.y * z,
            z * v2.x - v2.z * x,
            x * v2.y - v2.x * y
        };
    }

    ld norm() const {
        return sqrt(x * x + y * y + z * z);
    }

    ld norm_sq() const {
        return x * x + y * y + z * z;
    }

    bool parallel(const V &v2) const {
        return eq(dot(v2), norm() * v2.norm());
    }

    bool antiparallel(const V &v2) const {
        return eq(dot(v2), -norm() * v2.norm());
    }

    bool perpendicular(const V &v2) const {
        return eq(dot(v2), 0);
    }
};

struct asteroid {
    V p, d;
    ld r;

    asteroid(V p, V d, const vector<V> &pts) : p(p), d(d) {
        r = 0;
        for (auto v : pts) {
            r = max(r, (v - p).norm()); 
        }
    }
};


bool between(ld x1, ld x2, ld y) {
    if (x1 > x2) swap(x1, x2);
    return geq(y, x1) && geq(x2, y);
}

bool between(V x1, V x2, V y) {
    return between(x1.x, x2.x, y.x)
        && between(x1.y, x2.y, y.y)
        && between(x1.z, x2.z, y.z);
}

// closest point on line a + vt to b
V closest_point_on_line(V a, V v, V x) {
    ld t = (x - a).dot(v) / v.norm_sq();
    return a + v * t;
}

// dist to closest point on line a + vt to b
ld dist_closest_point_on_line(V a, V v, V x) {
    return (closest_point_on_line(a, v, x) - x).norm();
}

// closest point on line a1 + v1t to a2 + b1t and vice versa
pair<V, V> closest_point_on_line(V a1, V v1, V a2, V v2) {
    V orig_v1 = v1;
    V orig_v2 = v2;

    V v3 = v1.cross(v2);
    v2 = v2 * -1;

    V a = a2 - a1;

    // simulated gaussian elimination
    {
        ld x = v1.x;
        v1 = v1 / x;
        a.x /= x;

        x = v2.x;
        v2 = v2 - v1 * x;
        a.y = a.y - a.x * x;

        x = v3.x;
        v3 = v3 - v1 * x;
        a.z = a.z - a.x * x;
    }

    {
        ld y = v2.y;
        v2 = v2 / y;
        a.y = a.y / y;

        y = v3.y;
        v3 = v3 - v2 * y;
        a.z = a.z - a.y * y;
    }

    {
        ld z = v3.z;
        v3 = v3 / z;
        a.z = a.z / z;
    }

    {
        ld z = v2.z;
        a.y -= z * a.z;
    }

    {
        ld y = v1.y;
        ld z = v1.z;
        a.x -= a.y * y + a.z * z;
    }

    return {a1 + orig_v1 * a.x, a2 + orig_v2 * a.y};
}

inline bool within(V a, V b, ld r) {
    return geq(r, (a - b).norm());
}

// project u onto v
V proj(V u, V v) {
    return v * (u.dot(v) / v.norm_sq());
}

// check if line segment goes through sphere
bool sphere(V s, V b, asteroid a) {
    V close = closest_point_on_line(s, b - s, a.p);
    if (between(s, b, close)) {
        if (within(close, a.p, a.r)) {
            return true;
        }
    }

    if (within(s, a.p, a.r)) {
        return true;
    }

    if (within(b, a.p, a.r)) {
        return true;
    }

    return false;
}

inline bool right_dir(V pt, asteroid a) {
    return proj(pt - a.p, a.d).parallel(a.d);
}

bool cylinder(V s, V b, asteroid a) {
    V v1 = b - s;

    if (v1.parallel(a.d) || v1.antiparallel(a.d)) {
        V close = closest_point_on_line(s, b - s, a.p);

        if (within(a.p, close, a.r)) {
            return right_dir(s, a) || right_dir(b, a);
        }
    } else {
        auto [c1, c2] = closest_point_on_line(s, b - s, a.p, a.d);
        if (between(s, b, c1)) {
            ld dist = (c1 - c2).norm();
            if (geq(a.r, dist) && right_dir(c2, a)) {
                return true; 
            }
        }

        if (geq(a.r, dist_closest_point_on_line(a.p, a.d, s)) && right_dir(s, a)) {
            return true;
        }

        if (geq(a.r, dist_closest_point_on_line(a.p, a.d, b)) && right_dir(b, a)) {
            return true;
        }
    }

    return false;
}

int n;
V s, b;
vector<asteroid> ast;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s.x >> s.y >> s.z;
    cin >> b.x >> b.y >> b.z;
    cin >> n;

    for (int i = 0; i < n; i++) {
        V p, d;
        cin >> p.x >> p.y >> p.z;
        cin >> d.x >> d.y >> d.z;

        vector<V> pts;
        int m; cin >> m;
        for (int j = 0; j < m; j++) {
            V pt;
            cin >> pt.x >> pt.y >> pt.z;
            pts.push_back(pt);
        }

        ast.emplace_back(p, d, pts);
    }

    for (auto &cur : ast) {
        if (sphere(s, b, cur) || cylinder(s, b, cur)) {
            cout << "Surrender\n";
            return 0;
        }
    }

    cout << "Go\n";

    return 0;
}

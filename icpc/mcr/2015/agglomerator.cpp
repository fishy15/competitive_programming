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

struct pt {
    ld x, y;

    pt operator+(const pt &other) const {
        return {x + other.x, y + other.y};
    }

    pt operator-(const pt &other) const {
        return {x - other.x, y - other.y};
    }

    pt &operator+=(const pt &other) {
        return *this = *this + other;
    }

    pt operator*(const ld r) const {
        return {r * x, r * y};
    }

    ld dist2() const {
        return x * x + y * y;
    }
};

typedef pt P;
bool circleInter(P a, P b, ld r1, ld r2) {
    return sqrt((a - b).dist2()) - r1 - r2 < eps;
}

struct circle {
    pt o;
    pt v;
    ld r;

    circle(ld x, ld y, ld vx, ld vy, ld r) : o{x, y}, v{vx, vy}, r(r) {}
    circle(pt o, pt v, ld r) : o(o), v(v), r(r) {}

    circle move(ld t) const {
        return circle{o + v * t, v, r};
    }

    circle merge(const circle &other) const {
        ld a1 = r * r;
        ld a2 = other.r * other.r;

        auto new_o = (o * a1 + other.o * a2) * (1 / (a1 + a2));
        auto new_v = (v * a1 + other.v * a2) * (1 / (a1 + a2));
        auto new_r = sqrt(a1 + a2);
        return {new_o, new_v, new_r};
    }
};

ld centers_closest(const circle &c1, const circle &c2) {
    ld l = 0;
    ld r = 1e9;

    auto dist_sq = [&](ld t) {
        pt o1 = c1.o + c1.v * t;
        pt o2 = c2.o + c2.v * t;
        return (o1 - o2).dist2();
    };

    for (int i = 0; i < 100; i++) {
        ld m1 = (2 * l + r) / 3;
        ld m2 = (l + 2 * r) / 3;

        if (dist_sq(m1) < dist_sq(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }

    return l;
}

ld first_inter(const circle &c1, const circle &c2, ld r) {
    ld l = 0;
    for (int i = 0; i < 200; i++) {
        ld m = (l + r) / 2;
        auto nc1 = c1.move(m);
        auto nc2 = c2.move(m);
        if (circleInter(nc1.o, nc2.o, nc1.r, nc2.r)) {
            r = m;
        } else {
            l = m;
        }
    }

    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<circle> circles;
    for (int i = 0; i < n; i++) {
        int x, y, vx, vy, r;
        cin >> x >> y >> vx >> vy >> r;
        circles.emplace_back(x, y, vx, vy, r);
    }

    ld cur_t = 0;
    while (true) {
        tuple<ld, int, int> merge_info = {INF, -1, -1};
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                auto dt = centers_closest(circles[i], circles[j]);
                auto c1 = circles[i].move(dt);
                auto c2 = circles[j].move(dt);
                if (circleInter(c1.o, c2.o, c1.r, c2.r)) {
                    // binary search to find the first time they intersect
                    auto b_dt = first_inter(circles[i], circles[j], dt);
                    merge_info = min(merge_info, {b_dt, i, j});
                }
            }
        }

        auto [dt, i, j] = merge_info;
        if (i == -1) {
            break;
        }

        cur_t += dt;
        for (auto &c : circles) {
            c = c.move(dt);
        }

        circles[i] = circles[i].merge(circles[j]);
        circles.erase(circles.begin() + j);
        n--;
    }

    cout << fixed << setprecision(15);
    cout << n << ' ' << cur_t << '\n';

    return 0;
}

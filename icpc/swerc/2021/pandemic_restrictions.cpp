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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    P unit() const { return *this / dist(); }
    friend istream &operator>>(istream &is, P &p) {
        return is >> p.x >> p.y;
    }
};

template<typename F>
double gss(double a, double b, F f) {
    double r = (sqrt(5) - 1) / 2, eps = 1e-8;
    double x1 = b - r * (b - a), x2 = a + r * (b - a);
    double f1 = f(x1), f2 = f(x2);
    while (b - a > eps) {
        if (f1 < f2) {
            b = x2; x2 = x1; f2 = f1;
            x1 = b - r*(b - a); f1 = f(x1);
        } else {
            a = x1; x1 = x2; f1 = f2;
            x2 = a + r*(b - a); f2 = f(x2);
        }
    }
    return min(f1, f2);
}

using P = Point<ld>;

double dist_meet(P a, P b, P c) {
    array<P, 3> pts = {a, b, c};

    for (int i = 0; i < 3; i++) {
        auto x = pts[i];
        auto y = pts[(i + 1) % 3];
        auto z = pts[(i + 2) % 3];
        auto side1 = (x - y).unit();
        auto side2 = (x - z).unit();
        if (side1.dot(side2) <= -0.5) {
            return (y - x).dist() + (z - x).dist();
        }
    }

    auto s1 = (a - b).dist();
    auto s2 = (a - c).dist();
    auto s3 = (b - c).dist();
    auto s = (s1 + s2 + s3) / 2;
    auto area = sqrt(s * (s - s1) * (s - s2) * (s - s3));

    return sqrt((s1*s1 + s2*s2 + s3*s3 + 4 * sqrt(3) * area) / 2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    P a, b, c;
    cin >> a >> b >> c;

    auto ans = gss(-1e4, 1e4, [&](double x) {
        return gss(-1e4, 1e4, [&](double y) {
            return max({
                dist_meet(a, b, P{x, y}),
                dist_meet(a, c, P{x, y}),
                dist_meet(b, c, P{x, y})
            });
        });
    });


    cout << fixed << setprecision(15);
    cout << ans << '\n';

    return 0;
}

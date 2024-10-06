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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

template<typename F>
double gss(double a, double b, F f) {
    double r = (sqrt(5)-1)/2, eps = 1e-7;
    double x1 = b - r*(b-a), x2 = a + r*(b-a);
    double f1 = f(x1), f2 = f(x2);
    while (b-a > eps)
        if (f1 < f2) { //change to > to find maximum
            b = x2; x2 = x1; f2 = f1;
            x1 = b - r*(b-a); f1 = f(x1);
        } else {
            a = x1; x1 = x2; f1 = f2;
            x2 = a + r*(b-a); f2 = f(x2);
        }
    return f(a);
}

using P = Point<ld>;

// finds bounds of y
pair<ld, ld> bounds(P f1, P f2, int a) {
    ld lo = max(f1.y, f2.y);
    ld hi = INF;
    ld ans_up = -1;
    rep(_, 0, 200) {
        ld m = (lo + hi) / 2;
        auto eval = [&](ld x) {
            P pt{x, m};
            return (pt- f1).dist() + (pt - f2).dist();
        };
        if (gss(-INF, INF, eval) <= a) {
            ans_up = m;
            lo = m;
        } else {
            hi = m;
        }
    }
    
    lo = -INF;
    hi = min(f1.y, f2.y);
    ld ans_down = -1;
    rep(_, 0, 200) {
        ld m = (lo + hi) / 2;
        auto eval = [&](ld x) {
            P pt{x, m};
            return (pt - f1).dist() + (pt - f2).dist();
        };
        if (gss(-INF, INF, eval) <= a) {
            ans_down = m;
            hi = m;
        } else {
            lo = m;
        }
    }

    return {ans_down, ans_up};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    P f1, f2;
    int a;
    cin >> f1.x >> f1.y >> f2.x >> f2.y;
    cin >> a;

    auto [ay1, ay2] = bounds(f1, f2, a);
    swap(f1.x, f1.y);
    swap(f2.x, f2.y);
    auto [ax1, ax2] = bounds(f1, f2, a);

    cout << fixed << setprecision(10);
    cout << ax1 << ' ' << ay1 << ' ' << ax2 << ' ' << ay2 << '\n';

    return 0;
}

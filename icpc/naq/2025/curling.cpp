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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; } // + => p on right
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    bool half() const { return y < 0 || (y == 0 && x < 0); }
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll red = 0;
    ll yellow = 0;

    using P = Point<ll>;
    P goal{144, 84};

    auto get_min = [&] {
        int n;
        cin >> n;

        vector<ll> dist;
        rep(i, 0, n) {
            P p;
            cin >> p.x >> p.y;
            dist.push_back((p - goal).dist2());
        }
        sort(all(dist));
        return dist;
    };

    rep(i, 0, 10) {
        auto rs = get_min();
        auto ys = get_min();
        if (rs.empty()) {
            yellow += sz(ys);
        } else if (ys.empty()) {
            red += sz(rs);
        } else if (rs[0] < ys[0]) {
            for (auto d : rs) {
                if (d < ys[0]) {
                    red++;
                }
            }
        } else {
            for (auto d : ys) {
                if (d < rs[0]) {
                    yellow++;
                }
            }
        }
    }

    cout << red << ' ' << yellow << '\n';

    return 0;
}

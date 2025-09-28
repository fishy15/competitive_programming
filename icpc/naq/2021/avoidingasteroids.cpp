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

template<class T> struct Point3D {
    typedef Point3D P;
    typedef const P& R;
    T x, y, z;
    explicit Point3D(T _x=0, T _y=0, T _z=0) : x(_x), y(_y), z(_z) {}
    P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
    P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
    P operator*(T d) const { return P(x*d, y*d, z*d); }
    P operator/(T d) const { return P(x/d, y/d, z/d); }
    T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
    P cross(R p) const { 
        return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
    }
    T dist2() const { return x*x + y*y + z*z; }
    double dist() const { return sqrt((double)dist2()); }
    P unit() const { return *this/(T)dist(); }
};

typedef Point3D<double> P3;

pair<P3, P3> segmentDistance3d(P3 s1, P3 e1, P3 s2, P3 e2) {
    pair<P3, P3> res{s1, s2};
    auto check = [&res](P3 a, P3 b) {
        if ((b-a).dist() < (res.second-res.first).dist())
            res = {a, b};
    };
    check(s1, s2);
    check(s1, e2);
    check(s2, s1);
    check(s2, e1);

    P3 d1 = (e1-s1).unit();
    double t1Max = (e1-s1).dist();
    P3 d2 = (e2-s2).unit();
    double t2Max = (e2-s2).dist();
    auto pointLine = [&](P3 p, P3 s, P3 d, double tMax) {
        P3 v = p-s;
        double t = v.dot(d);
        if (0 <= t && t <= tMax)
            check(s+d*t, p);
    };
    pointLine(s1, s2, d2, t2Max);
    pointLine(e1, s2, d2, t2Max);
    pointLine(s2, s1, d1, t1Max);
    pointLine(e2, s1, d1, t1Max);

    P3 n = d1.cross(d2);
    if (n.dist2() != 0) {
        double t1 = (d2.cross(n)).dot(s2-s1)/n.dot(n);
        double t2 = (d1.cross(n)).dot(s2-s1)/n.dot(n);
        if(0 <= t1 && t1 <= t1Max && 0 <= t2 && t2 <= t2Max)
            check(s1+d1*t1, s2+d2*t2);
    }
    return res;
}

bool check(P3 s, P3 b, P3 p, P3 d, const vector<P3> &hull) {
    double r = 0;
    for (auto hull_pt : hull) {
        r = max(r, (p - hull_pt).dist());
    }

    auto end_asteroid = p + d * INF;
    auto [pt1, pt2] = segmentDistance3d(s, b, p, end_asteroid);
    auto min_d = (pt1 - pt2).dist();
    return min_d > r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    P3 s, b;
    int n;
    cin >> s.x >> s.y >> s.z >> b.x >> b.y >> b.z >> n;

    rep(i, 0, n) {
       P3 p, d;
       int m;
       cin >> p.x >> p.y >> p.z >> d.x >> d.y >> d.z >> m;

       vector<P3> hull(m);
       for (auto &pt : hull) {
           cin >> pt.x >> pt.y >> pt.z;
       }

       if (!check(s, b, p, d, hull)) {
           cout << "Surrender\n";
           return 0;
       }
    }

    cout << "Go\n";

    return 0;
}

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
    bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}

template<class P>
bool inter(P a, P b, P c, P d) {
    return !segInter(a, b, c, d).empty();
}

template<class P>
bool inside(P a, P c, P d) {
    if (c.x <= a.x && a.x <= d.x) {
        if (c.y <= a.y && a.y <= d.y) {
            return true;
        }
    }
    return false;
}

void solve() {
    int xl, yl, xr, yr;
    int x1, y1, x2, y2;

    cin >> xl >> yl >> xr >> yr;
    cin >> x1 >> y1 >> x2 >> y2;

    using P = Point<ll>;
    auto p1 = P(x1, y1);
    auto p2 = P(x2, y2);
    if (inside(p1, P(xl, yl), P(xr, yr))) {
        cout << "STOP\n";
        return;
    }
    if (inside(p2, P(xl, yl), P(xr, yr))) {
        cout << "STOP\n";
        return;
    }
    if (inter(p1, p2, P(xl, yl), P(xl, yr))) {
        cout << "STOP\n";
        return;
    }
    if (inter(p1, p2, P(xl, yl), P(xr, yl))) {
        cout << "STOP\n";
        return;
    }
    if (inter(p1, p2, P(xr, yr), P(xl, yr))) {
        cout << "STOP\n";
        return;
    }
    if (inter(p1, p2, P(xr, yr), P(xr, yl))) {
        cout << "STOP\n";
        return;
    }
    cout << "OK\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

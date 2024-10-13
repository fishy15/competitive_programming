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

using P = Point<ll>;

struct DSU {
    vector<int> dsu;
    vector<int> size;
    DSU(int n) : dsu(n), size(n, 1) {
        iota(all(dsu), 0);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (size[x] < size[y]) swap(x, y);
            dsu[y] = x;
            size[x] += size[y];
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m, n, k;
    cin >> m >> n >> k;

    vector<pair<P, int>> circles;
    rep(i, 0, k) {
        int x, y, r;
        cin >> x >> y >> r;
        circles.push_back({P(x, y), r});
    }

    int top = k;
    int bottom = k+1;
    int left = k+2;
    int right = k+3;

    DSU dsu(k + 4);

    // join with ends
    rep(i, 0, k) {
        auto [o, r] = circles[i];
        if (o.x <= r) {
            dsu.join(i, left);
        }
        if (m - o.x <= r) {
            dsu.join(i, right);
        }
        if (o.y <= r) {
            dsu.join(i, top);
        }
        if (n - o.y <= r) {
            dsu.join(i, bottom);
        }
    }

    // join with each other
    rep(i, 0, k) {
        rep(j, i+1, k) {
            auto dist2 = (circles[i].first - circles[j].first).dist2();
            ll allowed = circles[i].second + circles[j].second;
            if (dist2 <= allowed * allowed) {
                dsu.join(i, j);
            }
        }
    }

    auto x_conn = dsu.find(left) == dsu.find(right);
    auto y_conn = dsu.find(top) == dsu.find(bottom);
    auto diag1 = dsu.find(left) == dsu.find(top);
    auto diag2 = dsu.find(right) == dsu.find(bottom);
    if (x_conn || y_conn || diag1 || diag2) {
        cout << "N\n";
    } else {
        cout << "S\n";
    }

    return 0;
}

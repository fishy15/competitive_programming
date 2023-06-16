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
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

#define sz(x) (x).size()
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = (a); i < (b); i++)

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P>
bool inPolygon(const vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	rep(i,0,n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}

double segDist(Point<ld>& s, Point<ld>& e, Point<ld>& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0l,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<Point<ll>> pts;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pts.push_back(P{a, 0});
    }

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pts[i].y = a;
    }

    P res;
    cin >> res.x >> res.y;

    cout << fixed << setprecision(12);

    auto hull = convexHull(pts);
    int sz = hull.size();

    auto ans = [&](const vector<ld> &vals) {
        cout << "Yes\n";

        map<P, int> rev;
        for (int i = 0; i < n; i++) {
            rev[pts[i]] = i;
        }

        vector<ld> ans(n);
        for (int i = 0; i < sz; i++) {
            ans[rev[hull[i]]] = vals[i];
        }

        for (auto x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    };

    auto comboSegment = [&](int i, int j, auto res) {
        Point<ld> a(hull[i].x, hull[i].y);
        Point<ld> b(hull[j].x, hull[j].y);
        Point<ld> re(res.x, res.y);
        ld diff_pt = (a - re).dist();
        ld diff_tot = (a - b).dist();

        vector<ld> m(sz);
        m[i] = diff_pt / diff_tot;
        m[j] = 1 - m[i];
        swap(m[i], m[j]);
        return m;
    };

    if (sz == 1) {
        if (hull[0] == res) {
            ans(vector{1.0l});
        } else {
            cout << "No\n";
        }
        return 0;
    }

    auto left_idx = min_element(hull.begin(), hull.end()) - hull.begin();
    auto right_idx = max_element(hull.begin(), hull.end()) - hull.begin();
    auto left = hull[left_idx];
    auto right = hull[right_idx];

    if (onSegment(left, right, res)) {
        ans(comboSegment(left_idx, right_idx, res));
        return 0;
    }

    for (int i = 0; i < sz; i++) {
        if (i != left_idx && i != right_idx) {
            if (onSegment(left, hull[i], res)) {
                ans(comboSegment(left_idx, i, res));
                return 0;
            }

            if (onSegment(right, hull[i], res)) {
                ans(comboSegment(right_idx, i, res));
                return 0;
            }

            if (inPolygon(vector<P>{left, right, hull[i]}, res)) {
                Point<ld> l(left.x, left.y);
                Point<ld> r(right.x, right.y);
                Point<ld> hi(hull[i].x, hull[i].y);
                Point<ld> re(res.x, res.y);

                auto d_res = segDist(l, r, re);
                auto d_i = segDist(l, r, hi);
                auto ratio_i = d_res / d_i;

                auto shift = re - hi * ratio_i;
                auto vals = comboSegment(left_idx, right_idx, shift / (1 - ratio_i));
                vals[left_idx] *= 1 - ratio_i;
                vals[right_idx] *= 1 - ratio_i;
                vals[i] = ratio_i;
                ans(vals);
                return 0;
            }
        }
    }

    cout << "No\n";

    return 0;
}

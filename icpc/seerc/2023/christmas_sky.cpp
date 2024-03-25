#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) (int) x.size()

using namespace std;
using ll = long long;

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	P operator*(T d) const { return P(x * d, y * d); }
	P operator/(T d) const { return P(x / d, y / d); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const { return x * p.y - y * p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	double angle() const { return atan2(y, x); }
	P unit() const { return * this / dist(); }
	P perp() const { return P(-y, x); }
	P normal() const { return perp().unit(); }
	P rotate(double a) const {
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
	friend ostream& operator<<(ostream &os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<double> P;
double ccRadius(const P &A, const P &B, const P &C) {
	return (B - A).dist() * (C - B).dist() * (A - C).dist() / 
		abs((B - A).cross(C - A)) / 2;
}
P ccCenter(const P &A, const P &B, const P &C) {
	P b = C - A, c = B - A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

pair<P, double> mec(vector<P> ps) {
	shuffle(all(ps), mt19937(time(0)));
	P o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
	rep(i, 0, sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
		o = ps[i], r = 0;
		rep(j, 0, i) if ((o - ps[j]).dist() > r * EPS) {
			o = (ps[i] + ps[j]) / 2;
			r = (o - ps[i]).dist();
			rep(k, 0, j) if ((o - ps[k]).dist() > r * EPS) {
				o = ccCenter(ps[i], ps[j], ps[k]);
				r = (o - ps[i]).dist();
			}
		}
	}
	return {o, r};
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vector<P> pt1(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		pt1[i] = P{(double) x, (double) y};
	}

	int m;
	cin >> m;

	vector<P> pt2(m);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		pt2[i] = P{(double) x, (double) y};
	}

	vector<P> tot;
	for (auto p1 : pt1) {
		for (auto p2 : pt2) {
			tot.push_back(p2 - p1);
		}
	}

	auto [t, d] = mec(tot);
	
	cout << fixed << setprecision(15);
	cout << d << ' ' << t.x << ' ' << t.y << '\n';

	return 0;
}

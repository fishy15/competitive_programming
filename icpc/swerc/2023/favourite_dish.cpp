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
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(P p) const { return P(x*p.x, y*p.y); }
	P operator/(P p) const { return P(x/p.x, y/p.y); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const  { return x * p.y - y * p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	double angle() const { return atan2(y, x); }
	P unit() const { return *this / dist(); }
	P perp() const { return P(-y, x); }
	P normal() const { return perp().unit(); }
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a)); }
	friend ostream &operator<<(ostream &os, P p) {
		return os << "(" << p.x << ", " << p.y << ")"; }
};

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), hb.begin() + t - (t == 2 && h[0] == h[1])};
}

typedef Point<ll> P;
vector<P> convexHull2(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) < 0) t--;
			h[t++] = p;
		}
	return {h.begin(), hb.begin() + t - (t == 2 && h[0] == h[1])};
}

struct frac {
	ll x, y;

	frac(ll x, ll y) {
		auto g = gcd(x, y);
		this->x = x / g;
		this->y = y / g;

		if (this->y < 0) {
			this->x *= -1;
			this->y *= -1;
		}
	}

	bool operator<(const frac &other) const {
		return x * other.y < y * other.x;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
    
	int n, m;
	cin >> n >> m;

	vector<Point<ll>> dishes(n);
	map<P, int> idx;
	for (int i = 0; i < n; i++) {
		cin >> dishes[i].x >> dishes[i].y;
		idx[dishes[i]] = i; // laziness
	}

	auto chull = convexHull(dishes);
	auto chull2 = convexHull2(dishes);
	P upmost, rightmost;
	for (auto p : chull) {
		if (upmost.y < p.y || (upmost.y == p.y && upmost.x > p.x)) {
			upmost = p;
		}
		if (rightmost.x < p.x || (rightmost.x == p.x && rightmost.y > p.y)) {
			rightmost = p;
		}
	}

	// restrict to only points on the range
	auto start_it = find(chull.begin(), chull.end(), rightmost);
	auto end_it = find(chull.begin(), chull.end(), upmost);
	chull = vector<P>(start_it, end_it + 1);

	start_it = find(chull2.begin(), chull2.end(), rightmost);
	end_it = find(chull2.begin(), chull2.end(), upmost);
	chull2 = vector<P>(start_it, end_it + 1);

	// look on chull2 for this, it has duplicates
	map<frac, int> break_ties;
	for (int i = 0; i < (int) chull2.size() - 1; i++) {
		auto pt1 = chull2[i];
		auto pt2 = chull2[i + 1];

		auto orig1 = idx[pt1];
		auto orig2 = idx[pt2];

		auto diff = pt2 - pt1;
		// we don't care abt these edge cases
		if (diff.x != 0 && diff.y != 0) {
			frac slope{diff.y, diff.x};
			if (!break_ties.count(slope)) {
				break_ties[slope] = min(orig1, orig2);
			} else {
				break_ties[slope] = min({break_ties[slope], orig1, orig2});
			}
		}
	}

	// now we actually process segments, 

	return 0;
}

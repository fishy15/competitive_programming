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
 
template<typename T>
struct point {
    T x, y;
 
    point() : x{}, y{} {}
    point(T x, T y) : x{x}, y{y} {}
 
    point operator+(const point<T> &other) const { return {x + other.x, y + other.y}; }
    point &operator+=(const point<T> &other) { return *this = *this + other; }
    point operator-(const point<T> &other) const { return {x - other.x, y - other.y}; }
    point &operator-=(const point<T> &other) { return *this = *this - other; }

    T norm2() const { return x * x + y * y; }
    ld norm() const { return sqrt(x * x + y * y); }
    T cross(const point<T> &other) { return x * other.y - y * other.x; }
};

template<typename T>
istream &operator>>(istream &in, point<T> &p) {
    return in >> p.x >> p.y;
}

template<typename T>
struct segment : public pair<point<T>, point<T>> {
    segment() : pair<point<T>, point<T>>{} {}
    segment(point<T> first, point<T> second) : pair<point<T>, point<T>>{first, second} {}

    pair<T, T> project_x() const {
        return {this->first.x, this->second.x};
    }

    pair<T, T> project_y() const {
        return {this->first.y, this->second.y};
    }
};

template<typename T>
int get_side(segment<T> seg, point<T> p) {
    auto vec = seg.second - seg.first;
    auto c = vec.cross(p - seg.second);
    return c > eps ? 1 : c < -eps ? -1 : 0;
}

template<typename T>
bool intersects(segment<T> seg1, segment<T> seg2) {
    auto check_projection = [](pair<T, T> proj1, pair<T, T> proj2) {
        if (proj1.first > proj1.second) swap(proj1.first, proj1.second);
        if (proj2.first > proj2.second) swap(proj2.first, proj2.second);
        return max(proj1.first, proj2.first) <= min(proj1.second, proj2.second);
    };

    if (get_side(seg1, seg2.first) == 0 && get_side(seg1, seg2.second) == 0) {
        return check_projection(seg1.project_x(), seg2.project_x())
            && check_projection(seg1.project_y(), seg2.project_y());
    } else {
        return get_side(seg1, seg2.first) != get_side(seg1, seg2.second)
            && get_side(seg2, seg1.first) != get_side(seg2, seg1.second);
    }
}

void solve() {
    point<ll> p1, p2, p3, p4;
    cin >> p1 >> p2 >> p3 >> p4;

    segment seg1{p1, p2};
    segment seg2{p3, p4};

    if (intersects(seg1, seg2)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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

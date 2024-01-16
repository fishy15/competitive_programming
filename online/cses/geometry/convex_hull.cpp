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

    bool operator<(const point<T> &other) const { return tie(x, y) < tie(other.x, other.y); }
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    int n;
    cin >> n;

    vector<point<ll>> points(n);
    for (auto &p : points) {
        cin >> p;
    }

    sort(points.begin(), points.end());

    vector<point<ll>> top_hull, bottom_hull;
    for (auto p : points) {
        // insert into top hull
        while (top_hull.size() >= 2) {
            auto a = end(top_hull)[-2];
            auto b = end(top_hull)[-1];
            if (get_side(segment{a, b}, p) != 1) {
                break;
            }
            top_hull.pop_back();
        }
        top_hull.push_back(p);

        // insert into top hull
        while (bottom_hull.size() >= 2) {
            auto a = end(bottom_hull)[-2];
            auto b = end(bottom_hull)[-1];
            if (get_side(segment{a, b}, p) != -1) {
                break;
            }
            bottom_hull.pop_back();
        }
        bottom_hull.push_back(p);
    }

    set<point<ll>> chull;
    for (auto p : top_hull) {
        chull.insert(p);
    }
    for (auto p : bottom_hull) {
        chull.insert(p);
    }

    cout << chull.size() << '\n';
    for (auto p : chull) {
        cout << p.x << ' ' << p.y << '\n';
    }

    return 0;
}
